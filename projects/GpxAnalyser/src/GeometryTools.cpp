#include "GeometryTools.h"

#include <cmath>

namespace GpxAnalyser
{

double ConvertToRadians(double degrees)
{
  const double ratio = M_PI / 180.0;
  return ratio * degrees;
}

double GeometryTools::CalculateDistanceInKm(const Point& p1, const Point& p2)
{
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

Point GeometryTools::FindIntermediatePoint(const Point& start, const Point& end, double ratio)
{
  Point ip;
  ip.Lat = start.Lat + ratio * (end.Lat - start.Lat);
  ip.Lon = start.Lon + ratio * (end.Lon - start.Lon);
  ip.Time = start.Time + ratio * (end.Time - start.Time);
  ip.Altitude = start.Altitude + ratio * (end.Altitude - start.Altitude);

  // does this differ significantly from just applying the ratio?
  ip.TrackPositionInKm = start.TrackPositionInKm + GeometryTools::CalculateDistanceInKm(start, ip);
  return ip;
}

}

