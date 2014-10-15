#include <iostream>

#include <SimpleAmqpClient/SimpleAmqpClient.h>

#include "Messaging.h"

using namespace std;
using namespace AmqpClient;

namespace GpxAnalyser
{

Messaging::Messaging(std::string& host, std::string& user, std::string& password)
 : _host(host)
 , _user(user)
 , _password(password)
{
}

void Messaging::Connect()
{
  cout << "Messaging: creating channel: host: " << this->_host << ", user: " << this->_user << ", password: " << this->_password << endl;
  this->_connection = Channel::Create(this->_host, 5672, this->_user, this->_password);
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

void Messaging::Subscribe()
{
  this->_consumerTag = this->_connection->BasicConsume("analysis-requests", "");
}

string Messaging::Consume()
{
  Envelope::ptr_t envelope = this->_connection->BasicConsumeMessage(this->_consumerTag);
  return envelope->Message()->Body(); // copy constructor will be invoked
}

void Messaging::PublishResult(std::string& result)
{
  cout << "Messaging: publishing result" << endl;
  BasicMessage::ptr_t message = BasicMessage::Create(result);
  message->ContentType("application/json");
  this->_connection->BasicPublish("run-ranker", "analysis-result", message);
}

}
