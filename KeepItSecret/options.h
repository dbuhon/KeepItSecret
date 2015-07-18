#include <QStringList>
#include <QList>
#include <QTcpSocket>
#include <QListIterator>
#include <QMap>
#include "client.h"

#ifndef OPTIONS_H
#define OPTIONS_H


class Options
{
public:
    Options(Client *_client);
    ~Options();
    bool option_showusers;
    bool option_adduser;
    bool option_addcontact;
    bool option_signin;
    bool option_message;
    //QMap<QString, QString> dictionaryCommands;

    void parseLine(const QString &line);

private:
    Client *client;
    void treatmentShowUsers(const QString &line);
    void treatmentAddUser(const QString &line);
    void treatmentAddContact(const QString &line);
    void treatmentSignIn(const QString &line);
    void treatmentMessage(const QString &line);
};

#endif // OPTIONS_H
