#include <cstdio>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <utility>
#include <vector>
#include <tuple>

namespace net {
  const int backlog = 15; // number of connections allowed

  int Listen(std::string protocol, std::string port) {
    int status;
    struct addrinfo hints;
    struct addrinfo *servinfo, *p;
    int listenfd;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    if (protocol == "tcp") {
      hints.ai_socktype = SOCK_STREAM;
    } else if (protocol == "udp") {
      hints.ai_socktype = SOCK_DGRAM;
    } else {
      printf("Invalid protocol");
      exit(1);
    }

    hints.ai_flags = AI_PASSIVE;

    if ((status = getaddrinfo(NULL, port.c_str(), &hints, &servinfo)) != 0) { // if you want specific IP, replace NULL with such
      fprintf(stderr, "getaddrinfo error: %s\n", strerror(status));
      exit(1);
    }

    for (p = servinfo; p != NULL; p = p->ai_next) {
      if ((listenfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)) == -1) {
        perror("Server: socket");
        continue;
      }
      
      if ((status = bind(listenfd, servinfo->ai_addr, servinfo->ai_addrlen)) == -1) {
        close(listenfd);
        perror("Server: bind");
        continue;
      }

      break;
    }

    freeaddrinfo(servinfo);

    if (p == NULL) {
      fprintf(stderr, "server: failed to start listening and bind\n");
      exit(1);
    }

    if ((status = listen(listenfd, backlog)) == -1) {
      fprintf(stderr, "listening error: %s\n", strerror(status));
      exit(1);
    }

    return listenfd;
  }

  int Accept(int listenfd) {
    struct sockaddr_storage their_addr;
    socklen_t addr_size = sizeof their_addr;
    int newfd;
    if ((newfd = accept(listenfd, (struct sockaddr*) &their_addr, &addr_size)) == -1) {
      fprintf(stderr, "accepting error: %s\n", strerror(newfd));
      return -1;
    } 

    return newfd;
  }

  int Read(int sockfd, std::vector<char>& buff) {
    int status = recv(sockfd, &buff, buff.size(), 0);
    if (status == -1) {
      fprintf(stderr, "reading error: %s\n", strerror(status));
      return status;
    } else if (status == 0) {
      printf("Connectiong has closed connection!");
      return status;
    }
    return 1;
  }

  int Send(int sockfd, const std::string& msg) {
    int sendAmount = msg.length();
    int bytes_sent = 0;
    int total_sent = 0;
    while (bytes_sent < sendAmount) {
      sendAmount -= bytes_sent;
      if ((bytes_sent = send(sockfd, msg.c_str() + total_sent, sendAmount, 0)) == -1) {
        fprintf(stderr, "sending error: %s\n", strerror(bytes_sent));
        return -1;
      }
      total_sent += bytes_sent;
    }
    return 0;
  }

  void Close(int sockfd) {
    close(sockfd);
  }


}