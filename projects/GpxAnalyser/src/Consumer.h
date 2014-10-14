#pragma once

#include "Messaging.h"
#include "JsonParser.h"
#include "Analyser.h"
#include "Publisher.h"

namespace GpxAnalyser
{

class Consumer
{
private:
    Messaging& _messaging;
    JsonParser& _jsonParser;
    Analyser& _analyser;
    Publisher& _publisher;

public:
    Consumer(Messaging& messaging, JsonParser& jsonParser, Analyser& analyser, Publisher& publisher);
    void Start();
};

}
