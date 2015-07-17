#include "server.h"

#define SEPARATOR "[|#|]"

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
 * Handle client connections
 * @brief Server::connectionHandler
 */
void Server::clientConnection()
{
    qDebug() << "A new client arrived !";

    // Get next pending connection
    QTcpSocket *socket = this->nextPendingConnection();

    QTextStream flux(socket);
    flux << "You are now connected to the server." << endl;

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
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());

    if (!client)
        return;

    QString line;

    // Read what the client sent
    while(client->canReadLine())
    {
        line = client->readLine();
        executeInstructions(line, client);
    }
}

/**
 * Execute instructions giving a command line
 * @brief Server::executeInstructions
 * @param line
 */
void Server::executeInstructions(QString line, QTcpSocket *client){
    qDebug() << line;

    QString option = line.split(SEPARATOR).at(0);

    // Commands that need to be logged in first
    if (connectedUsers.contains(client)){
        /**
          * The client asked for the list of connected users
          */
        if (option == "*SHOWUSERS*" && line.split(SEPARATOR).length() == 2){

            QTextStream flux(client);
            flux << "*SHOWUSERS*" << SEPARATOR;

            QListIterator<QTcpSocket*> iter(connectedUsers);
            while (iter.hasNext()){
                flux << iter.next()->objectName() << SEPARATOR;
            }
            flux << endl;
        }
        /**
          * The client asked to send a message
          */
        else if (option == "*MSG*" && line.split(SEPARATOR).length() >= 3){

            QString login(line.split(SEPARATOR).at(1));
            QString msg(line.split(SEPARATOR).at(2));

            qDebug() << "A message was sent";

            //TODO send message (using the HashMap)

            // QTextStream flux(&receiver);
            // flux << login << " : " << msg << endl;
        }
    }


    // Command that can be executed without being logged in

    /**
      * The client asked for a connection
      */
    if (option == "*SIGNIN*" && line.split(SEPARATOR).length() == 3){

        QString login(line.split(SEPARATOR).at(1));
        QString password(line.split(SEPARATOR).at(2));

        QTextStream flux(client);

        // Try to log in
        if (DBTools::Instance().tryToSignIn(login, password)){
            flux << "*SIGNIN*" << SEPARATOR << "OK" << SEPARATOR << login << SEPARATOR << endl;
            client->setObjectName(login);
            connectedUsers.append(client);

            sendNewUserListToClients();
        }
        else
            flux << "*SIGNIN*" << SEPARATOR << "NOK" << SEPARATOR << SEPARATOR << endl;
    }
    /**
      * The client asked for the server to add in its database a user
      */
    else if (option == "*ADDUSER*" && line.split(SEPARATOR).length() == 3){

        QString login(line.split(SEPARATOR).at(1));
        QString password(line.split(SEPARATOR).at(2));

        // User creation
        UserKIS user(login, password);

        QTextStream flux(client);

        // Try to save in the database
        if (user.save())
            flux << "*ADDUSER*" << SEPARATOR << "OK" << endl;
        else
            flux << "*ADDUSER*" << SEPARATOR << "NOK" << endl;
    }
}

/**
 * Handle client disconnection
 * @brief Server::clientDisconnection
 */
void Server::clientDisconnection()
{
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());

    if (!client)
        return;

    connectedUsers.removeAll(client);
    client->deleteLater();

    sendNewUserListToClients();
}

Server::~Server()
{

}

/**
 * Send to the clients the new list of connectedUsers
 * @brief Server::sendNewUserList
 */
void Server::sendNewUserListToClients(){
    QListIterator<QTcpSocket*> iter(connectedUsers);
    while (iter.hasNext()){
        QTextStream flux(iter.next());

        flux << "*SHOWUSERS*" << SEPARATOR;
        QListIterator<QTcpSocket*> it(connectedUsers);
        while (it.hasNext()){
            flux << it.next()->objectName() << SEPARATOR;
        }
        flux << endl;
    }
}

