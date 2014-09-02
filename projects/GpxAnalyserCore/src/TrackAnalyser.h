#pragma once

#include "TrackAnalysis.h"
#include "Track.h"

#include <list>

using namespace std;

namespace GpxAnalyserCore
{

class TrackAnalyser
{
public:
    TrackAnalysis* Analyse(Track& track, list<double>& targets);
private:
    TrackAnalysis* Analyse(Track& track, double target);
};

}

