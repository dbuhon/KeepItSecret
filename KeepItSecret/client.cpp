#include "client.h"
#include <QTextStream>
#include <QHostAddress>
#include <QDebug>
#include "options.h"
#include "cryptoutils.h"

#define SEPARATOR "[|#|]"

Client::Client(QObject *parent) : QObject(parent)
{
    QString address = "192.168.1.252";

    socket = new QTcpSocket();
    //socket->connectToHost(QHostAddress::LocalHost, 9999);
    socket->connectToHost(address, 22);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyToRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnection()));
}

/**
 * Action performed when the client disconnects
 * @brief Client::disconnection
 */
void Client::disconnection()
{
    socket->deleteLater();
    exit(0);
}

Client::~Client()
{

}

/**
 * Action performed when tu client has something to read from its socket
 * @brief Client::readyToRead
 */
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

/**
 * Send a command
 * @brief Client::sendCommand
 * @param command
 */
void Client::sendCommand(QString command)
{
    QTextStream flux(socket);
    flux << command << endl;
}

/**
 * Send a message through the server
 * @brief Client::sendMessage
 * @param login
 * @param date
 * @param msg
 */
void Client::sendMessage(QString login, QString date, QString msg){
    QTextStream flux(socket);
    flux << "*MSG*" << SEPARATOR << login << SEPARATOR << date << SEPARATOR << msg << SEPARATOR << endl;
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
 * Ask the server to return the history of conversation with the partner
 * @brief Client::askLogs
 * @param partner
 */
void Client::askLogs(QString partner){
    QTextStream flux(socket);
    flux << "*GETLOGS*" << SEPARATOR << partner << SEPARATOR << endl;
}

/**
 * Ask the server if the giving login and password are correct to log in
 * @brief Client::tryToSignIn
 * @param login
 * @param password
 */
void Client::tryToSignIn(QString login, QString password){
    CryptoUtils crypto;
    this->secretKey = crypto.getSecretKey(password);

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

/**
 * Returns the socket
 * @brief Client::getSocket
 * @return
 */
QTcpSocket *Client::getSocket()
{
    return this->socket;
}

