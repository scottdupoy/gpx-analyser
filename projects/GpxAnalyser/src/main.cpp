#include <iostream>
#include <string>

#include <SimpleAmqpClient/SimpleAmqpClient.h>
#include <rapidjson/document.h>

using namespace std;
using namespace AmqpClient;
using namespace rapidjson;

class Messaging
{
//private:
public: // just for dev
  std::string _user;
  std::string _password;
  Channel::ptr_t _connection;

public:
  Messaging(std::string& user, std::string& password);
  void Connect();
  void DeclareStructure();
  void PublishResult(std::string& result);
};

Messaging::Messaging(std::string& user, std::string& password)
 : _user(user)
 , _password(password)
{
}

void Messaging::Connect()
{
  cout << "Messaging: creating channel: user: " << this->_user << ", password: " << this->_password << endl;
  this->_connection = Channel::Create("localhost", 5672, this->_user, this->_password);
}

void Messaging::DeclareStructure()
{
  cout << "Messaging: declaring exchange and queue" << endl;
  this->_connection->DeclareExchange(
    "run-ranker",
    Channel::EXCHANGE_TYPE_DIRECT,
    false, // passive
    true, // durable
    false); // autoDelete
  this->_connection->DeclareQueue(
    "analysis-requests",
    false, // passive
    false, // durable
    false, // exclusive
    true); // autoDelete
  this->_connection->BindQueue(
    "analysis-requests",
    "run-ranker",
    "analysis-request");
}

void Messaging::PublishResult(std::string& result)
{
  cout << "Messaging: publishing result" << endl;
  BasicMessage::ptr_t message = BasicMessage::Create(result);
  message->ContentType("application/json");
  cout << "  sending: " << message->Body().c_str() << endl;
  this->_connection->BasicPublish("run-ranker", "analysis-result", message);
}

int main(int argc, char* argv[])
{
  if (argc < 3)
  {
    cerr << "ERROR: Insufficient argument. Please provide RMQ credentials." << endl; 
    return -1;
  }

  string user(argv[1]);
  string password(argv[2]);

  Messaging messaging(user, password);
  messaging.Connect();
  messaging.DeclareStructure();

  cout << "starting consumer" << endl;
  string consumerTag = messaging._connection->BasicConsume("analysis-requests", "");
  while (true) {
    Envelope::ptr_t envelope = messaging._connection->BasicConsumeMessage(consumerTag);
    cout << "consumed message" << endl;

    Document document;
    document.Parse(envelope->Message()->Body().c_str());

    if (document.HasMember("guid") && document["guid"].IsString())
    {
      cout << ">> guid: " << document["guid"].GetString() << endl;
      std::string result = "{\"message\":\"c++ result goes here\"}";
      messaging.PublishResult(result);
    }
  }

  return 0;
}

