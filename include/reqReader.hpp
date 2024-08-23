#ifndef REQREADER_H
#define REQREADER_H

#include "request.hpp"
#include <vector>
#include <optional>

class reqReader {
private:
  int _connfd;
  std::vector<char> _buff;
  int _idx;
  Request _req;

public:
  reqReader(int connfd);
  std::optional<Request> read();

private:

  std::string readNextWord(); // places _idx on the beginning of the next word (one character after read space)
  int readHeader();
  int readCRLF();
};

#endif