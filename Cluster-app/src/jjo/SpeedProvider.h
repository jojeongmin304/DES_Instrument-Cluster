#ifndef SPEEDPROVIDER_H
# define SPEEDPROVIDER_H

# include <QObject>
# include <QTimer>

class SpeedProvider : public QObject {
    Q_OBJECT
	Q_PROPERTY(size_t speed READ speed WRITE setSpeed NOTIFY speedChanged)

public:
	SpeedProvider();
	explicit SpeedProvider(QObject *);
	~SpeedProvider();

	inline size_t speed() const { return _speed;}
	void setSpeed(size_t);

	signals:
		void speedChanged();

private:
	size_t _speed;
};

#endif
 
