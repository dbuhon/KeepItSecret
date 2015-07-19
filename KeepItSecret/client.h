#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);
    ~Client();

    void sendMessage(QString login, QString date, QString msg);
    void sendCommand(QString command);
    void addUser(QString login, QString password);
    void addContact(QString contact);
    void tryToSignIn(QString login, QString password);
    void showUsers();

    QTcpSocket* getSocket();
    QString login;
    QStringList listUsers;

Q_SIGNALS:
    void signinSignal(bool isOk);
    void addUserSignal(bool isAdded);
    void addContactSignal(bool isAdded);
    void populateListContactsSignal();

public slots:
    void readyToRead();
    void disconnection();

private:
    QTcpSocket *socket;
};

#endif // CLIENT_H
