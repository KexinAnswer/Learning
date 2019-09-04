#include <unordered_map>
#include "tcp_select_server.hpp"
//#include "tcp_thread_server.hpp"
// #include "tcp_process_server.hpp"
// #include "tcp_server.hpp"


int main(){
  TcpSelectServer server("0.0.0.0", 9090);
  server.Start( [](const std::string& req, std::string* resp){
    *resp = req;
  });
  return 0;

  return 0;
}

