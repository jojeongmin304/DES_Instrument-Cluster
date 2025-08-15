#ifndef BATTERYPROVIDER_H
#define BATTERYPROVIDER_H

# include <QObject>
# include <QTimer>
#include "INA219.h"
#include "BatterySoc.h"

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
    bool isFirstReading;
    QTimer _timer;
    INA219 _ina219;
    BatterySOC _battery_soc;
};

#endif // BATTERYPROVIDER_H
