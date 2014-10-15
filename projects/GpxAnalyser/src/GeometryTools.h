#pragma once

#include "Point.h"

namespace GpxAnalyser
{

class GeometryTools
{
public:
  static double CalculateDistanceInKm(const Point& p1, const Point& p2);
  static Point FindIntermediatePoint(const Point& start, const Point& end, double ratio);

private:
  // prevent construction
  GeometryTools();
};

}

