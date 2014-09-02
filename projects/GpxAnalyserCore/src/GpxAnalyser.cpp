#include <string>
#include <iostream>
#include <list>

#include "GpxAnalyser.h"
#include "TrackAnalysis.h"

using namespace std;

namespace GpxAnalyserCore
{

void GpxAnalyser::AnalyseFile(string& filePath)
{
    cout << "Analysing file: " << filePath << endl;
    // TODO: RAII
    Track* track = this->fileReader.Read(filePath);

    cout << "  Name: " << track->Name << endl;
    tm t = track->UtcTime;
    cout << "  Time: " << t.tm_year << "-" << (1 + t.tm_mon) << "-" << t.tm_mday << " " << t.tm_hour << ":" << t.tm_min << ":" << t.tm_sec << endl;
    cout << "  Number of points: " << track->Points.size() << endl;

    if (track->Points.size() < 2)
    {
        delete track;
        cout << "ERROR: Insufficient points to continue" << endl;
    }

    list<double> targets;
    targets.push_back(1.0);
    targets.push_back(5.0);
    targets.push_back(10.0);
    
    // TODO: RAII
    TrackAnalysis* analysis = this->trackAnalyser.Analyse(*track, targets);

    delete analysis;
    delete track;
}

}
