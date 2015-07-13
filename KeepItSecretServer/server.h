#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class Server : public QTcpServer
{

public:
    Server();
    ~Server();
public slots:
    void newConnection();
    void readClient();
    void clientDisconnection();
    void executeInstructions(QString line);

private:
    QList<QTcpSocket *> clientConnections;
    QMap<QTcpSocket*, QTcpSocket*> conversations;
};

#endif // SERVER_H
