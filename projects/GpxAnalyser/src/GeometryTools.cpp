#include "GeometryTools.h"

#include <cmath>

namespace GpxAnalyser
{

double ConvertToRadians(double degrees)
{
  const double ratio = M_PI / 180.0;
  return ratio * degrees;
}

double CalculateDistanceInKmByRatio(const Point& p1, const Point& p2)
{
  // if distance data is present in strava streams then simply take a linear
  // approach. should keep things consistent with strava results.
  return std::abs(p2.TrackPositionInKm - p1.TrackPositionInKm);
}

double CalculateDistanceInKmByHaversineMethod(const Point& p1, const Point& p2)
{
  // haversine method is quick and accurate to ~0.3%
  const double radius = 6371;

  double latDiff = ConvertToRadians(p2.Lat - p1.Lat);
  double lonDiff = ConvertToRadians(p2.Lon - p1.Lon);
  double sinLatDiff = sin(latDiff / 2.0);
  double sinLonDiff = sin(lonDiff / 2.0);

  double a = sinLatDiff * sinLatDiff + cos(ConvertToRadians(p1.Lat)) * cos(ConvertToRadians(p2.Lat)) * sinLonDiff * sinLonDiff;

  double sqrta = sqrt(a);
  double c = 2.0 * asin(1.0 < sqrta ? 1.0 : sqrta);
  
  return radius * c;
}

double CalculateDistanceInKmByVincentyMethod(const Point& p1, const Point& p2)
{
  // much more accurate than the haversine method, but slower
  // TODO
  return 0.0;
}

double GeometryTools::CalculateDistanceInKm(const Point& p1, const Point& p2)
{
  // if change this method then make sure the FindIntermediatePoint method is similarly changed.
  return CalculateDistanceInKmByRatio(p1, p2);
  //return CalculateDistanceInKmByHaversineMethod(p1, p2);
  //return CalculateDistanceInKmByVincentyMethod(p1, p2);
}

Point GeometryTools::FindIntermediatePoint(const Point& start, const Point& end, double ratio)
{
  Point ip;
  ip.Lat = start.Lat + ratio * (end.Lat - start.Lat);
  ip.Lon = start.Lon + ratio * (end.Lon - start.Lon);
  ip.Time = start.Time + ratio * (end.Time - start.Time);
  ip.Altitude = start.Altitude + ratio * (end.Altitude - start.Altitude);

  // may have to revert back to calculating the distances if things deviate too much or
  // the strava distance stream is missing
  //ip.TrackPositionInKm = start.TrackPositionInKm + GeometryTools::CalculateDistanceInKm(start, ip);

  // interpolate by using a straight ratio. should be faster and keep more consistent with strava.
  ip.TrackPositionInKm = start.TrackPositionInKm + ratio * (end.TrackPositionInKm - start.TrackPositionInKm);
  return ip;
}

}

