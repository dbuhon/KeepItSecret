#include "kis_user.h"
#include "dbtools.h"

kis_user::kis_user(const QString &_login, const QString &_password) : login(_login), password(_password){
}

bool kis_user::save(){
    DBTools::Instance().addUser(*this);
    // DBTools::Instance().saveDatabase;
    return true;
}

QString kis_user::getLogin() const{
    return this->login;
}

QString kis_user::getPassword() const{
    return this->password;
}

kis_user::~kis_user()
{

}

