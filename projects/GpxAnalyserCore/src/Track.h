#pragma once

#include <list>
#include "Point.h"

namespace GpxAnalyserCore
{

struct Track
{
    std::string Name;

    tm UtcTime;

    std::list<Point> Points;
};

}

