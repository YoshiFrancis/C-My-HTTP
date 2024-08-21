#include "../include/server.hpp"


HTTPServer::HTTPServer(std::string ip, int port) {

}

HTTPServer::~HTTPServer() {

}

void HTTPServer::listenAndServe(std::string address, int port) {
  
}

void HTTPServer::handlerFunc(std::string path, void (*func)(std::string request, int responseSocket)) {
  handlerFuncs[path] = func;
}

void HTTPServer::handleConnection(int newfd) const {
  
}


void parse(std::vector<char>& message) {

}