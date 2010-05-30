/*==========================================================
 Copyright (c) avp::ptr, 2010
 ==========================================================*/

#ifndef _DBCONNECTOR_H_
#define _DBCONNECTOR_H_

#include <string>
#include <vector>
#include "GpsPoint.h"

#include "sqlite3x.hpp"
using namespace sqlite3x;

using namespace std;

class DBconnector
{
public:
    DBconnector(const string& databasePath);
    ~DBconnector();

	void setupDbConnection();
	void closeDbConnection();
    bool getGpsPoints(vector<GpsPoint>& gpsPoints, string username);
    bool setGpsPointsTimestamp(vector<GpsPoint>& gpsPoints);

private:

    string m_databasePath;
	sqlite3_connection* m_dbconn;

};

#endif // _DBCONNECTOR_H_
