#include <QTcpSocket>

#ifndef CONTACT_H
#define CONTACT_H


class kis_contact : public QTcpSocket
{
public:
    kis_contact();
    ~kis_contact();

    kis_contact(const QString &_login, const QTcpSocket &_socket);
    bool save();
    QString getLogin() const;
    QTcpSocket getSocket() const;

public:
    QString login;
};

#endif // CONTACT_H
