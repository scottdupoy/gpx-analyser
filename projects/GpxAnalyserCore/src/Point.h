#pragma once

namespace GpxAnalyserCore
{

struct Point
{
    tm UtcTime;

    double Latitude;

    double Longitude;

    double Elevation;

    double TrackPositionInKm;

    int HeartRate;
};

}

