
#include "AnalyserException.h"

using namespace std;

namespace GpxAnalyserCore
{

AnalyserException::AnalyserException(const char* message)
 : runtime_error(message)
{
}

}
