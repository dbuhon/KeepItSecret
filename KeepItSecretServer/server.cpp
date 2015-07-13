#include "server.h"

Server::Server()
{
    // Emits a signal when a user connects
    connect(this, SIGNAL(newConnection()),
            this, SLOT(newConnection()));

    if(!this->listen(QHostAddress::Any, 9999))
        qDebug() << "Server could not start";
    else
        qDebug() << "Server started";
}

void Server::newConnection()
{
    // Get next pending connection
    QTcpSocket *socket = this->nextPendingConnection();

    // Message from client
    connect(client, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
    connect(socket, SIGNAL(readyRead()),this, SLOT(readClient()));
}

void Server::readClient()
{
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());

        if (!client)
            return;

    QString line;

    while(client->canReadLine())
    {
        line = client->readLine();
    }

    QString option = line.split("|#|").at(0);

    if (option == "adduser" && line.split("|#|").length() >= 3){
        QString login(ligne.split("|#|").at(1);
        QString password(ligne.split("|#|").at(2);

        // TODO dbtools add user to db

        QTextStream flux(&client);
        flux << "User added to the database" << endl;
    }
    else if (option == "signin" && line.split("|#|").length() >= 2){
        QString login(ligne.split("|#|").at(1);
        QString password(ligne.split("|#|").at(2);

        // TODO dbtools try to signin

        QTextStream flux(&client);
        flux << "User logged in" << endl;
    }
    else if (line.split("|#|").length() >= 2){
        QString login(ligne.split("|#|").at(1);
        QString msg(lign.split("|#|").at(2));

        // TODO send message (through HashMap)

        // QTextStream flux(&receiver);
        //flux << ligne << endl;

    }
    clientConnections.append(client);

}

void Server::clientDisconnected()
{
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());

    if (!client)
        return;

    clientConnections.removeAll(client);
    client->deleteLater();
}

Server::~Server()
{

}


