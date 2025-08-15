#include "CANReceiver.h"
#include "SpeedProvider.h"
#include "BatteryProvider.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

	try {
		// 1. Create the worker objects with CAN init and starting the QThread
        SpeedProvider speedPrv;
        BatteryProvider batteryPrv;
		CANReceiver canRcv1("can1"); 

		// 2. Connect Receiver to speedPrv 
		// Once CanReceiver emit the newSpeed() signals, the speed setter may catch the signal and execute it
		QObject::connect(&canRcv1, &CANReceiver::newSpeed,
		&speedPrv, &SpeedProvider::setSpeed);
        //batteryprovider이거도 추가해야하나?
        //QObject::connect(&)
		
		// 3. Expose the instance of c++ to QML
		engine.rootContext()->setContextProperty("speedController", &speedPrv);
        engine.rootContext()->setContextProperty("batteryController", &batteryPrv);
		
		// 4. Run the CANReceiver on the QTread
		canRcv1.start();
		
		// Load the Main.qml
		const QUrl url(QStringLiteral("qrc:/Main.qml"));
		QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &app,
			[url](QObject *obj, const QUrl &objUrl) {
				if (!obj && url == objUrl)
				QCoreApplication::exit(-1);
			},
			Qt::QueuedConnection);
		engine.load(url);
		
		return app.exec();
		
		// 5. Handle the program exit
		// Before the termination of app, stop the CANReceiver QThred safely
		canRcv1.quit();
		canRcv1.wait();
		
	} catch (const std::runtime_error &e) {
		qCritical() << e.what();

		// For now just exit programe with printing out the error code
		return EXIT_FAILURE;
	}
}
