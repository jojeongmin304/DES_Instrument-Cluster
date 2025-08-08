#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "speedometer.h"
#include "rpmgauge.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QGraphicsScene *scene;
    QGraphicsView *view;
};

#endif // MAINWINDOW_H
