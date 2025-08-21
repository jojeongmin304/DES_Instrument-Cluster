#include "InstrumentCluster.h"

#include <QDebug>

int main(int argc, char *argv[]) {
	int appExit = EXIT_FAILURE;
	
	try {
		QGuiApplication app(argc, argv);

		InstrumentCluster cluster;
		ViewModel model;

		qDebug() << "1";
		const std::shared_ptr<SharedMemory>& vehicle = cluster.getVehicle();
		qDebug() << "2";
		if (vehicle && vehicle->isValid()) {
			qDebug() << "3";
			model.setVehicle(vehicle);

			qDebug() << "4";
			cluster.setTimer("drivemod");
			cluster.connectTimerModel("drivemode", 300, model, &ViewModel::receiveTimeout);
			qDebug() << "5";
		}
		
		const std::shared_ptr<BatteryMonitor>& battery = cluster.getBattery();
		if (battery && battery->isConnected()) {
			model.setBattery(battery);

			cluster.setTimer("battery");
			cluster.connectTimerModel("battery", 5000, model, &ViewModel::receiveTimeout);
		}

		if (cluster.openCan("can1")) {
			cluster.connectCanModel("can1", model, &ViewModel::receiveCanData);
		} else {
			qCritical() << "Fail to open can1";
		}
		
		cluster.registerModel("ViewModel", model);
		cluster.loadQml("qrc:/Main.qml", app);
		appExit = app.exec();

	} catch (const std::exception& e) {
		qCritical() << "Application error:" << e.what();
	}

	return appExit;
}
