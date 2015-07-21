#include <QStringList>
#include <QList>
#include <QTcpSocket>
#include <QListIterator>
#include <QMap>
#include <QTextEdit>
//#include <functional>

#ifndef OPTIONS_H
#define OPTIONS_H

//typedef void (*actionHandler)(const QString&);

class Options
{
public:
    Options(QTcpSocket *_client, QList<QTcpSocket *> *_connectedUsers, QTextEdit *_logger);
    ~Options();
    bool option_showusers;
    bool option_adduser;
    bool option_addcontact;
    bool option_signin;
    bool option_message;
    bool option_getlogs;

    bool loggedin;
    QTcpSocket *client;
    QList<QTcpSocket *> *connectedUsers;
    //QMap<QString, actionHandler> dictionaryActions;

    void parseLine(const QString &line);
    void sendContactListToClients();
    void sendUserListToClients();

private:
    QTextEdit *logger;
    void treatmentShowUsers(const QString &line);
    void treatmentGetLogs(const QString &line);
    void treatmentAddUser(const QString &line);
    void treatmentAddContact(const QString &line);
    void treatmentSignIn(const QString &line);
    void treatmentMessage(const QString &line);
};

#endif // OPTIONS_H
