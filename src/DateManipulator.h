/*==========================================================
 Copyright (c) avp::ptr, 2010
 ==========================================================*/

#ifndef _DATEMANIPULATOR_H_
#define _DATEMANIPULATOR_H_

#include <iostream>
#include <vector>
#include <string>
#include "GpsPoint.h"

struct DateTokens
{
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
};

class DateManipulator
{
public:

	/**
	 *
	 */
	void manipulate(const GpsPoint& reference, std::vector<GpsPoint>& points);

private:

	/**
	 * \brief Get closest point to the reference gps-point.
	 */
	std::vector<GpsPoint>::iterator getClosestPoint(const GpsPoint& reference,
		std::vector<GpsPoint>& points);

	/**
	 *
	 */
	void setTimestamps(const GpsPoint& reference,
		std::vector<GpsPoint>::iterator begin,
		std::vector<GpsPoint>::iterator end,
		std::vector<GpsPoint>::iterator point);

public:

	/**
	 * \brief Convert internal timestamp to unix time.
	 */
	time_t getUnixTime(const std::string& date);

	/**
	 * \brief Convert unix time to internal time stamp.
	 */
	std::string getTimestamp(const time_t& uTime);
};

#endif
