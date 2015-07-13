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
    void sendSpecificMessage(QString type, QString login, QString password);

    ~Client();

signals:

public slots:
    void readyRead();
    void disconnected();

private:
    QTcpSocket *socket;
};

#endif // CLIENT_H
