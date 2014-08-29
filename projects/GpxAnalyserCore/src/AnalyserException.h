#pragma once

#include <stdexcept>

using namespace std;

namespace GpxAnalyserCore
{

class AnalyserException : public runtime_error
{
public:
    AnalyserException(const char* message);
};

}
