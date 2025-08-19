#ifndef BATTERYPROVIDER_H
#define BATTERYPROVIDER_H

# include <QObject>
# include <QTimer>
# include <deque>
# include "INA219.h"
# include "BatterySoc.h"

class BatteryProvider : public QObject {
    Q_OBJECT
    Q_PROPERTY(int capacity READ capacity WRITE setCapacity NOTIFY capacityChanged)

public:
    BatteryProvider();
    explicit BatteryProvider(QObject *);
    ~BatteryProvider();

    inline int capacity() const { return _capacity;}
    void setCapacity(int);

signals:
    void capacityChanged();

private slots:
    void updateCapacity();

private:
    int _capacity;
    QTimer _timer;
    INA219 _ina219;
    BatterySOC _battery_soc;

    // --- 이동 평균 필터 및 이상치 제거를 위한 변수 추가 ---
    std::deque<float> _voltage_history;
    const size_t _filter_window_size = 10;      // 평균 낼 샘플 개수
    const float _voltage_drop_threshold = 0.01f; // 이 값(0.01V) 이상 떨어지면 무시
};

#endif // BATTERYPROVIDER_H
