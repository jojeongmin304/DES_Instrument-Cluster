#include "SpeedProvider.h"

#include <iostream>

SpeedProvider::SpeedProvider()
	: _speed(0) {}

SpeedProvider::SpeedProvider(QObject *parent = nullptr)
    : QObject(parent), _speed(0) {}

SpeedProvider::~SpeedProvider() {}

void SpeedProvider::setSpeed(int val) {
	std::cout << "changing spee from " << _speed << " to " << val << "\n";
    // if (_speed != val) {
		_speed = val;
		// Notify QML that the value has changed
    // }
	emit speedChanged(); 
}
