#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    setCentralWidget(view);

    Speedometer *speed = new Speedometer();
    RPMGauge *rpm = new RPMGauge();

    scene->addItem(speed);
    scene->addItem(rpm);

    speed->setPos(50, 50);
    rpm->setPos(300, 50);
}

MainWindow::~MainWindow() {
    // Cleanup handled by Qt parent-child hierarchy
}
