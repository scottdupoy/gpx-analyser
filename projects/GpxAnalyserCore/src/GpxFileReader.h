#pragma once

#include <string>
#include "GpxFile.h"

using namespace std;

namespace GpxAnalyserCore
{

class GpxFileReader
{
public:
    GpxFile* Read(string& filePath);
};

}
