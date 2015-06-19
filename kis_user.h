#include <QString>
#include <QFile>
#include <QFileInfo>

#ifndef KIS_USER_H
#define KIS_USER_H

class kis_user
{
public:
    kis_user(const QString &_login, const QString &_password);
    bool save();
    ~kis_user();

private:
    QString login;
    QString password;
};

#endif // KIS_USER_H
