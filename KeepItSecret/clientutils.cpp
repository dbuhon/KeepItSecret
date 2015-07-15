#include "clientutils.h"

ClientUtils ClientUtils::m_instance=ClientUtils();

ClientUtils &ClientUtils::Instance()
{
    return m_instance;
}

ClientUtils::ClientUtils()
{
    client = new Client;
}

ClientUtils::~ClientUtils()
{

}
