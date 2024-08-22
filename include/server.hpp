#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <unordered_map>
#include "response.hpp"
#include "request.hpp"

class HTTPServer {
public:
  HTTPServer() {};
  ~HTTPServer();

private:
  // socket file descriptor server is listeninig on
  int _socketfd;
  // paths mapping to handler functions
  std::unordered_map<std::string, void (*)(Request request, Response res)> handlerFuncs;
public:
  void listenAndServe(std::string address, int port);
  void handlerFunc(std::string path, void (*func)(Request req, Response res));
private:
  void handleConnection(int socket) const;
  Request parse(std::vector<char>& message) const;

};

#endif