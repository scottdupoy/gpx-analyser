#include <iostream>
#include <string>

#include "Messaging.h"
#include "JsonParser.h"
#include "Analyser.h"
#include "Consumer.h"

using namespace std;
using namespace GpxAnalyser;

int main(int argc, char* argv[])
{
  if (argc < 4)
  {
    cerr << "ERROR: Insufficient argument. Please provide RMQ host and credentials." << endl; 
    return -1;
  }

  string host(argv[1]);
  string user(argv[2]);
  string password(argv[3]);

  Messaging messaging(host, user, password);
  messaging.Connect();
  messaging.DeclareStructure();

  JsonParser jsonParser;
  Analyser analyser;
  Consumer consumer(messaging, jsonParser, analyser);

  consumer.Start();
  
  return 0;
}
