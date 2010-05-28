#include <iostream>
#include <vector>
#include <string>
#include "GpsPoint.h"
#include "DateManipulator.h"

/*
 *
 *
 *
 */
int main(int argc, char** argv)
{
	// TODO Würde ich vermutlich per 'argv' übergeben!?								<--
	// Reference values must be set from anywhere.
	double latitude = 0.0;
	double longitude = 0.0;
	std::string timestamp = "2010-02-09T10:39:05Z";

	// TODO Ebenfalls aus 'argv' lesen.												<--
	// Setup all names we want to manipulate.
	std::vector<std::string> names;
	names.push_back("rajko");
	names.push_back("peter");
	names.push_back("tobi");

	// Refernce GpsPoint.
	GpsPoint reference;
	reference.setGpsPoint(latitude, longitude, 0.0, timestamp, "unused");

	// Read a set of gps points for a specific person and manipulate 
	// all its timestamps according the given reference gps point.
	// TODO Je nach Aufwand könnte man pro Person einen Thread starten!?			<--
	for (unsigned int i = 0; i < names.size(); i++)
	{
		// Get set of GPS points for that specific person.
		// ... std::vector<GpsPoint> points = ...

		// 
		DateManipulator dm;
		//dm.manipulate(refernce, points);
	}

	return 0;
}
