#ifndef RPMGAUGE_H
#define RPMGAUGE_H
#pragma once

#include <QGraphicsItem>
#include <QPropertyAnimation>

class RPMGauge : public QObject, public QGraphicsItem {
    Q_OBJECT
    Q_PROPERTY(qreal rotationAngle READ rotationAngle WRITE setRotationAngle)

public:
    RPMGauge();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

    qreal rotationAngle() const;
    void setRotationAngle(qreal angle);

private:
    qreal m_rotation;
    QPropertyAnimation *animation;
};

#endif // RPMGAUGE_H
