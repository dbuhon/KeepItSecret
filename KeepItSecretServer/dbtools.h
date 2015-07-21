#include <QSet>
#include <QtSql>
#include <QFileInfo>
#include <QCoreApplication>
#include <QSetIterator>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "kis_user.h"
#include "kis_log.h"

#ifndef DBTOOLS_H
#define DBTOOLS_H

class DBTools
{
public:
    static DBTools& Instance();
    bool loadDatabase();
    bool addUser(const UserKIS &user);
    bool tryToSignIn(const QString &login, const QString &password) const;
    bool insertContact(const QString &contact, const QString &login) const;
    QStringList getContacts(QString &login);
    bool userExistsInKIS_USER(const QString &user) const;
    bool isAContact(const QString &contact, const QString &user) const;
    QString getSecret(QString &login);
    bool insertLog(const QString &encryptedMessage, const QString &date, const QString &sender, const QString &receiver) const;
    QList<LogKIS> getLogs(const QString &partner, const QString &receiver) const;
private:
    DBTools();
    ~DBTools();
    DBTools& operator=(const DBTools&);
    DBTools (const DBTools&);

    static DBTools m_instance;
    QSqlDatabase myDB;
};

#endif // DBTOOLS_H
