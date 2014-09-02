#pragma once

#include <map>

#include "Track.h"
#include "Effort.h"

using namespace std;

namespace GpxAnalyserCore
{

struct TrackAnalysis
{
    tm StartTime;

    tm EndTime;

    tm Duration;

    double DistanceInKm;

    map<double, Effort> BestEfforts;
};

}

