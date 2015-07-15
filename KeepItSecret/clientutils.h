#include "client.h"

#ifndef CLIENTUTILS_H
#define CLIENTUTILS_H


class ClientUtils
{
public:
    static ClientUtils& Instance();
    Client *client;

private:
    ClientUtils();
    ~ClientUtils();
    ClientUtils& operator=(const ClientUtils&);
    ClientUtils (const ClientUtils&);

    static ClientUtils m_instance;

};

#endif // CLIENTUTILS_H
