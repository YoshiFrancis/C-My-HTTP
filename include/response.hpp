#ifndef RESPONSE_H
#define RESPONSE_H

// TODO

#include <string>
#include <unordered_map>
typedef std::unordered_map<std::string, std::string> Header;
class Response {
public:
  Response() : _protocol("HTTP/1.1"), _status("200"), _status_desc("OK")
  {}

  enum class StatusCode {
    OK = 200,
    Created = 201,
    Accepted = 202,
    NoContent = 204,
    Found = 302,
    BadRequest = 400,
    Unauthorized = 401,
    Forbidden = 403,
    NotFound = 404,
    MethodNotAllowed = 405,
    NotAcceptable = 406,
    TooManyRequests = 429,
    InternalServererror = 500,
    NotImplemented = 501,
    HTTPVersionNotSupported = 505,
  };

private:
  std::string _status;
  std::string _status_desc;
  std::string _protocol;
  Header _header;
  std::string _body;

public:
  void writeStatus(StatusCode code);
  void writeHeader(std::string& key, std::string& val);
  void write(std::string& arg); 
  std::string serialize() const;
};

#endif