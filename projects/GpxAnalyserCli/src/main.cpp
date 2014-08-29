#include <iostream>

#include "usage.h"
#include "GpxAnalyserCore/Analyser.h"

using namespace GpxAnalyserCli;
using namespace GpxAnalyserCore;
using namespace std;

int main(int argc, char* argv[])
{    
    if (argc < 2)
    {
        cerr << "ERROR: Insufficient arguments supplied" << endl;
        Usage();
        return -1;
    }
    
    string f(argv[1]);
    
    Analyser analyser;
    analyser.AnalyseFile(f);
   
    return 0;
}
