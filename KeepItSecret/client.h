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
    QString login;

Q_SIGNALS:
    void signinSignal(bool isOk);
    void addUserSignal(bool isOk);

public slots:
    void readyToRead();
    void disconnection();
    void readInstructions(QString line);

private:
    QTcpSocket *socket;
    QList<QString> listUsers;
};

#endif // CLIENT_H
