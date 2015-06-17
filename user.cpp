#include "user.h"

user::user(const QString &_login, const QString &_password) : login(_login), password(_password), id(){
    this->id = id.createUuid();
}

bool user::save(){
    // TODO save
    return false;
}

user::~user()
{

}

