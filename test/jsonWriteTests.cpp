#include <iostream>
#include <ctime>

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/memorybuffer.h>

using namespace std;
using namespace rapidjson;

template<typename T>
void addData(Writer<T>& direct)
{
  direct.StartObject();
  
  direct.String("k");
  direct.String("v");
  
  direct.String("id");
  direct.Int(123456);

  direct.String("dists");
  direct.StartArray();
  direct.Int(1);
  direct.Int(2);
  direct.Int(3);
  direct.EndArray();

  direct.String("points");
  direct.StartArray();
  for (int i = 0; i < 10000; i++)
  {
    direct.StartObject();
    direct.String("lat");
    direct.Double(1.11 * i);

    direct.String("lon");
    direct.Double(2.22 * i);

    direct.String("altitude");
    direct.Int(100 * i);

    direct.EndObject();
  }
  direct.EndArray();

  direct.EndObject();
}

int main()
{
  // results indicate the the string method is reliably quicker
  const int iterations = 100;
  clock_t start;
  cout << "json test" << endl << endl;

  // strings second
  start = std::clock();
  cout << "string tests" << endl;
  for (int i = 0; i < iterations; i++)
  {
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    addData<StringBuffer>(writer);
    string json = buffer.GetString();
  }
  cout << (clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << endl << endl;

  // memory first
  start = clock();
  cout << "memory tests" << endl;
  for (int i = 0; i < iterations; i++)
  {
    MemoryBuffer buffer;
    Writer<MemoryBuffer> writer(buffer);
    addData<MemoryBuffer>(writer);
    string json(buffer.GetBuffer(), buffer.GetSize());
  }
  cout << (clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << endl << endl;

  cout << "finished" << endl;

  return 0;
}

