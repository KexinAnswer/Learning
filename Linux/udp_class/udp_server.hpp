#pragma once

#include <cassert>
#include <functional>
#include "udp_socket.hpp"

typedef std::function<void(const std::string&, std::string*)>Handler;

class UdpServer{
public:
  UdpServer(){
    assert(sock_.Socket());
  }

  ~UdpServer(){
    sock_.Close();
  }

  bool Start(const std::string& ip, uint16_t port, Handler handler){
    bool ret = sock_.Bind(ip, port);
    if(!ret){
      return false;
    }

    while(1){
      std::string req;
      std::string peer_ip;
      uint16_t peer_port;
      sock_.RecvFrom(&req,&peer_ip, & peer_port);
      std::string resp;
      handler(req,&resp);
      sock_.SendTo(resp,peer_ip, peer_port);
    }
  }

private:
  UdpSocket sock_;
};

