#include <string>

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h> // tried memorybuffer but was slower

#include "JsonEncoder.h"

using namespace std;
using namespace rapidjson;

namespace GpxAnalyser
{

void AddKvp(Writer<StringBuffer>& writer, const char* key, const string& value)
{
  writer.String(key);
  writer.String(value.c_str());
}

void AddKvp(Writer<StringBuffer>& writer, const char* key, const int value)
{
  writer.String(key);
  writer.Int(value);
}

void AddKvp(Writer<StringBuffer>& writer, const char* key, const long value)
{
  writer.String(key);
  writer.Int64(value);
}

void AddKvp(Writer<StringBuffer>& writer, const char* key, const double value)
{
  writer.String(key);
  writer.Double(value);
}

void AddPoint(Writer<StringBuffer>& writer, const Point& point)
{
  writer.StartObject();
  AddKvp(writer, "lat", point.Lat);
  AddKvp(writer, "lon", point.Lon);
  AddKvp(writer, "time", point.Time);
  AddKvp(writer, "altitude", point.Altitude);
  AddKvp(writer, "trackPositionInKm", point.TrackPositionInKm);
  writer.EndObject();
}

void AddEffort(Writer<StringBuffer>& writer, const Effort& effort)
{
  writer.StartObject();

  AddKvp(writer, "distanceInKm", effort.DistanceInKm);
  AddKvp(writer, "duration", effort.Duration);

  writer.String("points");
  writer.StartArray();

  list<Point>::const_iterator it = effort.Points.begin();
  list<Point>::const_iterator end = effort.Points.end();
  for (; it != end; it++)
  {
    AddPoint(writer, *it);
  }

  writer.EndArray();

  writer.EndObject();
}

void AddDistance(Writer<StringBuffer>& writer, const Distance& distance)
{
  writer.StartObject();
  AddKvp(writer, "id", distance.Id);
  AddKvp(writer, "distanceInKm", distance.DistanceInKm);
  AddKvp(writer, "name", distance.Name);
  AddKvp(writer, "type", distance.Type);
  writer.EndObject();
}

void AddBestEffort(Writer<StringBuffer>& writer, const BestEffort& bestEffort)
{
  writer.StartObject();
  writer.String("distance");
  AddDistance(writer, bestEffort.EffortDistance);  
  writer.String("effort");
  AddEffort(writer, bestEffort.BestEffort);
  writer.EndObject();
}

void AddBestEfforts(Writer<StringBuffer>& writer, const list<BestEffort>& bestEfforts)
{
  writer.StartArray();
  list<BestEffort>::const_iterator it = bestEfforts.begin();
  list<BestEffort>::const_iterator end = bestEfforts.end();
  for (; it != end; it++)
  {
    AddBestEffort(writer, *it);
  }
  writer.EndArray();
}

string JsonEncoder::Encode(Result& result)
{
  StringBuffer buffer;
  Writer<StringBuffer> writer(buffer);

  writer.StartObject();

  AddKvp(writer, "athleteId", result.AthleteId);
  AddKvp(writer, "activityId", result.ActivityId);
  AddKvp(writer, "name", result.Name);
  AddKvp(writer, "movingTime", result.MovingTime);
  AddKvp(writer, "elapsedTime", result.ElapsedTime);
  AddKvp(writer, "distanceInKm", result.DistanceInKm);
  AddKvp(writer, "startDate", result.StartDate);

  writer.String("activity");
  AddEffort(writer, result.Activity);

  writer.String("bestEfforts");
  AddBestEfforts(writer, result.BestEfforts);

  writer.EndObject();

  return buffer.GetString();
}

}

