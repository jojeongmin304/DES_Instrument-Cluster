#include "rpmgauge.h"
#include <QPainter>
#include <QTimer>
#include <QtMath>

RPMGauge::RPMGauge() : m_rotation(0) {
    setTransformOriginPoint(100, 100);  // center for rotation

    animation = new QPropertyAnimation(this, "rotationAngle");
    animation->setDuration(1000);
    animation->setStartValue(0);
    animation->setEndValue(180);  // simulate max 180 km/h
    animation->start();

    // Animate every second with a new random speed
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=]() {
        int newSpeed = rand() % 181;  // 0 to 180
        animation->stop();
        animation->setStartValue(m_rotation);
        animation->setEndValue(newSpeed);
        animation->start();
    });
    timer->start(1500);
}

QRectF RPMGauge::boundingRect() const {
    return QRectF(0, 0, 200, 200);
}

void RPMGauge::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawEllipse(0, 0, 200, 200);  // dial background

    // draw needle
    painter->save();
    painter->translate(100, 100);
    painter->rotate(m_rotation - 90);  // rotate needle
    painter->setPen(QPen(Qt::red, 3));
    painter->drawLine(0, 0, 70, 0);  // needle line
    painter->restore();

    // draw speed markers
    for (int i = 0; i <= 180; i += 30) {
        painter->save();
        painter->translate(100, 100);
        painter->rotate(i - 90);
        painter->drawLine(80, 0, 90, 0);
        painter->restore();
    }
}

qreal RPMGauge::rotationAngle() const {
    return m_rotation;
}

void RPMGauge::setRotationAngle(qreal angle) {
    m_rotation = angle;
    update();
}

