#include "kis_contact.h"

kis_contact::kis_contact()
{

}

kis_contact::kis_contact(const QString &_login, const QTcpSocket &_socket){
    this->login = _login;
    this->socket = _socket;
}

bool kis_contact::save(){

}

QString kis_contact::getLogin() const{
    return this->login;
}

QTcpSocket kis_contact::getSocket() const{
    return this->socket;
}

kis_contact::~kis_contact()
{

}
