#include "server.h"

Server::Server()
{
    // Emits a signal when a user connects
    connect(this, SIGNAL(newConnection()),
            this, SLOT(clientConnection()));

    if(!this->listen(QHostAddress::Any, 9999))
        qDebug() << "Server could not start";
    else
        qDebug() << "Server started";
}

/**
 * Handle the connections
 * @brief Server::connectionHandler
 */
void Server::clientConnection()
{
    qDebug() << "New connection";

    // Get next pending connection
    QTcpSocket *socket = this->nextPendingConnection();

    /*socket->write("Hello client\r\n");
    socket->flush();*/

    // Get ready to read
    connect(socket, SIGNAL(disconnected()), this, SLOT(clientDisconnection()));
    connect(socket, SIGNAL(readyRead()),this, SLOT(readClient()));
}

/**
 * Read what the client sent and execute instructions
 * @brief Server::readClient
 */
void Server::readClient()
{
    qDebug() << "readClient";

    kis_contact *client = qobject_cast<kis_contact *>(sender());

    if (!client)
        return;

    QString line;

    // Read what the client sent
    while(client->canReadLine())
    {
        line = client->readLine();
    }

    executeInstructions(line, client);

    connectedUsers.append(client);

}

/**
 * Execute instructions giving a command line
 * @brief Server::executeInstructions
 * @param line
 */
void Server::executeInstructions(QString line, kis_contact *client){
    QString option = line.split("|#|").at(0);
    if (option == "showlistuser" && line.split("|#|").length() >= 1){
        QTextStream flux(client);

        flux << "listuser|#|";

        QListIterator<kis_contact*> iter(connectedUsers);
        while (iter.hasNext()){
            flux << iter.next()->login << "|#|";

        }
        flux << endl;
    }
    else if (option == "adduser" && line.split("|#|").length() >= 3){
        QString login(line.split("|#|").at(1));
        QString password(line.split("|#|").at(2));

        QTextStream flux(client);

        kis_user user(login, password);

        if (user.save())
            flux << "|#|[i]adduser success|#|" << endl;
        else
            flux << "|#|[x]adduser fail"
                    "|#|" << endl;
    }
    else if (option == "signin" && line.split("|#|").length() >= 3){
        QString login(line.split("|#|").at(1));
        QString password(line.split("|#|").at(2));

        QTextStream flux(client);

        if (DBTools::Instance().tryToSignIn(login, password))
            flux << "|#|[i]signin success|#|" << endl;
        else
            flux << "|#|[x]signin fail|#|" << endl;
    }
    else if (line.split("|#|").length() >= 2){
        QString login(line.split("|#|").at(0));
        QString msg(line.split("|#|").at(1));

        //TODO send message (using the HashMap)

        // QTextStream flux(&receiver);
        // flux << login << " : " << msg << endl;
    }
}

/**
 * Handle disconnections
 * @brief Server::clientDisconnection
 */
void Server::clientDisconnection()
{
    kis_contact *client = qobject_cast<kis_contact *>(sender());

    if (!client)
        return;

    connectedUsers.removeAll(client);
    client->deleteLater();
}

Server::~Server()
{

}

