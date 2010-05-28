/*==========================================================
 Copyright (c) avp::ptr, 2010
 ==========================================================*/

#ifndef _DBCONNECTOR_H_
#define _DBCONNECTOR_H_

#include <string>

using namespace std;

class DBconnector
{
public:
    DBconnector(const string& databasePath);
    ~DBconnector();

    void setupDatabaseConnection();

    void closeDatabaseConnection();
private:

    string m_databasePath;

};

#endif // _DBCONNECTOR_H_
