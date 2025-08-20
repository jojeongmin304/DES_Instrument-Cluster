#include "BatteryMonitor.h"

BatteryMonitor::BatteryMonitor()
	: _chip(INA219_I2C_BUS, INA219_ADDRESS), _battery(BTRYSOC_CELLS_SERIES) {}

BatteryMonitor::~BatteryMonitor() {}

int BatteryMonitor::getSoc() {
	float val = _filterAbnormalDrop(_chip.getBusVoltage());

    _vrecord.push_back(val);
	_sum += val;
    if (_vrecord.size() > FILTER_RANGE) {
		_sum -= _vrecord.front();
        _vrecord.pop_front();
    }

    // Return the filtered soc value as a percentage (full charged: 100%)
    return static_cast<int>(_battery.voltageToSoC(_average));
}

float BatteryMonitor::_filterAbnormalDrop(float val) {
	float result = val;
	if (!_vrecord.empty()) {
        _average = _sum / _vrecord.size();
        if (val < (_average - THRESHOLD)) {
            result = _vrecord.back();
        }
    }
	return result;
}