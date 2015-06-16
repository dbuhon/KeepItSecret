#include "user.h"

user::user()
{

}

user::user(const char*& _login, const char*& _password1, const char*& _password2){
    if (_password1 != _password2)
        return;

    this->login = _login;
    this->password = _password;
}

user::save(){
    // TODO Implementation persistance, serialization
    // QFile, QVariant, QSqlite ?
}

user::~user()
{

}

