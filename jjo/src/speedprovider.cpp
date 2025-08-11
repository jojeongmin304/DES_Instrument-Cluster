#include "speedprovider.h"

#include <QDebug> // For logging

SpeedProvider::SpeedProvider(QObject *parent) : QObject(parent) {}

int SpeedProvider::speed() const {
    return m_speed;
}

void SpeedProvider::setSpeed(int speed) {
    if (m_speed == speed)
        return;
    m_speed = speed;
    emit speedChanged(); // Notify QML that the value has changed
}

// This is where the magic happens!
void SpeedProvider::onMessageReceived(int id, int dlc, const QVariantList &data, double timestamp) {
    // Let's assume CAN ID 0x180 is for vehicle speed and the value is in the first byte.
    // This is just an example; you'll need to adapt it to your actual CAN data specification.
    const int VEHICLE_SPEED_ID = 0x10;

	// Log the entire received data list for debugging purposes
    qDebug() << "Received CAN message data:" << data;

    if (id == VEHICLE_SPEED_ID) {
        if (!data.isEmpty()) {
            int new_speed = data.first().toInt();

            setSpeed(new_speed);
        }
    }
    // You can add more 'if' or 'switch' statements here to handle other CAN IDs.
}

// #include "speedprovider.h"

// SpeedProvider::SpeedProvider(QObject *parent)
//     : QObject(parent), m_speed(0), m_isSpeedingUp(true)
// {
//     auto timer = new QTimer(this);
//     connect(timer, &QTimer::timeout, this, &SpeedProvider::updateSpeed);
//     timer->start(50);
// }

// int SpeedProvider::speed() const
// {
//     return m_speed;
// }

// void SpeedProvider::updateSpeed()
// {
//     if (m_isSpeedingUp) {
//         m_speed += 2;
//         if (m_speed >= 220) {
//             m_speed = 220;
//             m_isSpeedingUp = false;
//         }
//     } else {
//         m_speed -= 2;
//         if (m_speed <= 0) {
//             m_speed = 0;
//             m_isSpeedingUp = true;
//         }
//     }
//     emit speedChanged();
// }
