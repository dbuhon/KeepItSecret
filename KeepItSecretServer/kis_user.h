#include <QString>
#include <QFile>
#include <QFileInfo>
#include <kis_contact.h>

#ifndef KIS_USER_H
#define KIS_USER_H

class kis_user
{
public:
    kis_user(const QString &_login, const QString &_password);
    bool save();
    QString getLogin() const;
    QString getPassword() const;
    ~kis_user();

private:
    QString login;
    QString password;    
    QList<kis_contact*> contacts;
};

#endif // KIS_USER_H
