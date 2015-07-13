#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);
    void sendMessage(QString login, QString msg);
    void sendCommand(QString option, QString login, QString password);
    ~Client();

public slots:
    void readyToRead();
    void disconnect();

private:
    QTcpSocket *socket;
};

#endif // CLIENT_H
