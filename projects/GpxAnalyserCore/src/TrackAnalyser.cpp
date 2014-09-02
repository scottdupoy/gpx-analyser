#include <iostream>

#include "TrackAnalyser.h"

using namespace std;

namespace GpxAnalyserCore
{

TrackAnalysis* TrackAnalyser::Analyse(Track& track, list<double>& targets)
{
    cout << "Analysing track: " << track.Name << endl;

    // TODO: RAII
    TrackAnalysis* analysis = new TrackAnalysis();

    for (auto it = targets.begin(); it != targets.end(); ++it)
    {
        TrackAnalysis* targetAnalysis = this->Analyse(track, *it);
        //TODO: aggregate
        delete targetAnalysis;
    }

    return analysis;
}

TrackAnalysis* TrackAnalyser::Analyse(Track& track, double target)
{
    cout << "  Target: " << target << endl;
    TrackAnalysis* analysis = new TrackAnalysis();
    // TODO
    return analysis;
}

}

