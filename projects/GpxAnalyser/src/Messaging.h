#pragma once

#include <SimpleAmqpClient/SimpleAmqpClient.h>
#include <string>

namespace GpxAnalyser
{

class Messaging
{
private:
  std::string _host;
  std::string _user;
  std::string _password;
public: // TODO: temp for dev
  AmqpClient::Channel::ptr_t _connection;
  std::string _consumerTag;

public:
  Messaging(std::string& host, std::string& user, std::string& password);
  void Connect();
  void DeclareStructure();
  void Subscribe();
  std::string Consume();
  void PublishResult(std::string& result);
};

}
