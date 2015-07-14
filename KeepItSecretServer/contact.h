#include <QTcpSocket>

#ifndef CONTACT_H
#define CONTACT_H


class Contact : public QTcpSocket
{
public:
    Contact();
    ~Contact();

    Contact(const QString &_login, const QTcpSocket &_socket);
    bool save();
    QString getLogin() const;
    QTcpSocket getSocket() const;

public:
    QString login;
};

#endif // CONTACT_H
