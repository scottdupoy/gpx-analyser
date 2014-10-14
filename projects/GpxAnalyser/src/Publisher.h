#pragma once

#include "Messaging.h"
#include "Result.h"

namespace GpxAnalyser
{

class Publisher
{
private:
  Messaging& _messaging;

public:
  Publisher(Messaging& messaging);
  void Publish(Result& result);
};

}
