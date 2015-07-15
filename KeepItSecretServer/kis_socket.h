#include <QTcpSocket>
#include <QObject>

#ifndef KIS_SOCKET_H
#define KIS_SOCKET_H


class SocketKIS : public QTcpSocket
{
    Q_OBJECT
public:
    SocketKIS();
    ~SocketKIS();
    QString login;
};

#endif // KIS_SOCKET_H
