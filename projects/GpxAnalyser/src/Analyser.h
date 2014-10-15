#pragma once

#include "Request.h"
#include "Result.h"
#include "BestEffort.h"

namespace GpxAnalyser
{

class Analyser
{
public:
  Result Analyse(const Request& request);

private:
  BestEffort CalculateBestEffort(const Distance& distance, const list<Point>& points);
};

}

