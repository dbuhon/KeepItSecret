#include "dbtools.h"

DBTools DBTools::m_instance=DBTools();

DBTools::DBTools()
{
}

DBTools::~DBTools()
{
}

DBTools& DBTools::Instance(){
    return m_instance;
}
