#pragma once

#include "Request.h"

namespace GpxAnalyser
{

class JsonParser
{
public:
  Request ParseRequest(const string& message);
};

}
