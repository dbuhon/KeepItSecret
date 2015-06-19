#include <QSet>
#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <QCoreApplication>
#include <QMessageBox>
#include <QApplication>
#include <QSet>
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

private:
    DBTools();
    ~DBTools();
    DBTools& operator=(const DBTools&);
    DBTools (const DBTools&);

    static DBTools m_instance;
    QSet<kis_user> listUser;
    QString databasePath;
    bool initDB();
};

#endif // DBTOOLS_H
