#include <unordered_map>
#include "tcp_thread_server.hpp"
// #include "tcp_process_server.hpp"
// #include "tcp_server.hpp"


int main(){
  TcpThreadServer server;
  server.Start("0.0.0.0", 9090, [](const std::string& req, std::string* resp){
    *resp = req;
  });
  return 0;

  return 0;
}

