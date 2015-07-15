#include "client.h"
#include <QTextStream>
#include <QHostAddress>
#include <QDebug>

#define SEPARATOR "[|#|]"

Client::Client(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket();
    socket->connectToHost(QHostAddress::Any, 9999);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyToRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnection()));
}

void Client::readyToRead()
{
    QString line;
    while(socket->canReadLine())
    {
        line = socket->readLine();
        qDebug() << line << endl;
    }

    // Fill the listUsers with users connected to the server
    if (line.split(SEPARATOR).length() >= 1 && line.split(SEPARATOR).at(0) == "listuser"){
        for (int i = 0; i < line.split(SEPARATOR).length(); i++){
            this->listUsers.append(line.split(SEPARATOR).at(i));
        }
    }
    else{
        QTextStream flux(socket);
        flux << line << endl;
    }
}

void Client::sendMessage(QString login, QString msg){
    QTextStream flux(socket);
    flux << login << SEPARATOR << msg << endl;
}

void Client::sendCommand(QString option, QString login, QString password)
{
    QTextStream flux(socket);
    flux << "*" << option << "*" << SEPARATOR << login << SEPARATOR << password << endl;
}

void Client::disconnection()
{
    socket->deleteLater();
    exit(0);
}

Client::~Client()
{

}
