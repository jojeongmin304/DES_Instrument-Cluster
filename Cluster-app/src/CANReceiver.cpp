#include "CANReceiver.h"

#include <QDebug>
#include <QByteArray>
#include <iostream>

// I am not sure why this is needed, but it seems to be a workaround for some issue with QThread.
CANReceiver::CANReceiver(QObject *parent = nullptr)
	: QThread(parent), _isRunning(true), _speed(0) {
		// _init(canName);
}

CANReceiver::CANReceiver(const std::string& canName)
	: QThread(nullptr), _isRunning(true), _speed(0) {
		_can.name = canName;
		_init();
}

CANReceiver::~CANReceiver() {
    _isRunning = false;

    if (_can.socket >= 0) {
        close(_can.socket);
    }
    wait();
}

void CANReceiver::_init() {
    qDebug() << "[Receiver] CAN socket initializing on " << QString::fromStdString(_can.name) << ".";

	_initDomainSocket();
	_initCanInterface();
	_initBind();
}

void CANReceiver::_initDomainSocket() {
    _can.socket = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (_can.socket < 0) {
        throw Error(INIT_FAIL_DOMAIN_SOCKET);
    }
}

void CANReceiver::_initCanInterface() {
    std::strcpy(_can.ifr.ifr_name, _can.name.c_str());
    if (ioctl(_can.socket, SIOCGIFINDEX, &_can.ifr) < 0) {
		throw Error(INIT_FAIL_CAN_INTERFACE);
    }
}

void CANReceiver::_initBind() {
    _can.addr.can_family = AF_CAN;
    _can.addr.can_ifindex = _can.ifr.ifr_ifindex;

    if (bind(_can.socket, (struct sockaddr *)&_can.addr, sizeof(_can.addr)) < 0) {
		throw Error(INIT_FAIL_BIND);
    }
}

void CANReceiver::run() {
    can_frame frame;
	qDebug() << "[Receiver] Thread started, listening for messages from " << QString::fromStdString(_can.name) << "...";

    while (_isRunning) {
        if (read(_can.socket, &frame, sizeof(struct can_frame)) > 0)
			_runHandleData(frame);
        else
            msleep(20); // Set interval
    }
}

void CANReceiver::_runHandleData(const can_frame& frame) {
	// Display all the received information
    //qDebug() << "[Receiver] Frame Received - ID:" << Qt::hex << frame.can_id
    //	     << "/ Len:" << frame.len
    //	     << "/ Data:" << QByteArray(reinterpret_cast<const char*>(frame.data), frame.len).toHex(' ');

	// Handle the data sent from Arduino
	switch (frame.can_id) {
		case ID_SPEED: {
			if (frame.len > 1) {
				float val = static_cast<float>((frame.data[0] << 8) | frame.data[1]); // RPM
				float speed = WHEEL_DIAMETER * PI * val / 60.0f; 
				emit newSpeed(static_cast<size_t>(speed));
			} break;
		}
		default: qDebug() << "[Receiver] Unreserved can_id has sent: " << Qt::hex << frame.can_id;
	}
}
