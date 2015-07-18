#include "client.h"
#include <QTextStream>
#include <QHostAddress>
#include <QDebug>
#include "options.h"

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
        Options options(this);
        options.parseLine(line);
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

/**
 * Ask the server to add a contact to this user
 * @brief Client::addContact
 * @param contact
 */
void Client::addContact(QString contact){
    QTextStream flux(socket);
    flux << "*ADDCONTACT*" << SEPARATOR << contact << SEPARATOR << endl;
}

QTcpSocket *Client::getSocket()
{
    return this->socket;
}

