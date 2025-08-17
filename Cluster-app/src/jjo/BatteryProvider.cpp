#include "BatteryProvider.h"
#include <numeric>

BatteryProvider::BatteryProvider()
    : _capacity(0), _ina219(1, 0x41), _battery_soc(3) {
    // INA219 칩 초기화 (begin 함수는 내부적으로 오류를 처리한다고 가정)
    _ina219.begin(0.1f, 3.2f);

    // 타이머의 timeout 시그널을 updateBatteryStatus 슬롯(함수)에 연결합니다.
    connect(&_timer, &QTimer::timeout, this, &BatteryProvider::updateCapacity);

    // 5초(5000ms)마다 타이머가 timeout 시그널을 보내도록 시작합니다.
    _timer.start(5000);
}

BatteryProvider::BatteryProvider(QObject *parent = nullptr)
    : QObject(parent), _capacity(0) {}

// 1초마다 타이머에 의해 호출되는 함수
void BatteryProvider::updateCapacity()
{
    // 1. INA219 칩에서 현재 버스 전압을 읽어옵니다.
    float new_voltage = _ina219.getBusVoltage();

    float voltage_to_add = new_voltage;

    // 2. (이상치 제거) 비정상적인 전압 강하인지 확인
    if (!_voltage_history.empty()) {
        float sum = std::accumulate(_voltage_history.begin(), _voltage_history.end(), 0.0f);
        float average_voltage = sum / _voltage_history.size();
        if (new_voltage < (average_voltage - _voltage_drop_threshold)) {
            voltage_to_add = _voltage_history.back();
        }
    }

    // 3. (이동 평균) 위에서 선택된 '정상적인' 값을 history에 추가
    _voltage_history.push_back(voltage_to_add);
    if (_voltage_history.size() > _filter_window_size) {
        _voltage_history.pop_front();
    }

    // 4. 필터링된 평균 전압 계산
    float sum = std::accumulate(_voltage_history.begin(), _voltage_history.end(), 0.0f);
    float average_voltage = sum / _voltage_history.size();

    // 5. 읽어온 전압을 바탕으로 배터리 용량(%)을 계산합니다.
    int currentSoc = static_cast<int>(_battery_soc.voltageToSoC(average_voltage));

    // 6. 계산된 새로운 값으로 내부 상태를 업데이트합니다.
    setCapacity(currentSoc);
}

BatteryProvider::~BatteryProvider() {}

void BatteryProvider::setCapacity(int val) {
    if (val != _capacity) {
        _capacity = val;
        emit capacityChanged();
    }
}

