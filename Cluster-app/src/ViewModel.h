#ifndef VIEWMODEL_H
# define VIEWMODEL_H

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
	Q_PROPERTY(int speed READ speed NOTIFY updateSpeed)

	public slots:  
		void receiveData(int, const QByteArray&);

	signals:
		void updateSpeed();

	/* CLASS */
	public:
		explicit ViewModel(QObject* parent = nullptr);
		~ViewModel();

		int speed() const { return _speed; } 

	private:
		int _speed; // Centimeters per second
		
		int _int(const QByteArray&, int) const;
		// float _float(const QByteArray&, size_t) const;
		// bool _bool(const QByteArray&, size_t) const;
};

#endif
