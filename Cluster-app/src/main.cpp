#include "InstrumentCluster.h"

#include <QDebug>

int main(int argc, char *argv[]) {
    try {
        InstrumentCluster cluster(argc, argv);

        if (!cluster.openGateway("can1")) {
			qCritical() << "Failed to open can1";
            return EXIT_FAILURE;
        }
        
		ViewModel model;
        cluster.connectModel("can1", model);
        cluster.registerModel("ViewModel", &model);
        cluster.loadQML("qrc:/Main.qml");
        
        return cluster.run();
        
    } catch (const std::exception& e) {
        qCritical() << "Application error:" << e.what();
        return EXIT_FAILURE;
    }
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