#include "client.h"
#include <QTextStream>
#include <QHostAddress>
#include <QDebug>

#define SEPARATOR "[|#|]"

Client::Client(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket();
    socket->connectToHost(QHostAddress::LocalHost, 9999);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyToRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnection()));
}

void Client::disconnection()
{
    socket->deleteLater();
    exit(0);
}

Client::~Client()
{

}

void Client::readyToRead()
{
    QString line;

    while(socket->canReadLine())
    {
        line = socket->readLine();
        readInstructions(line);
    }
}

void Client::readInstructions(QString line){
    qDebug() << line;

    QString option = line.split(SEPARATOR).at(0);


    // Get the result of SHOWUSERS command and fil the listUsers with it
    if (line.split(SEPARATOR).length() >= 1 && option == "*SHOWUSERS*"){
        this->listUsers.clear();
        if (this->login.isEmpty()) return;

        for (int i = 1; i < line.split(SEPARATOR).length() - 1; i++){
            QString user = line.split(SEPARATOR).at(i);

            if (this->login.compare(user) != 0)
                this->listUsers.append(user);
        }
        emit populateListContactsSignal();
    }


    // Get the result of SIGNIN command
    else if (line.split(SEPARATOR).length() == 4 && option == "*SIGNIN*"){
        QString result = line.split(SEPARATOR).at(1);
        QString login = line.split(SEPARATOR).at(2);

        if (result == "OK"){
           this->login = login;
           emit signinSignal(true);
        }
        else {
            emit signinSignal(false);
         }
    }


    // Get the result of ADDUSER command
    else if (line.split(SEPARATOR).length() == 3 && option == "*ADDUSER*"){
        QString result = line.split(SEPARATOR).at(1);

         if (result == "OK"){
            emit addUserSignal(true);
         }
         else {
             emit addUserSignal(false);
         }
    }

    // Get the result of ADDCONTACT command
    else if (line.split(SEPARATOR).length() == 3 && option == "*ADDCONTACT*"){
        QString result = line.split(SEPARATOR).at(1);

         if (result == "OK"){
            emit addContactSignal(true);
         }
         else {
             emit addContactSignal(false);
         }
    }

    else if (line.split(SEPARATOR).length() >= 2 && option == "*MSG*"){
        QString login = line.split(SEPARATOR).at(1);
        QString msg = line.split(SEPARATOR).at(2);

        // TRAITEMENT
    }

    else{
        QTextStream flux(socket);
        flux << line << endl;
    }
}

void Client::sendMessage(QString login, QString msg){
    QTextStream flux(socket);
    flux << "*MSG*" << SEPARATOR << login << SEPARATOR << msg << endl;
}

void Client::sendCommand(QString command)
{
    QTextStream flux(socket);
    flux << command << endl;
}

/**
 * Ask the server to add in its database a user
 * @brief Client::addUser
 * @param login
 * @param password
 */
void Client::addUser(QString login, QString password){
    QTextStream flux(socket);
    flux << "*ADDUSER*" << SEPARATOR << login << SEPARATOR << password << SEPARATOR << endl;
}

/**
 * Ask the server if the giving login and password are correct to log in
 * @brief Client::tryToSignIn
 * @param login
 * @param password
 */
void Client::tryToSignIn(QString login, QString password){
    QTextStream flux(socket);
    flux << "*SIGNIN*" << SEPARATOR << login << SEPARATOR << password << SEPARATOR << endl;
}

/**
 * Ask the server to return a list which contains all the connected users
 * @brief Client::showUsers
 */
void Client::showUsers(){
    QTextStream flux(socket);
    flux << "*SHOWUSERS*" << SEPARATOR << endl;
}

void Client::addContact(QString contact){
    QTextStream flux(socket);
    flux << "*ADDCONTACT*" << SEPARATOR << contact << SEPARATOR << endl;
}

QStringList Client::getUsers()
{
    return this->listUsers;
}






