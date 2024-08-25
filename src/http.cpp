#include "../include/http.hpp"
#include "../include/net.hpp"
#include "../include/request.hpp"
#include "../include/response.hpp"
#include "../include/reqReader.hpp"
#include <string>
#include <iostream>

http::~http() {
  net::Close(_socketfd);
}

void http::listenAndServe(std::string address, int port) {
  _socketfd = net::Listen("tcp", address + std::to_string(port));
  while (true) {
    int conn = net::Accept(_socketfd);
    handleConnection(conn);
  }
}

void http::handlerFunc(std::string path, void (*func)(Request& request, Response& res)) {
  handlerFuncs[path] = func;
}

void http::handleConnection(int connfd) const {
  reqReader r(connfd);
  std::optional<Request> req = r.read();
  if (!req.has_value())
    return;
  Response res;  // need to work on initialization

  handlerFuncs.at(req.value().getTarget())(req.value(), res);
  net::Send(connfd, res.serialize());
}
