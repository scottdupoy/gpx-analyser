#pragma once

#include <list>

#include "Point.h"

using namespace std;

namespace GpxAnalyserCore
{

struct Effort
{
    double DistanceInKm;

    tm Duration;

    list<Point> Points;
};

}

