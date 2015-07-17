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
    void sendMessage(QString login, QString msg);
    void sendCommand(QString command);
    ~Client();
    void addUser(QString login, QString password);
    void tryToSignIn(QString login, QString password);
    void showUsers();
    QStringList getUsers();
    QString login;

Q_SIGNALS:
    void signinSignal(bool isOk);
    void addUserSignal(bool isAdded);
    void populateListContactsSignal();

public slots:
    void readyToRead();
    void disconnection();
    void readInstructions(QString line);

private:
    QTcpSocket *socket;
    QStringList listUsers;
};

#endif // CLIENT_H
