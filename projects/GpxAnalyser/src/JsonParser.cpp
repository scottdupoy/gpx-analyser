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

  // top-level request details
  Request request;
  request.AthleteId = document["athleteId"].GetInt();
  request.ActivityId = document["activityId"].GetInt64();
  request.Name = document["name"].GetString();
  request.MovingTime = document["movingTime"].GetDouble();
  request.ElapsedTime = document["elapsedTime"].GetDouble();
  request.StartDate = document["startDate"].GetString(); // keep as string, just passing through
  request.DistanceInKm = document["distanceInKm"].GetDouble();

  // distances
  const Value& distances = document["distances"];
  SizeType count = distances.Size();
  for (SizeType i = 0; i < count; i++)
  {
    Distance distance;
    const Value& item = distances[i];
    distance.Id = item["id"].GetInt();
    distance.DistanceInKm = item["distanceInKm"].GetDouble();
    distance.Name = item["name"].GetString();
    distance.Type = item["type"].GetString();
    request.Distances.push_back(distance);
  }

  // points
  const Value& points = document["points"];
  count = points.Size();
  for (SizeType i = 0; i < count; i++)
  {
    Point point;
    const Value& item = points[i];
    point.Lat = item["lat"].GetDouble();
    point.Lon = item["lon"].GetDouble();
    point.Time = item["time"].GetDouble(); // should always be an int at this point
    point.TrackPositionInKm = item["distance"].GetDouble() / 1000.0; // m => km
    point.Altitude = item["altitude"].GetDouble();
    request.Points.push_back(point);
  }

  return request;
}

}
