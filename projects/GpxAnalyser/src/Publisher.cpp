#include <iostream>

#include "Publisher.h"

using namespace std;

namespace GpxAnalyser
{

Publisher::Publisher(Messaging& messaging)
  : _messaging(messaging)
{
}

void Publisher::Publish(Result& result)
{
  // TODO: pack result into a JSON payload - for now just send guid.
  // TODO: remove tempStart and tempEnd
  string message = "{\"message\":\"" + result.Guid + "\"}";
  this->_messaging.PublishResult(message);
}

}
