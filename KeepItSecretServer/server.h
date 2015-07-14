#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <dbtools.h>
#include <kis_user.h>
#include <contact.h>

class Server : public QTcpServer
{

public:
    Server();
    ~Server();
public slots:
    void newConnection();
    void readClient();
    void disconnected();
    void executeInstructions(QString line, Contact* contact);

private:
    QList<Contact*> clientConnections;
    QMap<Contact*, Contact*> conversations;
};

#endif // SERVER_H
