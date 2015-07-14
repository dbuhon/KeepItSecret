#include <QTcpSocket>
#include <QObject>

#ifndef CONTACT_H
#define CONTACT_H


class kis_contact : public QTcpSocket
{
    Q_OBJECT
public:
    kis_contact();
    ~kis_contact();
    QString login;
    bool save();

};

#endif // CONTACT_H
