#include "../include/server.hpp"
#include "../include/net.hpp"
#include "../include/request.hpp"
#include "../include/response.hpp"
#include <string>

HTTPServer::~HTTPServer() {
  net::Close(_socketfd);
}

void HTTPServer::listenAndServe(std::string address, int port) {
  _socketfd = net::Listen("tcp", address + std::to_string(port));
  while (true) {
    int conn = net::Accept(_socketfd);
    handleConnection(conn);
  }
}

void HTTPServer::handlerFunc(std::string path, void (*func)(Request request, Response res)) {
  handlerFuncs[path] = func;
}

void HTTPServer::handleConnection(int connfd) const {
  std::vector<char> buff(1028);
  int status = net::Read(connfd, buff);
  while (status != 0) {
    std::vector<char> newbuff(1028);
    status = net::Read(connfd, newbuff);
    buff.insert(buff.end(), newbuff.begin(), newbuff.end());
  }

  Request req = parse(buff); 
  Response res;  // need to work on initialization

  handlerFuncs.at(req.getPath())(req, res);
}


Request HTTPServer::parse(std::vector<char>& message) const {
  // TODO
}