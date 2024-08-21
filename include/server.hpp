#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <unordered_map>

class HTTPServer {
public:
  HTTPServer(std::string ip, int port);
  ~HTTPServer();

private:
  // socket file descriptor server is listeninig on
  int m_socketfd;
  // paths mapping to handler functions
  std::unordered_map<std::string, void (*)(std::string request, int responseSocket)> handlerFuncs;
public:
  void listenAndServe(std::string address, int port);
  void handlerFunc(std::string path, void (*func)(std::string request, int responseSocket));
private:
  void handleConnection(int socket) const;
  void parse(std::vector<char>& message);
};

#endif