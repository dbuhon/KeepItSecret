#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <dbtools.h>
#include <kis_user.h>
#include <kis_contact.h>

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
    void executeInstructions(QString line, kis_contact *contact);

private:
    QList<kis_contact *> connectedUsers;
    QMap<kis_contact*, kis_contact*> conversations;
};

#endif // SERVER_H
