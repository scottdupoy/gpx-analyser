#include <string>
#include <iostream>

#include "GpxAnalyser.h"

using namespace std;

namespace GpxAnalyserCore
{

void GpxAnalyser::AnalyseFile(string& filePath)
{
    cout << "Analysing file: " << filePath << endl;
    GpxFile* file = this->fileReader.Read(filePath);
}

}
