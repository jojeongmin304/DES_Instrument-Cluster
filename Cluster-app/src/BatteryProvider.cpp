#include "BatteryProvider.h"

BatteryProvider::BatteryProvider()
    : _capacity(0), isFirstReading(true), _ina219(1, 0x41), _battery_soc(3) {
    // INA219 칩 초기화 (begin 함수는 내부적으로 오류를 처리한다고 가정)
    _ina219.begin(0.1f, 3.2f);

    // 타이머의 timeout 시그널을 updateBatteryStatus 슬롯(함수)에 연결합니다.
    connect(&_timer, &QTimer::timeout, this, &BatteryProvider::updateCapacity);

    // 1초(1000ms)마다 타이머가 timeout 시그널을 보내도록 시작합니다.
    _timer.start(1000);
}

BatteryProvider::BatteryProvider(QObject *parent = nullptr)
    : QObject(parent), _capacity(0) {}

// 1초마다 타이머에 의해 호출되는 함수
void BatteryProvider::updateCapacity()
{
    // 1. INA219 칩에서 현재 버스 전압을 읽어옵니다.
    float voltage = _ina219.getBusVoltage();

    // 2. 읽어온 전압을 바탕으로 배터리 용량(%)을 계산합니다.
    int currentSoc = static_cast<int>(_battery_soc.voltageToSoC(voltage));

    // 3. 계산된 새로운 값으로 내부 상태를 업데이트합니다.
    setCapacity(currentSoc);
}

BatteryProvider::~BatteryProvider() {}

void BatteryProvider::setCapacity(int val) {
    if (isFirstReading) {
        _capacity = val;
        isFirstReading = false;
        emit capacityChanged();
        return; //함수종료
    }

    if (val != _capacity && (val > _capacity || _capacity - val > 5)) {
        _capacity = val;
        emit capacityChanged();
    }
}

