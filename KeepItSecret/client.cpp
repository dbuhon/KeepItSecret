#include "client.h"
#include <QTextStream>
#include <QHostAddress>

Client::Client(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket();
    socket->connectToHost(QHostAddress::LocalHost, 9999);
    connect(socket, SIGNAL(readyToRead()), this, SLOT(readyToRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
}

void Client::readyToRead()
{
    QString line;
    while(socket->canReadLine())
    {
        line = socket->readLine();
        qDebug() << line << endl;
    }

    QTextStream flux(socket);
    flux << line << endl;
}

void Client::sendMessage(QString login, QString msg){
    QTextStream flux(socket);
    flux << login << "|#|" << msg << endl;
}

void Client::sendCommand(QString option, QString login, QString password)
{
    QTextStream flux(socket);
    flux << option << "|#|" << login << "|#|" << password << endl;
}

void Client::disconnect()
{
    socket->deleteLater();
    exit(0);
}

Client::~Client()
{

}
