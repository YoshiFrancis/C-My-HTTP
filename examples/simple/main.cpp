#include "../../include/http.hpp"

int main(int argc, char* argv[]) {
	http server;
  server.listenAndServe("127.0.0.0", 8000);
}

void handleIndex(Request& req, Response& res) {
  res.writeHeader("hello", "world");
  res.writeStatus(Response::StatusCode::OK); // would like to move this enum to http class
  res.write("YOSHI WAS HERE");
}
