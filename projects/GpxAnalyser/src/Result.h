#pragma once

#include <string>
#include <list>

#include "Effort.h"
#include "BestEffort.h"

using namespace std;

namespace GpxAnalyser
{

class Result
{
public:
  int AthleteId;
  long ActivityId;
  string Name;
  double MovingTime;
  double ElapsedTime;
  double DistanceInKm;
  string StartDate;
  Effort Activity;
  list<BestEffort> BestEfforts;
};

}
