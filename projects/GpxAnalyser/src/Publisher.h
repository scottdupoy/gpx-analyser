#pragma once

#include "Messaging.h"
#include "JsonEncoder.h"
#include "Result.h"

namespace GpxAnalyser
{

class Publisher
{
private:
  Messaging& _messaging;
  JsonEncoder& _jsonEncoder;

public:
  Publisher(Messaging& messaging, JsonEncoder& jsonEncoder);
  void Publish(Result& result);
};

}
