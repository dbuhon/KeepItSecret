#include <QSet>
#include <QMainWindow>
#include <QtSql>
#include <QFileInfo>
#include <QCoreApplication>
#include <QApplication>
#include <QSetIterator>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "client.h"
#include "kis_user.h"

#ifndef DBTOOLS_H
#define DBTOOLS_H

class DBTools
{
public:
    static DBTools& Instance();
    bool loadDatabase();
    bool addUser(const UserKIS &user);
    bool tryToSignIn(const QString &login, const QString &password) const;

private:
    DBTools();
    ~DBTools();
    DBTools& operator=(const DBTools&);
    DBTools (const DBTools&);

    static DBTools m_instance;
    QSqlDatabase myDB;
};

#endif // DBTOOLS_H
