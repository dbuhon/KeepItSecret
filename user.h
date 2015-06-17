#include <QString>
#ifndef USER_H
#define USER_H

class user
{
public:
    user(const QString &_login, const QString &_password);
    bool save();
    ~user();

private:
    QString login;
    QString password;
};

#endif // USER_H
