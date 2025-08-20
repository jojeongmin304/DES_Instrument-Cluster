#ifndef CANRECEIVER_H
# define CANRECEIVER_H

# include "error.h"

# include <unistd.h>
# include <sys/socket.h>
# include <sys/ioctl.h>
# include <net/if.h>
# include <cstring>

# include <linux/can.h>
# include <linux/can/raw.h>

# include <QThread>
# include <QDebug>

# define WHEEL_DIAMETER 6.8 // cm
# define PI 3.1415

enum canID_e {
	ID_SPEED = 0x10
};

class CANReceiver : public QThread {
    Q_OBJECT
    Q_PROPERTY(int speed READ speed NOTIFY newSpeed)

	public:
		struct CANSocket {
			int socket;
			ifreq ifr;
			sockaddr_can addr;

			std::string name;
			
			CANSocket() : socket(-1), ifr(), addr(), name() {
				std::memset(&addr, 0, sizeof(addr));
			}
		};

		CANReceiver() = delete;
		explicit CANReceiver(QObject *);
		CANReceiver(const std::string&);
		~CANReceiver();
		
		inline int speed() const { return _speed; }
		
	protected:
		// When QThread starts, this function runs in a separate thread.
		void run() override;
		
	private:
		struct CANSocket _can;
		
		bool _isRunning; 
		size_t _speed = 0;
		
		void _init();
		void _initDomainSocket();
		void _initCanInterface();
		void _initBind();

		void _runHandleData(const can_frame&);
	
	signals:
		// This signal is emitted when a new speed value is received.
		void newSpeed(size_t);
};

#endif
