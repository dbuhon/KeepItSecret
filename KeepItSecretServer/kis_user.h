#include <QObject>
#include <QString>
#include <QFile>
#include <QFileInfo>

#ifndef KIS_USER_H
#define KIS_USER_H

class UserKIS
{
public:
    UserKIS(const QString &_login, const QString &_password);
    bool save();
    QString getLogin() const;
    QString getPassword() const;
    ~UserKIS();

private:
    QString login;
    QString password;
};

#endif // KIS_USER_H
