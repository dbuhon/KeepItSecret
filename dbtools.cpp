#include "dbtools.h"

DBTools DBTools::m_instance=DBTools();

DBTools::DBTools()
{
    if (initDB())
        loadDatabase();
    else qDebug() << "ECHEC LORS DE L INITIALISATION DE LA BASE DE DONNEES : INITDB";
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
    QSqlDatabase myDB = QSqlDatabase::addDatabase("QSQLITE");

    if(!myDB.isValid())
    {
        // This shows a message Box if Database Connection Fails.
        QString str;
    }

    myDB.setDatabaseName(this->databasePath);
    //myDB.setUserName("username");
    //myDB.setPassword("password");
    if (!myDB.open())
    {
        // This shows a message if System cannot Open created Database
    }

    else
    {
        /*QString qryStr;
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
        }*/
        QApplication::restoreOverrideCursor();
    }
}


bool DBTools::addUser(const kis_user &user){
    bool isUnique = true;
    for (auto it : listUser){
        if (((kis_user)it).getLogin() == user.getLogin())
            isUnique = false;
    }

    if (isUnique)
        listUser.push_back(user);

    return isUnique;
}

bool DBTools::tryToSignIn(const QString &login, const QString &password) const{
    for (auto it : listUser){
        if (((kis_user)it).getLogin() == login && ((kis_user)it).getPassword() == password)
            return true;
    }
    return false;
}

DBTools::~DBTools()
{
}
