#include <QtSql/QSqlDatabase>

#ifndef DBTOOLS_H
#define DBTOOLS_H


class DBTools
{
public:
    static DBTools& Instance();

private:
    DBTools& operator=(const DBTools&){}
    DBTools (const DBTools&){}

    static DBTools m_instance;
    DBTools();
    ~DBTools();
};

#endif // DBTOOLS_H
