#include "kis_user.h"
#include "dbtools.h"

kis_user::kis_user(const QString &_login, const QString &_password) : login(_login), password(_password){
}

bool kis_user::save(){
    bool isUnique = true;
    /*QSet<kis_user>::iterator it;
    for (it = DBTools.Instance().listUser.begin(); it != DBTools.Instance().listUser.end(); it++){
        if (this->login == ((kis_user) *it).login){
            isUnique = false;
            break;
        }
    }

    if (isUnique)
        DBTools.Instance().listUser.insert(this);*/

    return isUnique;
}

kis_user::~kis_user()
{

}

