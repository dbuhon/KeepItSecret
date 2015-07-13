#include "client.h"
#include <QTextStream>

Client::Client(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket();
    socket.connectToHost(serverAddr, 9999);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

}



void Client::readyRead()
{
    QString ligne;
    while(socket.canReadLine()) // tant qu'il y a quelque chose à lire dans la socket
    {
        ligne = socket.readLine();

        QString ps = ligne.split("|").at(0);

        if (ps == "add"){
            // TODO dbtools add user

            QTextStream flux(&client);
            flux << "Add ok" << endl;
        }
        else if (ps == "signin"){
            // TODO dbtools try to signin

            QTextStream flux(&client);
            flux << "Sign in ok" << endl;
        }
        else{
            // send message
            // TOTO nvoyer au destinataire ds la hasmap
           // QTextStream flux(&destinataire);
            //flux << ligne << endl;

        }

        qDebug() << ligne;
    }
    QTextStream flux(&socket);
    flux << ligne << endl;
}

void Client::disconnected()
{
    qDebug() << socketDescriptor << " Disconnected";


    socket->deleteLater();
    exit(0);
}

Client::~Client()
{

}

void Client::sendMessage(QString login, QString msg){
    QTextStream flux(&socket);
    flux << login << " : " << msg << endl;
}

void Client::sendSpecificMessage(QString type, QString login, QString password)
{
    QTextStream flux(&socket);
    flux << type << "|" << login << "|" << password << endl;
}
