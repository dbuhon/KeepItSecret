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

/**
 * Handle the connections
 * @brief Server::connectionHandler
 */
void Server::newConnection()
{
    qDebug() << "New connection";

    // Get next pending connection
    QTcpSocket *socket = this->nextPendingConnection();

    socket->write("Hello client\r\n");
    socket->flush();

    // Get ready to read
    connect(socket, SIGNAL(readyRead()),this, SLOT(readClient()));
}

/**
 * Read what the client sent and execute instructions
 * @brief Server::readClient
 */
void Server::readClient()
{
    qDebug() << "readClient";

    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());

    if (!client)
        return;

    QString line;

    // Read what the client sent
    while(client->canReadLine())
    {
        line = client->readLine();
    }

    executeInstructions(line, client);

<<<<<<< HEAD
    // TEST TO CHANGE
    Contact *c = new Contact("test_login", *client);
    clientConnections.append(c);
=======
    clientConnections.append(client);
>>>>>>> master
}

/**
 * Execute instructions giving a command line
 * @brief Server::executeInstructions
 * @param line
 */
void Server::executeInstructions(QString line, QTcpSocket *client){
    QString option = line.split("|#|").at(0);
    if (option == "showlistuser" && line.split("|#|").length() >= 1){
        QTextStream flux(&*client);

        flux << "listuser|#|";
<<<<<<< HEAD

        QListIterator<Contact*> iter(clientConnections);
        while (iter.hasNext()){
            flux << iter.next()->getLogin() << "|#|";
=======
        for (Contact c : clientConnections){
            flux << c.getLogin() << "|#|";
>>>>>>> master
        }
        flux << endl;
    }
    else if (option == "adduser" && line.split("|#|").length() >= 3){
        QString login(line.split("|#|").at(1));
        QString password(line.split("|#|").at(2));

        QTextStream flux(&*client);

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

        QTextStream flux(&*client);

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
void Server::disconnected()
{
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());

    if (!client)
        return;

<<<<<<< HEAD
    // TEST TO CHANGE
    Contact *c = new Contact("test_login", *client);

    clientConnections.removeAll(c);
=======
    clientConnections.removeAll(client);
>>>>>>> master
    client->deleteLater();
}

Server::~Server()
{

}
