/*==========================================================
 Copyright (c) avp::ptr, 2010
 ==========================================================*/

#ifndef _DBCONNECTOR_H_
#define _DBCONNECTOR_H_

#include <string>
#include <vector>
#include "GpsPoint.h"

using namespace std;

class DBconnector
{
public:
    DBconnector(const string& databasePath);
    ~DBconnector();

    bool getGpsPoints(vector<GpsPoint>& gpsPoints, string username);
    bool setGpsPointsTimestamp(vector<GpsPoint>& gpsPoints);

private:

    string m_databasePath;

};

#endif // _DBCONNECTOR_H_
