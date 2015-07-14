#include "contact.h"

Contact::Contact()
{

}

Contact::Contact(const QString &_login, const QTcpSocket &_socket){
    this->login = _login;
    this->socket = _socket;
}

bool Contact::save(){

}

QString Contact::getLogin() const{
    return this->login;
}

QTcpSocket Contact::getSocket() const{
    return this->socket;
}

Contact::~Contact()
{

}
