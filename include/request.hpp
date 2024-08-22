#ifndef REQUEST_H
#define REQUEST_H

#include <string>

// TODO
class Request {
private:
  std::string _path;
public:
  std::string getPath() const { return _path; }
};

#endif