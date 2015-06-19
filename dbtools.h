#include <QSet>
#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <QCoreApplication>
#include <QMessageBox>
#include <QApplication>
#include "user.h"

#ifndef DBTOOLS_H
#define DBTOOLS_H

class DBTools
{
public:
    static DBTools& Instance();
    void loadDatabase();
    QSet<user> listUser;

private:
    DBTools();
    ~DBTools();
    DBTools& operator=(const DBTools&);
    DBTools (const DBTools&);

    static DBTools m_instance;
    QString databasePath;
    bool initDB();
};

#endif // DBTOOLS_H
