#include "DateManipulator.h"

void DateManipulator::manipulate(const GpsPoint& reference, std::vector<GpsPoint>& points)
{
	std::vector<GpsPoint>::iterator closestPoint = getClosestPoint(reference, points);
}

std::vector<GpsPoint>::iterator DateManipulator::getClosestPoint(const GpsPoint& reference, 
		std::vector<GpsPoint>& points)
{
	return points.begin();
}

void DateManipulator::setTimestamps(const GpsPoint& reference,
		std::vector<GpsPoint>::iterator begin,
		std::vector<GpsPoint>::iterator end,
		std::vector<GpsPoint>::iterator point)
{

}
