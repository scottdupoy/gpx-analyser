#pragma once

#include <string>

#include "Result.h"

namespace GpxAnalyser
{

class JsonEncoder
{
public:
  std::string Encode(Result& result);
};

}

