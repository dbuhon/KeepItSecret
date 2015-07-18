#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include "dbtools.h"
#include "kis_user.h"
#include "kis_socket.h"
#include <QTextEdit>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server(QTextEdit *_logger);
    ~Server();

public slots:
    void clientConnection();
    void readClient();
    void clientDisconnection();

private:
    QTextEdit* logger;
    QList<QTcpSocket *> connectedUsers;
    QMap<QTcpSocket*, QTcpSocket*> conversations;
    void executeInstructions(QString line, QTcpSocket *contact);
    void sendNewUserListToClients();
    void sendContactListToClients();
};

#endif // SERVER_H
