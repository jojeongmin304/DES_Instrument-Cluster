#include "SpeedProvider.h"

SpeedProvider::SpeedProvider()
	: _speed(0) {}

SpeedProvider::SpeedProvider(QObject *parent = nullptr)
    : QObject(parent), _speed(0) {}

SpeedProvider::~SpeedProvider() {}

void SpeedProvider::setSpeed(size_t val) {
    if (_speed != val) {
		_speed = val;
		// Notify QML that the value has changed
        emit speedChanged(); 
    }
}
