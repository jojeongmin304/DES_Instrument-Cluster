#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H

#pragma once

#include <QGraphicsItem>
#include <QPropertyAnimation>

class Speedometer : public QObject, public QGraphicsItem {
    Q_OBJECT
    Q_PROPERTY(qreal rotationAngle READ rotationAngle WRITE setRotationAngle)

public:
    Speedometer();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

    qreal rotationAngle() const;
    void setRotationAngle(qreal angle);

private:
    qreal m_rotation;
    QPropertyAnimation *animation;
};

#endif // SPEEDOMETER_H
