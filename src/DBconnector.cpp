/*==========================================================
 Copyright (c) avp::ptr, 2010
 ==========================================================*/

#include "DBconnector.h"

#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>
using namespace std;

#include "sqlite3x.hpp"
using namespace sqlite3x;

// --------------------------------------------------------------------------------------
#define CATCHDBERRORS																	\
	catch(exception &ex)																\
	{																					\
		cout << "Database error: " << ex.what() << endl;	                            \
	}																					\
// --------------------------------------------------------------------------------------

DBconnector::DBconnector(const string& databasePath)
:
m_databasePath(databasePath)
{
    //ctor
}

DBconnector::~DBconnector()
{
    //dtor
}


bool DBconnector::getGpsPoints(vector<GpsPoint>& gpsPoints, string username)
{
    bool result = false;
    string query = "SELECT a.gpsdataid AS gpsdataid, a.latitude AS latitude, \
                    a.longitude AS longitude, a.time AS time, \
                    a.elevation AS elevation, b.name AS name \
                    FROM gpsdata AS a \
                    JOIN user AS b ON (a.user = b.userid) \
                    WHERE name = '";
    query += username;
    query += "';";

    try
    {
        sqlite3_connection con(m_databasePath.c_str());

        sqlite3_command cmd(con, query.c_str());
		sqlite3_reader reader=cmd.executereader();

		while(reader.read())
		{
            GpsPoint gpsPoint;

            gpsPoint.setGpsPoint(reader.getint(0),
                                 reader.getdouble(1),
                                 reader.getdouble(2),
                                 reader.getdouble(4),
                                 reader.getstring(3));

            gpsPoints.push_back(gpsPoint);
		}
        con.close();
        result = true;
    }
    CATCHDBERRORS
    return result;
}

bool DBconnector::setGpsPointsTimestamp(vector<GpsPoint>& gpsPoints)
{
    bool result = false;
    try
    {
        sqlite3_connection con(m_databasePath.c_str());

        sqlite3_transaction trans(con);
        {
            for(unsigned int i = 0; i < gpsPoints.size(); ++i)
            {
				stringstream ss;
				ss << gpsPoints[i].getGpsPointId();

                string query = "UPDATE gpsdata \
                                SET time = '";
                query += gpsPoints[i].getTimestamp();
                query += "' WHERE gpsdataid = '";
				query += ss.str();
                query += "';";
                sqlite3_command cmd(con, query.c_str());
                cmd.executenonquery();
            }
        }
        trans.commit();
        con.close();
        result = true;
    }
    CATCHDBERRORS
    return result;
}
