/*==========================================================
 Copyright (c) avp::ptr, 2010
 ==========================================================*/

#ifndef _DATEMANIPULATOR_H_
#define _DATEMANIPULATOR_H_

#include <iostream>
#include <vector>
#include <string>
#include "GpsPoint.h"


/*
 * \brief A timestamp manipulator.
 */
class DateManipulator
{
public:

	/**
	 * \brief Manipulate GpsPoints according to the given reference GpsPoint.
	 *
	 * Find the closest point to the reference and take it as initial point 
	 * to manipulate all the others, so that their timestamps correspond to 
	 * the timestamp of the reference point.
	 */
	void manipulate(const GpsPoint& reference, std::vector<GpsPoint>& points);

private:

	/**
	 * \brief Get closest point to the reference gps-point.
	 */
	std::vector<GpsPoint>::iterator getClosestPoint(const GpsPoint& reference,
		std::vector<GpsPoint>& points);

	/**
	 * \brief Set timestamp of all points.
	 */
	void setTimestamps(const GpsPoint& reference,
		std::vector<GpsPoint>::iterator begin,
		std::vector<GpsPoint>::iterator end,
		std::vector<GpsPoint>::iterator point);

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
