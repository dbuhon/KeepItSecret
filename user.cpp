#include "user.h"

user::user(const QString &_login, const QString &_password) : login(_login), password(_password){
}

bool user::save(){
    // TODO Vérification n'existe pas déjà
    // TODO Implementation persistance, serialization
    // QFile, QVariant, QSqlite ?
    return false;
}

user::~user()
{

}

