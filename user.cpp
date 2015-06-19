#include "user.h"
#include "dbtools.h"

user::user(const QString &_login, const QString &_password) : login(_login), password(_password){
}

bool user::save(){
    bool isUnique = true;
    /*QSet<user>::iterator it;
    for (it = DBTools.Instance().listUser.begin(); it != DBTools.Instance().listUser.end(); it++){
        if (this->login == ((user) *it).login){
            isUnique = false;
            break;
        }
    }

    if (isUnique)
        DBTools.Instance().listUser.insert(this);*/

    return isUnique;
}

user::~user()
{

}

