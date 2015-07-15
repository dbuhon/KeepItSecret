#include "kis_user.h"
#include "dbtools.h"

UserKIS::UserKIS(const QString &_login, const QString &_password) : login(_login), password(_password){
}

bool UserKIS::save(){
    return DBTools::Instance().addUser(*this);
}

QString UserKIS::getLogin() const{
    return this->login;
}

QString UserKIS::getPassword() const{
    return this->password;
}

UserKIS::~UserKIS()
{

}

