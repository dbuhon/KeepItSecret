#include <QTcpSocket>

#ifndef CONTACT_H
#define CONTACT_H


class kis_contact : public QTcpSocket
{
public:
    kis_contact();
    ~kis_contact();
    QString login;
    bool save();

};

#endif // CONTACT_H
