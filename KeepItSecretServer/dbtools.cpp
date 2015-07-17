#include "dbtools.h"

DBTools DBTools::m_instance=DBTools();

DBTools::DBTools()
{
    if (!loadDatabase())
       qDebug() << "[x]Error" << "Cannot load the database";
}

DBTools& DBTools::Instance(){
    return m_instance;
}

bool DBTools::loadDatabase(){
    myDB = QSqlDatabase::addDatabase("QSQLITE");
    myDB.setDatabaseName("mydb");

    if (!myDB.open())
    {
        qDebug() << "[x]Error" << "Cannot open the database";
        return false;
    }
    else
    {
        qDebug() << "[i]Success" << "Database opened";


        QString qryStr;
        QSqlQuery query(myDB);
        qryStr = "CREATE TABLE IF NOT EXISTS KIS_USER ( Login varchar(255) PRIMARY KEY, Password varchar(255) )";
        query.prepare(qryStr);
        if(!query.exec(qryStr))
            qDebug() << query.lastError().text();

        qryStr = "CREATE TABLE IF NOT EXISTS KIS_CONTACT (Contact varchar(255), User varchar(255), FOREIGN KEY (Contact) REFERENCES KIS_USER(login), FOREIGN KEY (User) REFERENCES KIS_USER(login))";
        query.prepare(qryStr);
        if(!query.exec(qryStr))
            qDebug() << query.lastError().text();


    }
    return true;
}

bool DBTools::addUser(const UserKIS &user){
    QString qryStr;
    QSqlQuery query(myDB);
    qryStr = "INSERT INTO KIS_USER ( Login, Password ) VALUES ('" + user.getLogin() + "', '" + user.getPassword() + "')";
    query.prepare(qryStr);
    if(!query.exec(qryStr))
    {
        qDebug() << query.lastError().text();
        return false;
    }

    return true;
}

bool DBTools::insertContact(const QString &contact, const QString &login) const{
    QString qryStr;
    QSqlQuery query(myDB);
    qryStr = "INSERT INTO KIS_CONTACT ( Contact, User ) VALUES ('" + contact + "', '" + login + "')";
    query.prepare(qryStr);
    if(!query.exec(qryStr))
    {
        qDebug() << query.lastError().text();
        return false;
    }

    return true;
}

bool DBTools::tryToSignIn(const QString &login, const QString &password) const{
    QString qryStr;
    QSqlQuery query(myDB);
    qryStr = "SELECT COUNT(*) FROM KIS_USER WHERE Login = '" + login + "' AND Password = '" + password + "'";
    query.prepare(qryStr);
    if(!query.exec(qryStr))
    {
        qDebug() << query.lastError().text();
        return false;
    }
    else
    {
        query.next();
        if(query.value(0).toInt() == 0)
            return false;
    }
    return true;
}

QStringList DBTools::getContacts(QString &login){
    QStringList listContacts;

    QString qryStr;
    QSqlQuery query(myDB);
    qryStr = "SELECT DISTINCT Contact FROM KIS_CONTACT WHERE Login = '" + login + "'";
    query.prepare(qryStr);
    if(!query.exec(qryStr))
    {
        qDebug() << query.lastError().text();
    }
    else
    {
        query.next();
            listContacts.append(query.value(0).toString());
    }

    return listContacts;
}

DBTools::~DBTools()
{
}
