#include "ViewModel.h"

#include <QDebug>
#include <cstring>

ViewModel::ViewModel(QObject *parent)
: QObject(parent), _speed(0) {}

ViewModel::~ViewModel() {}

/* QT METHODS */
void ViewModel::receiveData(int canID, const QByteArray& data) {
	qDebug() << "[ViewModel] Received CAN frame - ID:" << Qt::hex << canID 
			 << "Data:" << data.toHex(' ') << "Size:" << data.size();
	
	switch (canID) {
		case ID_RPM: {
			if (data.size() < 2) {
				qWarning() << "[ViewModel] RPM frame too short:" << data.size();
				break;
			}

			// Convert RPM to speed using wheel diameter
			// Speed = (wheel circumference * RPM) / 60 (to get per second)
			// Result in cm/s as per your original implementation
			int val = static_cast<int>(WHEEL_DIAMETER * PI * static_cast<float>(_int(data, 0)) / 60.0f);
			if (val != _speed) {
				_speed = val;
				emit updateSpeed();
			}
			break;
		}

		default: qDebug() << "[ViewModel] Unreserved CAN ID received:" << Qt::hex << canID;
	}
}

/* CLASS METHODS */
int ViewModel::_int(const QByteArray& data, int pos = 0) const {
	if (pos + 1 >= data.size()) {
		return 0;
	}
	
	// Parse as big-endian 16-bit integer
	return (static_cast<unsigned char>(data[pos]) << 8) | 
		    static_cast<unsigned char>(data[pos + 1]);
}