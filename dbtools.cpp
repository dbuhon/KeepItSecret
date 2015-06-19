#include "dbtools.h"

DBTools DBTools::m_instance=DBTools();

DBTools::DBTools()
{
    initDB();
}

DBTools& DBTools::Instance(){
    return m_instance;
}

bool DBTools::initDB(){
    // Find if database exists
    QString tmpString = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    QFileInfo databaseFileInfo(QString("%1/%2").arg(tmpString).arg("mydb"));
    this->databasePath = databaseFileInfo.absoluteFilePath();

    if (!databaseFileInfo.exists())
    {
        bool copySuccess = QFile::copy(QString("assets:/mydb"), this->databasePath);

        if (!copySuccess)
        {
            this->databasePath.clear();
            return false;
        }
    }
    return true;
}

void DBTools::loadDatabase(){
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    QMessageBox mb;
    QSqlDatabase myDB = QSqlDatabase::addDatabase("QSQLITE");

    if(!myDB.isValid())
    {
        // This shows a message Box if Database Connection Fails.
        QString str;
        str = this->databasePath;
        str.prepend(" Cannot Add database ");
        mb.setText(str);
        mb.exec();
    }

    myDB.setDatabaseName(this->databasePath);
    //myDB.setUserName("username");
    //myDB.setPassword("password");
    if (!myDB.open())
    {
        // This shows a message if System is unable to Open created Database
        mb.setText(" Cannot open database  ");
        mb.exec();
    }

    else
    {
        QString qryStr;
        QSqlQuery query(myDB);
        qryStr = QString("SELECT Id,  Name, Description FROM Table1");
        query.prepare(qryStr);
        if(!query.exec(qryStr)){
            mb.setText(query.lastError().text());
            mb.exec();
        }
        else
        {
            while(query.next())
            {
                mb.setText(QString("\nId:%1  Name:%2  Desc:%3")
                    .arg(query.value("Id").toString())
                    .arg(query.value("Name").toString())
                    .arg(query.value("Description").toString()));
                mb.exec();
            }
        }
        QApplication::restoreOverrideCursor();
    }
}


bool DBTools::addUser(const kis_user &user){
    bool isUnique = true;
    QSetIterator<kis_user> it(listUser);
    while (it.hasNext()){
        if (user.getLogin() == it.next().getLogin()){
            isUnique = false;
            break;
        }
    }

    if (isUnique)
        listUser.insert(user);

    return isUnique;
}

DBTools::~DBTools()
{
}
