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
 * Handle the connections
 * @brief Server::connectionHandler
 */
void Server::clientConnection()
{
    qDebug() << "A new client arrived !";

    // Get next pending connection
    QTcpSocket *socket = this->nextPendingConnection();

    QTextStream flux(socket);
    flux << "Hello client!" << endl;

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
    // TODO faire fonctionner avec kis_contact
    //kis_contact *client = qobject_cast<kis_contact *>(sender());
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());

    if (!client)
        return;

    QString line;

    // Read what the client sent
    while(client->canReadLine())
    {
        line = client->readLine();

        qDebug() << line;
        //executeInstructions(line, client);
    }


}

/**
 * Execute instructions giving a command line
 * @brief Server::executeInstructions
 * @param line
 */
void Server::executeInstructions(QString line, kis_contact *client){
    QString option = line.split(SEPARATOR).at(0);

    // Need to be logged in
    if (connectedUsers.contains(client)){

        if (option == "*showlistuser*" && line.split(SEPARATOR).length() >= 1){

            QTextStream flux(client);
            flux << "*listuser*" << SEPARATOR;

            QListIterator<kis_contact*> iter(connectedUsers);
            while (iter.hasNext()){
                flux << iter.next()->login << SEPARATOR;
            }
            flux << endl;
        }
        // Send message
        else if (line.split(SEPARATOR).length() >= 2){
            QString login(line.split(SEPARATOR).at(0));
            QString msg(line.split(SEPARATOR).at(1));

            qDebug() << "A message was sent";

            //TODO send message (using the HashMap)

            // QTextStream flux(&receiver);
            // flux << login << " : " << msg << endl;
        }
    }
    else{
        if (option == "*signin*" && line.split(SEPARATOR).length() >= 3){
            QString login(line.split(SEPARATOR).at(1));
            QString password(line.split(SEPARATOR).at(2));

            QTextStream flux(client);

            // Try to log in
            if (DBTools::Instance().tryToSignIn(login, password)){
                flux << "*[i]signin success*" << endl;
                client->login = login;
                connectedUsers.append(client);
            }
            else
                flux << "*[x]signin fail*" << endl;
        }

        else if (option == "*adduser*" && line.split(SEPARATOR).length() >= 3){
            QString login(line.split(SEPARATOR).at(1));
            QString password(line.split(SEPARATOR).at(2));

            // User creation
            kis_user user(login, password);

            QTextStream flux(client);

            // Try to save in the database
            if (user.save())
                flux << "*[i]adduser success*" << endl;
            else
                flux << "*[x]adduser fail*" << endl;
        }
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

