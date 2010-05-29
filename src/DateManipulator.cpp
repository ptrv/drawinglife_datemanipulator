/*==========================================================
 Copyright (c) avp::ptr, 2010
 ==========================================================*/

#include "DateManipulator.h"
#include <sstream>
#include <limits>
#include <cmath>
#include <ctime>

void DateManipulator::manipulate(const GpsPoint& reference, std::vector<GpsPoint>& points)
{
	std::vector<GpsPoint>::iterator point = getClosestPoint(reference, points);
	this->setTimestamps(reference, points.begin(), points.end(), point);
}

std::vector<GpsPoint>::iterator DateManipulator::getClosestPoint(const GpsPoint& reference,
		std::vector<GpsPoint>& points)
{
	double rLat = reference.getLatitude();
	double rLon = reference.getLongitude();
	double dist = std::numeric_limits<double>::max();
	std::vector<GpsPoint>::iterator closest;
	std::vector<GpsPoint>::iterator it = points.begin();
	std::vector<GpsPoint>::iterator end = points.end();
	while (it != end)
	{
		double deltaLat = it->getLatitude() - rLat;
		double deltaLon = it->getLongitude() - rLon;
		double distance = deltaLat * deltaLat + deltaLon * deltaLon;
		if (distance < dist)
		{
			dist = distance;
			closest = it;
		}
		++it;
	}

	return closest;
}

void DateManipulator::setTimestamps(const GpsPoint& reference,
		std::vector<GpsPoint>::iterator begin,
		std::vector<GpsPoint>::iterator end,
		std::vector<GpsPoint>::iterator point)
{
	// Get refence time in unix-time.
	time_t refTimestamp = getUnixTime(reference.getTimestamp());
	// Get current time in unix-time.
	time_t curTimestamp = getUnixTime(point->getTimestamp());

	// Change all timestamps before the current point.
	std::vector<GpsPoint>::iterator it = begin;
	while (it < point)
	{		
		time_t timestamp = getUnixTime(it->getTimestamp());
		time_t delta = curTimestamp - timestamp;
		time_t newTimestamp = refTimestamp - delta;
		it->setTimestamp(this->getTimestamp(newTimestamp));		
		++it;
	}

	// Change all timestamps after the current point.
	it = point + 1;
	while (it < end)
	{		
		time_t timestamp = getUnixTime(it->getTimestamp());
		time_t delta = timestamp - curTimestamp;
		time_t newTimestamp = refTimestamp + delta;
		it->setTimestamp(this->getTimestamp(newTimestamp));
		++it;
	}

	// Change timestamp of the current point itself.
	point->setTimestamp(reference.getTimestamp());
}

time_t DateManipulator::getUnixTime(const std::string& d)
{
	int year, month, day, hour, minute, second;
	// Split given date.
	std::string date = d.substr(0, d.find('T'));
	std::string time = d.substr(d.find('T') + 1, 8);
	// Return value.
	DateTokens dt;
	// Split date.
	std::stringstream(date.substr(0,  4)) >> year;		// 2010
	std::stringstream(date.substr(5,  7)) >> month;		// 02
	std::stringstream(date.substr(8, 10)) >> day;		// 09
	// Split time.
	std::stringstream(time.substr(0, 2)) >> hour;		// 10
	std::stringstream(time.substr(3, 5)) >> minute;		// 39
	std::stringstream(time.substr(6, 8)) >> second;		// 05
	tm t;
	t.tm_year = year - 1900;
	t.tm_mon = month;
	t.tm_mday = day;
	t.tm_hour = hour + 1;
	t.tm_min = minute;
	t.tm_sec = second;
	return mktime(&t);
}

std::string DateManipulator::getTimestamp(const time_t& uTime)
{	
	tm* time = gmtime(&uTime);	
	
	std::stringstream date;
	// Year
	date << (time->tm_year + 1900);
	date << "-";
	// Month
	if (time->tm_mon < 10) date << 0;
	date << time->tm_mon;
	date << "-";
	// Day
	if (time->tm_mday < 10) date << 0;
	date << time->tm_mday;
	date << "T";
	// Hour
	if (time->tm_hour < 10) date << 0;
	date << time->tm_hour;
	date << ":";
	// Minute
	if (time->tm_min < 10) date << 0;
	date << time->tm_min;
	date << ":";
	// Second
	if (time->tm_sec < 10) date << 0;
	date << time->tm_sec;
	date << "Z";
	return date.str();
}


// -----------------------------------------------------------------------------
//	Unit testing
// -----------------------------------------------------------------------------

int main(int argc, char** argv)
{
	// Create reference point.
	GpsPoint leipzig;
	leipzig.setGpsPoint(0, 6, 7, 0, std::string("1989-11-20T17:15:25Z"));
	
	// Create sample points.
	GpsPoint a, b, c, d, e;
	a.setGpsPoint(1, 2, 2, 0, std::string("2010-02-09T10:39:05Z"));
	b.setGpsPoint(2, 4, 4, 0, std::string("2010-02-09T10:45:05Z"));
	c.setGpsPoint(3, 4, 6, 0, std::string("2010-02-09T10:50:05Z"));
	d.setGpsPoint(4, 6, 6, 0, std::string("2010-02-09T10:55:05Z"));
	e.setGpsPoint(5, 9, 9, 0, std::string("2010-02-09T11:01:05Z"));
	std::vector<GpsPoint> points;
	points.push_back(a);
	points.push_back(b);
	points.push_back(c);
	points.push_back(d);
	points.push_back(e);

	// Print all points.
	std::cout << "Points before timestamp manipulation." << std::endl;
	for (unsigned int i = 0; i < points.size(); i++)
	{
		std::cout << points.at(i) << std::endl;
	}
	
	// Manipulate all time stamps.
	std::cout << "" << std::endl;
	std::cout << "Find closest GpsPoint to that reference GpsPoint" << std::endl;
	std::cout << leipzig << std::endl;
	std::cout << "" << std::endl;

	DateManipulator dm;
	dm.manipulate(leipzig, points);

	// Print all points.
	std::cout << "Manipulate all GpsPoint in the way that they match to the refrence." << std::endl;
	for (unsigned int i = 0; i < points.size(); i++)
	{
		std::cout << points.at(i) << std::endl;
	}

	return 0;
}
