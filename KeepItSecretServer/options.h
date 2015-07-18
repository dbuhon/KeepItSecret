#include <QStringList>
#include <QList>
#include <QTcpSocket>
#include <QListIterator>
#include <QMap>

#ifndef OPTIONS_H
#define OPTIONS_H


class Options
{
public:
    Options(QTcpSocket *_client, QList<QTcpSocket *> *_connectedUsers);
    ~Options();
    bool option_showusers;
    bool option_adduser;
    bool option_addcontact;
    bool option_signin;
    bool option_message;

    bool loggedin = false;
    QTcpSocket *client;
    QList<QTcpSocket *> *connectedUsers;
    //QMap<QString, QString> dictionaryCommands;

    void parseLine(const QString &line);
    void sendContactListToClients();
    void sendUserListToClients();

private:
    void treatmentShowUsers(const QString &line);
    void treatmentAddUser(const QString &line);
    void treatmentAddContact(const QString &line);
    void treatmentSignIn(const QString &line);
    void treatmentMessage(const QString &line);
};

#endif // OPTIONS_H
