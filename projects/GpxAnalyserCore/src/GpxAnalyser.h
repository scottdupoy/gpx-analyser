#pragma once

#include <string>

#include "GpxFileReader.h"
#include "TrackAnalyser.h"

namespace GpxAnalyserCore
{

class GpxAnalyser
{
private:
    GpxFileReader fileReader;
    TrackAnalyser trackAnalyser;

public:
    void AnalyseFile(std::string& filePath);
};

}
