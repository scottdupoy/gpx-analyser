#include <iostream>

#include "Publisher.h"

using namespace std;

namespace GpxAnalyser
{

Publisher::Publisher(Messaging& messaging, JsonEncoder& jsonEncoder)
  : _messaging(messaging), _jsonEncoder(jsonEncoder)
{
}

void Publisher::Publish(Result& result)
{
  string json = this->_jsonEncoder.Encode(result);
  this->_messaging.PublishResult(json);
}

}
