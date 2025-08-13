#ifndef SPEEDPROVIDER_H
#define SPEEDPROVIDER_H

#include <QObject>
#include <QVariantList> // Include this

class SpeedProvider : public QObject
{
    Q_OBJECT
    // The speed property that QML will bind to.
    Q_PROPERTY(int speed READ speed WRITE setSpeed NOTIFY speedChanged)

public:
    explicit SpeedProvider(QObject *parent = nullptr);

    int speed() const;
    void setSpeed(int speed);

public slots:
    // This slot will connect to the CanGatewayClient's signal.
    void onMessageReceived(int id, int dlc, const QVariantList &data, double timestamp);

	signals:
    void speedChanged();

private:
     int m_speed =0;
};

#endif // SPEEDPROVIDER_H
