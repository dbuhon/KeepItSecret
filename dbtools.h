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
    DBTools Instance();
    void loadDatabase();

    QSet<user> listUser;

private:
    DBTools();
    ~DBTools();

    static DBTools m_instance;
    bool initDB();
    QString databasePath;
};

#endif // DBTOOLS_H
