/*=======================================================
 Copyright (c) avp::ptr, 2010
=======================================================*/

#ifndef _GPSPOINT_H_
#define _GPSPOINT_H_

#include <iostream>

/**
 * \brief Holds one gps point with timestamp.
 *
 */
class GpsPoint
{
	int m_gpsPointId;
	double m_latitude;
	double m_longitude;
	double m_elevation;
	std::string m_timestamp;
//	std::string m_location;

public:
	GpsPoint()
	:
	m_gpsPointId(0),
	m_latitude(0.0),
	m_longitude(0.0),
	m_elevation(0.0),
	m_timestamp("")//,
//	m_location("")
	{};

	~GpsPoint(){};

    /**
    * \brief Set values for a GpsPoint.
    * \param gpsPointId
    * \param latitude
    * \param longitude
    * \param elevation
    * \param timestamp
    */
	void setGpsPoint(int gpsPointId,
                     double latitude,
					 double longitude,
					 double elevation,
					 const std::string& timestamp)//,
//					 const std::string& location)
	{
		m_gpsPointId = gpsPointId;
		m_latitude = latitude;
		m_longitude = longitude;
		m_elevation = elevation;
		m_timestamp = timestamp;
//		m_location = location;
	}
	//---------------------------------------------------------------------------
	/**
	* \brief Get id of gps point.
	* \return gpsPointId int value.
	*/
	int getGpsPointId() const { return m_gpsPointId; }
	/**
	* \brief Get latitude.
	* \return latitude double value.
	*/
	double getLatitude() const { return m_latitude; }
	/**
	* \brief Get longitude.
	* \return longitude double value.
	*/
	double getLongitude() const { return m_longitude; }
	/**
	* \brief Get elevation.
	* \return elevation double value.
	*/
	double getElevation() const { return m_elevation; }
	//---------------------------------------------------------------------------
//    /**
//	* \brief Get location for GpsPoint.
//	* \return Location string.
//	*/
//	const std::string& getLocation() const { return m_location; }
	//---------------------------------------------------------------------------
    /**
	* \brief Get time stamp for GpsPoint.
	* \return Timestamp string.
	*/
	const std::string& getTimestamp() const { return m_timestamp; }
	// -----------------------------------------------------------------------------
    /**
	* \brief Set time stamp for GpsPoint.
	* \return Timestamp string.
	*/
	void setTimestamp(const std::string& timestamp) { m_timestamp = timestamp; }
	// -----------------------------------------------------------------------------
	/**
	* \brief Clear GpsPoint object.
	*/
	void clear()
	{
		m_gpsPointId = 0;
		m_latitude = 0;
		m_longitude = 0;
		m_elevation = 0;
		m_timestamp = "";
//		m_location = "";
	}
};

inline std::ostream& operator<<(std::ostream& os, const GpsPoint& p)
{
	os << "id: " << p.getGpsPointId() << ", ";
	os << "lat: " << p.getLatitude() << ", ";
	os << "lon: " << p.getLongitude() << ", ";
	os << "time: " << p.getTimestamp();
	return os;
}


#endif // _GPSPOINT_H_
