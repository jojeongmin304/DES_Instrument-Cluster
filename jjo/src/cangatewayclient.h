#ifndef CANGATEWAYCLIENT_H
#define CANGATEWAYCLIENT_H

#include <QObject>
#include <QVariantList>

class CanGatewayClient : public QObject
{
    Q_OBJECT
public:
    explicit CanGatewayClient(QObject *parent = nullptr);

public slots:
    // This slot will contain the main loop and run in the background thread.
    void process();

signals:
    // This signal is emitted when a new message is successfully parsed.
    void messageReceived(int id, int dlc, const QVariantList &data, double timestamp);
    // A signal to report errors.
    void errorOccurred(const QString &errorString);
    // A signal to indicate the connection is finished.
    void finished();
};

#endif // CANGATEWAYCLIENT_H