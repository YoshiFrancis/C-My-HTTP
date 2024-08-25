#ifndef HTTP_H
#define HTTP_H

#include <fstream>
#include <string>
#include <optional>
#include <unordered_map>
#include "response.hpp"
#include "request.hpp"

class http {
public:
  http() {};
  ~http();

private:
  // socket file descriptor server is listeninig on
  int _socketfd;
  // paths mapping to handler functions
  std::unordered_map<std::string, void (*)(Request& request, Response& res)> handlerFuncs;
public:
  void listenAndServe(std::string address, int port);
  void handlerFunc(std::string path, void (*func)(Request& req, Response& res));
private:
  void handleConnection(int socket) const;
  Request parse(std::vector<char>& message) const;

};

#endif