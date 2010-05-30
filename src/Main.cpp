/*==========================================================
 Copyright (c) avp::ptr, 2010
 ==========================================================*/

/*
Alright, here are some things we should check if errors occur.  ;)

1. I'm not really careful by converting a date-string into single integers.
I just assume that the date-string looks always the same... but that might
not be the case.

2. Maybe, we could have a timezone issue, by converting the timestamps
into the unix time. But, if the reference gpspoint is within the same
timezone, it should work.
The reason I use the unix time anyway is, that it makes time calculations
easier if you don't have to handle a 'normal' time format.
*/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "GpsPoint.h"
#include "DateManipulator.h"
#include "DBconnector.h"

/**
 * Print usage informations to console.
 */
void printUsage(std::string& exe)
{
	std::cout << "\nUsage: " << exe << " [database] [latitude] [longitude] [timestamp] [name]" << std::endl;
	std::cout << "   database          db.sqlite" << std::endl;
	std::cout << "   latitude          52.5018387" << std::endl;
	std::cout << "   longitude         13.4338551" << std::endl;
	std::cout << "   timestamp         1989-11-20T17:15:25Z" << std::endl;
	std::cout << "   name              usernames for db entry" << std::endl;

	std::cout << "\nCopyright (c) avp::ptr, 2010 \n" << std::endl;
}

/**
 * Read all settings from command line arguments.
 *	[1] database name
 *	[2] reference latitude
 *	[3] reference longitude
 *	[4] reference timestamp
 *	[5] ..[N] names to change
 */
int main(int argc, char** argv)
{
	// Predefine all informations.
//	std::string dbName = "res/db3.sqlite";							// database name
	std::string dbName = "db.sqlite";							// database name
	double refLatitude = 52.5018387;							// reference latitude
	double refLongitude = 13.4338551;							// reference longitude
	std::string refTimestamp = "1989-11-20T17:15:25Z";			// reference timestamp
	std::vector<std::string> names;								// 0..N names to change

	// -------------------------------------------------------------
	// Comment it out here, if you don't want to use runtime args.
	// But, take care that you set up the names-vector by yourself.
	//
//    names.push_back("Sophia");
	// Get runtime informations.
	std::string executable(argv[0]);
	int i = executable.find_last_of('/');
	if (i < 0) i = executable.find_last_of('\\');
	std::string exName = executable.substr(i + 1);
	std::string exPath = executable.substr(0, i);
	// Check for usage problems.
	if (argc == 2)
	{
		std::string str(argv[1]);
		if (str == "--help" || str == "/?")
		{
			printUsage(exName);
			return 0;
		}
	}
	// Check for missing command line arguments.
	if (argc < 6)
	{
		std::cerr << "Error: Missing command line argumenst." << std::endl;
		printUsage(exName);
		return 1;
	}

	// Read database name from command line.
	if (argc >= 2) dbName = argv[1];
	// Read reference coordinates from command line.
	if (argc >= 4)
	{
		std::stringstream ssLatitude(argv[2]);
		ssLatitude >> refLatitude;
		std::stringstream ssLongitude(argv[3]);
		ssLongitude >> refLongitude;
	}
	// Read reference timestamp from command line.
	if (argc >= 5) refTimestamp = argv[4];
	// Read names from command line.
	for (int i = 5; i < argc; i++)
	{
		names.push_back(argv[i]);
	}

	// -------------------------------------------------------------

	// Create refernce GpsPoint.
	GpsPoint refGpsPoint;
	refGpsPoint.setGpsPoint(0, refLatitude, refLongitude, 0.0, refTimestamp);
	// Print it.
	std::cout << "Reference GPS point:" << std::endl;
	std::cout << refGpsPoint << "\n" << std::endl;

	// Read a set of gps points for a specific person and manipulate
	// all its timestamps according the given reference gps point.
	for (unsigned int i = 0; i < names.size(); i++)
	{
		// Statistics
		std::cout << "" << std::endl;
		std::cout << "Username: " << names.at(i) << std::endl;
		std::cout << "> Reading from database ... ";

		// Get set of GPS points for that specific person.
		std::vector<GpsPoint> points;
		DBconnector dbConnector(dbName);
		dbConnector.setupDbConnection();
		dbConnector.getGpsPoints(points, names.at(i));

		// Some more statistics.
		std::cout << "[done]" << std::endl;
		std::cout << "GPS points: " << points.size() << std::endl;
		std::cout << "> Manipulating timestamps ... ";

		// Manipuate all timestamps.
		DateManipulator dm;
		dm.manipulate(refGpsPoint, points);

		// Some more statistics.
		std::cout << "[done]" << std::endl;
		std::cout << "Closest point: " << dm.getClosestGpsPoint() << std::endl;

		// Write back into db.
		std::cout << "> Writing back into database ... ";
		dbConnector.setGpsPointsTimestamp(points);
		dbConnector.closeDbConnection();
		std::cout << "[done]" << std::endl;
	}

	// Bye.
	std::cout << "\nAlright, I guess I am done." << std::endl;
	return 0;
}


