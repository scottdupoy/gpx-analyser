#include <iostream>
#include <rapidjson/document.h>

#include "Consumer.h"
#include "Result.h"

using namespace std;
using namespace rapidjson;

namespace GpxAnalyser
{

Consumer::Consumer(Messaging& messaging, JsonParser& jsonParser, Analyser& analyser, Publisher& publisher)
 : _messaging(messaging)
 , _jsonParser(jsonParser)
 , _analyser(analyser)
 , _publisher(publisher)
{
}

void Consumer::Start()
{
  cout << "subscribing to queue" << endl;
  this->_messaging.Subscribe();

  while (true)
  {
    cout << "waiting for message" << endl;
    Request request = this->_jsonParser.ParseRequest(this->_messaging.Consume());

    cout << "received request:" << endl;
    cout << "  guid:         " << request.Guid << endl;
    cout << "  athleteId:    " << request.AthleteId << endl;
    cout << "  activityId:   " << request.ActivityId << endl;
    cout << "  name:         " << request.Name << endl;
    cout << "  distanceInKm: " << request.DistanceInKm << endl;

/*
    for (list<Distance>::const_iterator it = request.Distances.begin(), end = request.Distances.end(); it != end; it++)
    {
      cout << "    distance: " << it->Name << " => " << it->Distance << endl;
    }

    for (list<Point>::const_iterator it = request.Points.begin(), end = request.Points.end(); it != end; it++)
    {
      cout << "    point: " << it->Lat << ", " << it->Lon << endl;
    }
*/

    Result result = this->_analyser.Analyse(request);

    cout << "Result:" << endl;
    cout << "  Guid:       " << result.Guid << endl;
    cout << "  AthleteId:  " << result.AthleteId << endl;
    cout << "  ActivityId: " << result.ActivityId << endl;
    cout << "    Activity.DistanceInKm: " << result.Activity.DistanceInKm << endl;
    cout << "    Activity.Duration:     " << result.Activity.Duration << endl;
    cout << "    Activity.Points.size:  " << result.Activity.Points.size() << endl;

    list<BestEffort>::const_iterator beIt = result.BestEfforts.begin();
    list<BestEffort>::const_iterator beEnd = result.BestEfforts.end();
    for(; beIt != beEnd; beIt++)
    {
      const Point& start = beIt->BestEffort.Points.front();
      cout << "  BestEffort:     " << beIt->EffortDistance.Name << endl;
      cout << "    Duration:     " << beIt->BestEffort.Duration << endl;
      cout << "    Start s:      " << start.Time << endl;
      cout << "    Start pos k:  " << start.TrackPositionInKm << endl;
    }

    this->_publisher.Publish(result);
  }
}

}

