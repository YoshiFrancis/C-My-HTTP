#include "../include/response.hpp"
#include <sstream>
#include <string>

void Response::writeStatus(Response::StatusCode code) {
  _status = "200";
  _status_desc = "OK";
  // using enum Response::StatusCode;
  // switch (Response::StatusCode code) {
  //   case OK:
  //     _status = std::to_string(OK);
  //     _status_desc = "OK";
  //     break;
  // }
}

void Response::write(std::string arg) {
  _body.append(arg);
}
void Response::writeHeader(std::string key, std::string val) {
  _header[key] = val;
}

std::string Response::serialize() const {
  std::stringstream ss;
  // status line
  ss << _protocol << " " << _status << " " << _status_desc << "\n\n";

  // headers 
  for (auto& header : _header) {
    ss << header.first << ": " << header.second << "\n";
  }
  ss << "\n";

  // body
  ss << _body;
  return ss.str();
}