#include "InstrumentCluster.h"

#include <QQmlContext>
#include <QFile>
#include <QDebug>

/* CON & DESTRUCTOR */
InstrumentCluster::InstrumentCluster(int argc, char** argv)
: _app(std::make_unique<QGuiApplication>(argc, argv)),
  _engine(std::make_unique<QQmlApplicationEngine>()) {}

InstrumentCluster::~InstrumentCluster() {
	for (const auto& pair : _threads) {
		closeGateway(pair.first);
	}
}

/* METHODS */
bool InstrumentCluster::openGateway(const std::string& ifname) {
	try {
		if (_findGateway(ifname)) {
			qWarning() << "[IC] Gateway for" << QString::fromStdString(ifname) << "already exists";
			return true;
		}
		
		// Instanciate gateway
		_gateways.emplace_back(new CANGateway(ifname));

		// Instanciate thread and move the gateway worker to thread
		_threads[ifname] = QThread_ptr(new QThread);
		_gateways.back()->moveToThread(_threads[ifname].get());

		// Set signals
		_openGatewaySetSignals(_gateways.back(), _threads[ifname], ifname);

		// Let the worker begin :)
		_threads[ifname]->start();
		
		qInfo() << "[IC] CAN Gateway opened for interface:" << QString::fromStdString(ifname);
		return true;
		
	} catch (const std::exception& e) {
		qCritical() << "[IC] Failed to open gateway for" << QString::fromStdString(ifname) << ":" << e.what();
		
		auto it = _threads.find(ifname);
		if (it != _threads.end()) {
			_threads.erase(it);
		}
		return false;
	}
}

void InstrumentCluster::_openGatewaySetSignals(InstrumentCluster::CANGateway_ptr& gateway, 
	                                           InstrumentCluster::QThread_ptr& thread, const std::string& ifname) {
	// Connect thread management signals
	QObject::connect(thread.get(), &QThread::started, gateway.get(), &CANGateway::start);
	QObject::connect(gateway.get(), &CANGateway::finished, thread.get(), &QThread::quit);

	// Connect status signals
	QObject::connect(gateway.get(), &CANGateway::connected, [ifname]() {
		qInfo() << "[IC] CAN Gateway activated:" << QString::fromStdString(ifname);
	});
	QObject::connect(gateway.get(), &CANGateway::disconnected, [ifname]() {
		qInfo() << "[IC] CAN Gateway deactivated:" << QString::fromStdString(ifname);
	});
	
	// Connect error handling
	QObject::connect(gateway.get(), &CANGateway::error, [ifname](const QString& error) {
		qCritical() << "[IC] CAN Gateway error on" << QString::fromStdString(ifname) << ":" << error;
	});
}

void InstrumentCluster::closeGateway(const std::string& ifname) {
	const auto& gateway = _findGateway(ifname);
	if (!gateway) {
		qWarning() << "[IC] No gateway found for CAN interface:" << QString::fromStdString(ifname);
		return;
	}

	// Stop the gateway
	gateway->stop();

	// Handle thread cleanup
	auto it = _threads.find(ifname);
	if (it != _threads.end()) {
		const auto& thread = it->second;

		if (thread->isRunning()) {
			thread->quit();
			thread->wait(CLOSE_WAIT);
			
			if (thread->isRunning()) {
				qWarning() << "[IC] Thread for" << QString::fromStdString(ifname) 
				           << "did not stop gracefully, terminating...";
				thread->terminate();
				thread->wait(FORCE_WAIT);
			}
		}
		_threads.erase(it);
	}

	_gateways.remove_if([&ifname](const CANGateway_ptr& ptr) {
		return ptr && ptr->ifname == ifname;
	});

	qInfo() << "[IC] CAN Gateway closed for interface:" << QString::fromStdString(ifname);
}

/* FUTURE: Implement a method to check if a gateway is connected */
// bool InstrumentCluster::isGatewayConnected(const std::string& interface) const {
// 	const auto& gateway = _findGateway(interface);
// 	return gateway && gateway->isConnected();
// }

// FUTURE: Implement a method to list all connected gateways
// std::vector<std::string> InstrumentCluster::getConnectedGateways() const {
// 	std::vector<std::string> connectedGateways;
// 	for (const auto& gateway : _gateways) {
// 		if (gateway && gateway->isConnected()) {
// 			connectedGateways.push_back(gateway->interfaceName());
// 		}
// 	}
// 	return connectedGateways;
// }

void InstrumentCluster::connectModel(const std::string& interface, ViewModel& model) {
	const auto& gateway = _findGateway(interface);
	if (!gateway) {
		qWarning() << "No gateway found for CAN interface:" << QString::fromStdString(interface);
		return;
	}
	
	// Connect the single newData signal to ViewModel's receiveData slot
	QObject::connect(gateway.get(), &CANGateway::newData, &model, &ViewModel::receiveData, Qt::QueuedConnection);
	qInfo() << "[IC] Connected CAN Gateway" << QString::fromStdString(interface) << "to ViewModel.";
}

void InstrumentCluster::registerModel(const std::string& ifname, ViewModel* model) {
	_engine->rootContext()->setContextProperty(QString::fromStdString(ifname), model);
	qInfo() << "[IC] ViewModel registered as:" << QString::fromStdString(ifname);
}

void InstrumentCluster::loadQML(const std::string& qmlEntry) {
	const QUrl url(QString::fromStdString(qmlEntry));
	if (!url.isValid() || url.isEmpty()) {
		qCritical() << "[IC] QML entry path is invalid:" << QString::fromStdString(qmlEntry);
		return;
	}

	if (url.isLocalFile()) {
		if (!QFile::exists(url.toLocalFile())) {
			qCritical() << "[IC] QML file does not exist at path:" << url.toLocalFile();
			return;
		}
	}

	QObject::connect(_engine.get(), &QQmlApplicationEngine::objectCreated, _app.get(),
		[url](QObject *obj, const QUrl &objUrl) {
			if (!obj && url == objUrl) 
				QCoreApplication::exit(EXIT_FAILURE);
		},
		Qt::QueuedConnection);
	
	_engine->load(url);
	qInfo() << "[IC] QML file loaded:" << QString::fromStdString(qmlEntry);
}

int InstrumentCluster::run() {
	return _app->exec();
}

const InstrumentCluster::CANGateway_ptr& InstrumentCluster::_findGateway(const std::string& interface) const {
	for (const auto& gateway : _gateways) {
		if (gateway && gateway->ifname == interface) {
			return gateway;
		}
	}
	// Return a null reference - this will be checked by the caller
	static CANGateway_ptr nullPtr;
	return nullPtr;
}


