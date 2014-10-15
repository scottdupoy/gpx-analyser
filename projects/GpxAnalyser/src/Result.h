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
  string Guid;
  int AthleteId;
  long ActivityId;
  Effort Activity;
  list<BestEffort> BestEfforts;
};

}
