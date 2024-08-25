#include "../include/reqReader.hpp"
#include "../include/net.hpp"
#include <string>

#define FAILURE 0
#define SUCCESS 1

reqReader::reqReader(int connfd) : _connfd(connfd)
{ }

std::optional<Request> reqReader::read() {
  int status = net::Read(_connfd, _buff);
  while (status != 0) {
    std::vector<char> newbuff(1028);
    status = net::Read(_connfd, newbuff);
    _buff.insert(_buff.end(), newbuff.begin(), newbuff.end());
  }
  
  std::string method = readNextWord();
  std::string target = readNextWord();
  std::string protocol = readNextWord();
  if (!readCRLF())
    return std::nullopt;

  _req.setMethod(method);
  _req.setTarget(target);
  _req.setProtocol(protocol);

  // reading headers
  while (true) {
    if (readHeader() == FAILURE) {
      return std::nullopt;
    }

    if (_buff[_idx] == '\r') {
      break;
    }
  }
  if (readCRLF() == FAILURE)
    return std::nullopt;
  if (readCRLF() == FAILURE)
    return std::nullopt;
  // reading body
  std::string body(_buff.begin() + _idx, _buff.end());
  _req.addToBody(body);

  return std::optional<Request>{ _req };
}

std::string reqReader::readNextWord() {
  std::string curr_word;
  while (_idx < _buff.size() && _buff[_idx] != ' ') {
    curr_word += _buff[_idx];
    ++_idx;
  }
  ++_idx;
  return curr_word;
}

int reqReader::readHeader() {
  std::string name = readNextWord();
  name = name.substr(0, name.length() - 1); // remove the :
  std::string arg = readNextWord();
  if (!readCRLF())
    return FAILURE;
  _req.addHeader(name, arg);
  return SUCCESS;

}

int reqReader::readCRLF() {
  if (_buff[_idx] != '\r')
    return FAILURE;
  ++_idx;
  if (_buff[_idx] != '\n')
    return FAILURE;
  ++_idx;
  return SUCCESS;
}
