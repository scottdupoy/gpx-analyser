#pragma once

#include <list>

#include "Point.h"

using namespace std;

namespace GpxAnalyser
{

class Effort
{
public:
  double DistanceInKm;
  double Duration;
  list<Point> Points;
};

}

