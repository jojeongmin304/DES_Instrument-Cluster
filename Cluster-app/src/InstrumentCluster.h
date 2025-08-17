#ifndef INSTRUMENTCLUSTER_H
# define INSTRUMENTCLUSTER_H

# include "CANGateway.h"
# include "ViewModel.h"

# include <string>
# include <list>
# include <vector>
# include <unordered_map>

# include <QGuiApplication>
# include <QQmlApplicationEngine>
# include <QThread>

class InstrumentCluster {
	public:
		InstrumentCluster() = delete;
		InstrumentCluster(int, char**);
		~InstrumentCluster();
		
		bool openGateway(const std::string&);
		void closeGateway(const std::string&);
		// bool isGatewayConnected(const std::string&) const;
		// std::vector<std::string> getConnectedGateways() const; 
		
		void connectModel(const std::string&, ViewModel&);
		void registerModel(const std::string&, ViewModel*);
		void loadQML(const std::string&);
		
		int run();
	
	private:
		/**
		 * @brief A custom deleter for std::unique_ptr to safely delete QObjects across threads.
		 *
		 * This deleter replaces the default `delete` call with `QObject::deleteLater()`.
		 * `deleteLater()` is thread-safe and posts a `DeferredDelete` event to
		 * the object's event loop, ensuring safe deletion on the correct thread.
		 */
		struct QObjectDeleter {
			void operator()(QObject* obj) const {
				if (obj) {
					obj->deleteLater();
				}
			}
		};

		template <typename T>
		using u_ptr = std::unique_ptr<T>;

		template <typename T, typename Deleter = QObjectDeleter>
		using u_ptr_d = std::unique_ptr<T, Deleter>;

		using QThread_ptr = u_ptr<QThread>;
		using CANGateway_ptr = u_ptr_d<CANGateway, QObjectDeleter>;

		u_ptr<QGuiApplication> _app;
		u_ptr<QQmlApplicationEngine> _engine;

		std::unordered_map<std::string, QThread_ptr> _threads;
		std::list<u_ptr_d<CANGateway, QObjectDeleter>> _gateways;

		void _openGatewaySetSignals(CANGateway_ptr&, QThread_ptr&, const std::string&);
		const CANGateway_ptr& _findGateway(const std::string&) const;
};

#endif
