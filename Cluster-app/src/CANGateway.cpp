#include "CANGateway.h"
#include "error.h"

#include <QThread>
#include <QByteArray>
#include <QDebug>

/* CON & DESTRUNTOR */
CANGateway::CANGateway(QObject *parent)
: QObject(parent), status(INIT) {}

CANGateway::CANGateway(const std::string& interface)
: QObject(nullptr), ifname(interface), status(INIT) {
	_init();
}

CANGateway::~CANGateway() {
    status = STOP;
    if (_pipe.socket > 0) {
        close(_pipe.socket);
        emit disconnected();
    }
}

/* QT METHODS */
void CANGateway::start() {
	if (status != READY) {
		qDebug() << "[Gateway] Interface not ready:" << QString::fromStdString(ifname);
		emit finished();
		return;
	} 

	// Start processing CAN data
	can_frame frame;
	qDebug() << "[Gateway] Started processing on interface" << QString::fromStdString(ifname) << "...";

	status = ACTIVE;
	emit connected();
	
    while (status == ACTIVE) {
        if (read(_pipe.socket, &frame, sizeof(struct can_frame)) > 0)
			_startHandleData(frame);
		else
            QThread::msleep(10);
    }

	// Processing loop finished
	qDebug() << "[Gateway] Processing loop finished for" << QString::fromStdString(ifname);
	emit disconnected();
	emit finished();
}

void CANGateway::_startHandleData(const can_frame& frame) {
	qDebug() << "[Gateway] Frame Received on" << QString::fromStdString(ifname) 
			 << "- ID:" << Qt::hex << frame.can_id
		     << ", Len:" << frame.can_dlc
		     << ", Data:" << QByteArray(reinterpret_cast<const char*>(frame.data), frame.can_dlc).toHex(' ');

	// Create QByteArray from raw CAN frame data
	QByteArray frameData(reinterpret_cast<const char*>(frame.data), frame.can_dlc);
	
	emit newData(frame.can_id, frameData);
}

void CANGateway::stop() {
	status = STOP;
	qDebug() << "[Gateway] Stopping CAN gateway for" << QString::fromStdString(ifname);
}

/* CLASS METHODS */
void CANGateway::_init() {
    qDebug() << "[Gateway] Initializing CAN interface" << QString::fromStdString(ifname) << "...";

	try {
		_initDomainSocket();
		_initCanInterface();
		_initBind();

		status = READY;
		qDebug() << "[Gateway] CAN interface" << QString::fromStdString(ifname) << "ready.";
		
	} catch (const std::exception& e) {
		status = FAULT;
		qCritical() << "[Gateway] Initialization failed for" 
			        << QString::fromStdString(ifname) << ":" << e.what();
		throw;
	}
}

void CANGateway::_initDomainSocket() {
    _pipe.socket = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (_pipe.socket < 0) {
        throw Error(ERR_INIT_FAIL_DOMAIN_SOCKET);
    }
}

void CANGateway::_initCanInterface() {
    std::strcpy(_pipe.ifr.ifr_name, ifname.c_str());
    if (ioctl(_pipe.socket, SIOCGIFINDEX, &_pipe.ifr) < 0) {
		throw Error(ERR_INIT_FAIL_CAN_INTERFACE);
    }
}

void CANGateway::_initBind() {
    _pipe.addr.can_family = AF_CAN;
    _pipe.addr.can_ifindex = _pipe.ifr.ifr_ifindex;
    if (bind(_pipe.socket, (struct sockaddr *)&_pipe.addr, sizeof(_pipe.addr)) < 0) {
		throw Error(ERR_INIT_FAIL_BIND);
    }
}
