#include <iostream>
#include <rapidjson/document.h>

#include "Consumer.h"

using namespace std;
using namespace rapidjson;

namespace GpxAnalyser
{

Consumer::Consumer(Messaging& messaging, JsonParser& jsonParser, Analyser& analyser)
 : _messaging(messaging)
 , _jsonParser(jsonParser)
 , _analyser(analyser)
{
}

void Consumer::Start()
{
  cout << "subscribing to queue" << endl;
  this->_messaging.Subscribe();

  while (true)
  {
    cout << "waiting for message" << endl;
    string message = this->_messaging.Consume();

    cout << "consumed message" << endl;
    Document document;
    document.Parse(message.c_str());

    if (document.HasMember("guid") && document["guid"].IsString())
    {
      cout << ">> guid: " << document["guid"].GetString() << endl;
      std::string result = "{\"message\":\"c++ result goes here\"}";
      this->_messaging.PublishResult(result);
    }
  }
}

}
