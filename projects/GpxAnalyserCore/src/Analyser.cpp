#include <string>

#include "GpxAnalyserCore/Analyser.h"
#include "GpxAnalyser.h"

using namespace std;

namespace GpxAnalyserCore
{

void Analyser::AnalyseFile(string& filePath)
{
    GpxAnalyser analyser;
    analyser.AnalyseFile(filePath);
}

}
