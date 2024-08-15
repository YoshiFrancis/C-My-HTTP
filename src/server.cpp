#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <unordered_map>

class HTTPServer {

private:
  int m_socket;
  // paths mapping to handler functions
  std::unordered_map<std::string, void (*)(std::string request, int responseSocket)> handlerFuncs;
public:
  void startListening(std::string address);
  void handleFunc(std::string path, void (*func)(std::string request, int responseSocket));
private:
  void runConnection(int socket) const;
};

#endif