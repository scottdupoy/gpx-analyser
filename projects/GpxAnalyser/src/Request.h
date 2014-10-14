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
  list<Distance> Distances;
  list<Point> Points;
};

}
