#ifndef VIEWMODEL_H
# define VIEWMODEL_H

# include "BatteryMonitor.h"

# include <QObject>
# include <QTimer>
# include <QByteArray>

# define WHEEL_DIAMETER 6.8 // CM
# define PI 3.1415

enum canID_e {
	ID_RPM = 0x10,
};

class ViewModel : public QObject {
	/* QT FRAMEWORK */
	Q_OBJECT
	Q_PROPERTY(int capacity READ capacity NOTIFY updateCapacity)
	Q_PROPERTY(int speed READ speed NOTIFY updateSpeed)

	public slots:  
		void receiveTimeout(const std::string&);
		void receiveCanData(int, const QByteArray&);

	signals:
		void updateCapacity();
		void updateSpeed();

	/* CLASS */
	public:
		explicit ViewModel(QObject* parent = nullptr);
		~ViewModel();

		int capacity() const { return _capacity; } 
		int speed() const { return _speed; } 

	private:
		BatteryMonitor _battery;
		int _capacity = 0;

		int _speed = 0; // Centimeters per second
		
		int _int(const QByteArray&, int) const;
		// float _float(const QByteArray&, size_t) const;
		// bool _bool(const QByteArray&, size_t) const;
};

#endif
