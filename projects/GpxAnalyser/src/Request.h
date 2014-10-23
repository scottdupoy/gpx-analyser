#pragma once

#include <string>
#include <list>

#include "Point.h"
#include "Distance.h"

using namespace std;

namespace GpxAnalyser
{

class Request
{
public:
  string Guid;
  int AthleteId;
  long ActivityId;
  string Name;
  double MovingTime;
  double ElapsedTime;
  double DistanceInKm;
  string StartDate;
  list<Distance> Distances;
  list<Point> Points;
};

}
