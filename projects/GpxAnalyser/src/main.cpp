#include <iostream>
#include <string>

#include "Messaging.h"
#include "JsonParser.h"
#include "Analyser.h"
#include "Consumer.h"

using namespace std;
using namespace GpxAnalyser;

// TODO: amongst (many) other things:
//  - check for function const-ness that can be applied
//  - check for possible div by zeroes
//  - abstract Delta list and running totals

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
  JsonEncoder jsonEncoder;
  Analyser analyser;
  Publisher publisher(messaging, jsonEncoder);
  Consumer consumer(messaging, jsonParser, analyser, publisher);

  consumer.Start();
  
  return 0;
}
