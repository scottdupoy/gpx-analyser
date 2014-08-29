#pragma once

#include <string>

namespace GpxAnalyserCore
{

// Simple wrapper class which exposes as little as possible outside the DLL and immediately
// delegates to an internal-only fully features class.
class Analyser
{
public:
    void AnalyseFile(std::string& filePath);
};

}
