#pragma once

#include <string>
#include "Track.h"

using namespace std;

namespace GpxAnalyserCore
{

class GpxFileReader
{
public:
    Track* Read(string& filePath);
};

}
