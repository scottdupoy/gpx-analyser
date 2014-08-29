#pragma once

#include <string>

#include "GpxFileReader.h"

namespace GpxAnalyserCore
{

class GpxAnalyser
{
private:
    GpxFileReader fileReader;

public:
    void AnalyseFile(std::string& filePath);
};

}
