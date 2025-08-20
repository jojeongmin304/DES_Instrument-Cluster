#ifndef SPEEDPROVIDER_H
# define SPEEDPROVIDER_H

# include <QObject>
# include <QTimer>

class SpeedProvider : public QObject {
    Q_OBJECT
	Q_PROPERTY(int speed READ speed WRITE setSpeed NOTIFY speedChanged)

public:
	SpeedProvider();
	explicit SpeedProvider(QObject *);
	~SpeedProvider();

	inline int speed() const { return _speed;}
	void setSpeed(int);

	signals:
		void speedChanged();

private:
	int _speed;
};

#endif
 
