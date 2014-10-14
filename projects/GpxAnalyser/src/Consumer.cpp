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
    cout << "  guid: " << request.Guid << endl;
    cout << "  athleteId: " << request.AthleteId << endl;
    cout << "  activityId: " << request.ActivityId << endl;

    Result result;
    result.Guid = request.Guid;

    // TODO: do analysis

    this->_publisher.Publish(result);
  }
}

}
