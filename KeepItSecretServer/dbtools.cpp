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
        qryStr = "CREATE TABLE IF NOT EXISTS KIS_USER ( Login varchar(255) NOT NULL PRIMARY KEY, Password varchar(255) NOT NULL)";
        query.prepare(qryStr);
        if(!query.exec(qryStr))
            qDebug() << query.lastError().text();

        qryStr = "CREATE TABLE IF NOT EXISTS KIS_LOG ( ID INTEGER PRIMARY KEY AUTOINCREMENT, EncryptedMessage text NOT NULL, Date varchar(100), Sender varchar(255) NOT NULL, Receiver varchar(255) NOT NULL, FOREIGN KEY (Sender) REFERENCES KIS_USER(login), FOREIGN KEY (Receiver) REFERENCES KIS_USER(login))";
        query.prepare(qryStr);
        if(!query.exec(qryStr))
            qDebug() << query.lastError().text();

        qryStr = "CREATE TABLE IF NOT EXISTS KIS_CONTACT (Contact varchar(255) NOT NULL, User varchar(255) NOT NULL, PRIMARY KEY (Contact,User), FOREIGN KEY (Contact) REFERENCES KIS_USER(login), FOREIGN KEY (User) REFERENCES KIS_USER(login))";
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

bool DBTools::insertLog(const QString &encryptedMessage, const QString &date, const QString &sender, const QString &receiver) const{
    QString qryStr;
    QSqlQuery query(myDB);

    if (!userExistsInKIS_USER(sender) || !userExistsInKIS_USER(receiver) || sender.compare(receiver) == 0)
        return false;

    qryStr = "INSERT INTO KIS_LOG ( EncryptedMessage, Date, Sender, Receiver ) VALUES ( '" + encryptedMessage + "', '" + date + "', (SELECT Login FROM KIS_USER WHERE Login='" + sender + "'), (SELECT Login FROM KIS_USER WHERE Login='" + receiver + "'))";
    query.prepare(qryStr);
    if(!query.exec(qryStr))
    {
        qDebug() << query.lastError().text();
        return false;
    }

    return true;
}

QStringList DBTools::getLogs(const QString &sender, const QString &receiver) const{
    QStringList listLogs;

    QString qryStr;
    QSqlQuery query(myDB);
    qryStr = "SELECT Sender, Date, EncryptedMessage FROM KIS_LOG WHERE Sender='" + sender + "' AND Receiver='" + receiver + "' LIMIT 50";
    query.prepare(qryStr);

    if(!query.exec(qryStr))
    {
        qDebug() << query.lastError().text();
    }
    else
    {
        // TODO : FIX THIS TREATMENT
        query.next();
        for (int i = 0; i < query.size(); i++)
            listLogs.append(query.value(i).toString());
    }

    return listLogs;
}

bool DBTools::insertContact(const QString &contact, const QString &login) const{
    QString qryStr;
    QSqlQuery query(myDB);

    if (!userExistsInKIS_USER(contact) || !userExistsInKIS_USER(login) || contact.compare(login) == 0)
        return false;

    qryStr = "INSERT INTO KIS_CONTACT ( Contact, User ) VALUES ( (SELECT Login FROM KIS_USER WHERE Login='" + contact + "'), (SELECT Login FROM KIS_USER WHERE Login='" + login + "'))";
    query.prepare(qryStr);
    if(!query.exec(qryStr))
    {
        qDebug() << query.lastError().text();
        return false;
    }

    /*
    qryStr = "INSERT INTO KIS_CONTACT ( Contact, User ) VALUES ( (SELECT Login FROM KIS_USER WHERE Login='" + login + "'), (SELECT Login FROM KIS_USER WHERE Login='" + contact + "'))";
    query.prepare(qryStr);
    if(!query.exec(qryStr))
    {
        qDebug() << query.lastError().text();
        return false;
    }
    */

    return true;
}

bool DBTools::userExistsInKIS_USER(const QString &user) const{
    QString qryStr;
    QSqlQuery query(myDB);

    qryStr="SELECT COUNT(*) FROM KIS_USER WHERE Login='" + user + "'";
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

bool DBTools::isAContact(const QString &contact, const QString &user) const{
    QString qryStr;
    QSqlQuery query(myDB);

    qryStr="SELECT COUNT(*) FROM KIS_CONTACT WHERE Contact='" + contact + "' AND User='" + user + "'";
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
        // TODO : FIX THIS TREATMENT
        query.next();
        for (int i = 0; i < query.size(); i++)
            listContacts.append(query.value(i).toString());
    }

    return listContacts;
}

QString DBTools::getSecret(QString &login){
    QString qryStr;
    QSqlQuery query(myDB);
    qryStr = "SELECT Password FROM KIS_USER WHERE Login = '" + login + "'";
    query.prepare(qryStr);
    if(!query.exec(qryStr))
    {
        qDebug() << query.lastError().text();
    }
    else
    {
        query.next();
        return query.value(0).toString();
    }
    return nullptr;
}

DBTools::~DBTools()
{
}
