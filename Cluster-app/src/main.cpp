#include "InstrumentCluster.h"

#include <QDebug>

int main(int argc, char *argv[]) {
	int appExit = EXIT_FAILURE;
	
	try {
		QGuiApplication app(argc, argv);
		InstrumentCluster cluster;
 
		ViewModel model;

		if (cluster.openCan("can1")) {
			cluster.connectCanModel("can1", model, &ViewModel::receiveCanData);
		} else {
			qCritical() << "Fail to open can1";
		}

		cluster.setTimer("battery");
		cluster.connectTimerModel("battery", 5000, model, &ViewModel::receiveTimeout);
		
		cluster.registerModel("ViewModel", model);
		cluster.loadQml("qrc:/Main.qml", app);
		appExit = app.exec();

	} catch (const std::exception& e) {
		qCritical() << "Application error:" << e.what();
	}

	return appExit;
}

/*
* Instrument Cluster Application Workflow:
* 
* 1. Application Initialization:
*    - InstrumentCluster creates Qt application and QML engine
*    - Sets up infrastructure for multi-threaded CAN communication
* 
* 2. CAN Gateway Setup:
*    - openGateway() creates CANGateway instance for "can1" interface
*    - CANGateway moves to dedicated thread for non-blocking operation
*    - Thread starts and CANGateway begins listening for CAN frames
* 
* 3. Data Processing Pipeline:
*    - ViewModel created to handle instrument data processing
*    - connectModel() links CANGateway signals to ViewModel slots
*    - When CAN data arrives: CANGateway::newData() → ViewModel::receiveData()
* 
* 4. QML Integration:
*    - registerModel() exposes ViewModel to QML as "ViewModel" property
*    - loadQML() loads Main.qml interface with access to ViewModel data
*    - Q_PROPERTY bindings allow QML to react to data changes automatically
* 
* 5. Runtime Operation:
*    - Qt event loop handles cross-thread communication
*    - CAN frames processed in background thread
*    - UI updates happen on main thread via Qt's signal/slot mechanism
*    - Application runs until user exits or error occurs
* 
* Data Flow:
* CAN Bus → CANGateway (thread) → ViewModel (main thread) → QML UI
*/