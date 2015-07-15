#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include "dbtools.h"
#include "kis_user.h"
#include "kis_socket.h"

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server();
    ~Server();
public slots:
    void clientConnection();
    void readClient();
    void clientDisconnection();
    void executeInstructions(QString line, SocketKIS *contact);

private:
    QList<SocketKIS *> connectedUsers;
    QMap<SocketKIS*, SocketKIS*> conversations;
};

#endif // SERVER_H
