#include <rapidjson/document.h>

#include "JsonParser.h"

using namespace rapidjson;

namespace GpxAnalyser
{

Request JsonParser::ParseRequest(const string& message)
{
  Document document;
  document.Parse(message.c_str());

  // TODO: validate the message has the expected data
  Request request;
  request.Guid = document["guid"].GetString();
  request.AthleteId = document["athleteId"].GetInt();
  request.ActivityId = document["activityId"].GetInt64();

  // TODO: distances and points

  return request;
}

}