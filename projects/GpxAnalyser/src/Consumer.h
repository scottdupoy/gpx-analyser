#pragma once

#include "Messaging.h"
#include "JsonParser.h"
#include "Analyser.h"

namespace GpxAnalyser
{

class Consumer
{
private:
    Messaging& _messaging;
    JsonParser& _jsonParser;
    Analyser& _analyser;

public:
    Consumer(Messaging& messaging, JsonParser& jsonParser, Analyser& analyser);
    void Start();
};

}
