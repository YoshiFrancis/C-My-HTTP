#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <unordered_map>

typedef std::unordered_map<std::string, std::string> Header;

// TODO
class Request {
private:
  std::string _target;
  std::string _protocol;
  std::string _method;
  Header _header;
  std::string _body;

public:
  std::string getTarget() const { return _target; }
  std::string getMethod() const { return _method; }
  std::string getProtocol() const { return _protocol; }
  Header getHeader() const { return _header; }
  std::string getBody() const {return _body; }

  void setTarget(std::string target);
  void setMethod(std::string method);
  void setProtocol(std::string protocol);
  void addHeader(std::string heading, std::string body);
  void addToBody(std::string adding);
};

#endif