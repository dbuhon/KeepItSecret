#include <QSet>
#include <QMainWindow>
#include <QtSql>
#include <QFileInfo>
#include <QCoreApplication>
#include <QApplication>
#include <QSetIterator>
#include "kis_user.h"

#ifndef DBTOOLS_H
#define DBTOOLS_H

class DBTools
{
public:
    static DBTools& Instance();
    void loadDatabase();
    bool addUser(const kis_user &user);
    bool tryToSignIn(const QString &login, const QString &password) const;

private:
    DBTools();
    ~DBTools();
    DBTools& operator=(const DBTools&);
    DBTools (const DBTools&);

    static DBTools m_instance;
    std::list<kis_user> listUser;
    QString databasePath;
    bool initDB();
};

#endif // DBTOOLS_H
