#pragma once
#include <cstdio>
#include <cstring>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class TcpSocket{
public:
  TcpSocket()
    :fd_(-1){

    }
  bool Socket(){
    fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if(fd_ < 0){
      perror("socket");
      return false;
    }
    return true;
  }

  bool Bind(const std::string& ip, uint16_t port){
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip.c_str());
    addr.sin_port = htons(port);
    int ret = bind(fd_, (sockaddr*)&addr, sizeof(addr));
    if(ret < 0){
      perror("Bind");
      return false;
    }
    return true;
  }

  bool Listen(){
    int ret = listen(fd_,10);
    if(ret < 0){
      perror("listen");
      return false;
    }
    return true;
  }

  bool Accept(TcpSocket* peer, std::string* ip = NULL, uint16_t* port = NULL){
    sockaddr_in peer_addr;
    socklen_t len = sizeof(peer_addr);
    int client_sock = accept(fd_, (sockaddr*)peer,&len);
    if(client_sock < 0){
      perror("accept");
      return false;
    }
    peer->fd_ = client_sock;

    if(ip != NULL){
      *ip = inet_ntoa(peer_addr.sin_addr);
    }
    if(port != NULL){
      *port = ntohs(peer_addr.sin_port);
    }
    return true;
  }

  int Recv(std::string* msg){
    msg->clear();
    char buf[1024 * 10] = {0};
    ssize_t n = recv(fd_, buf, sizeof(buf)-1, 0);
    if(n < 0){
      perror("recv");
      return -1;
    }else if(n == 0){
      return 0;
    }else{
      msg->assign(buf);
      return 1;
    }
  }
  bool Send(const std::string msg){
    ssize_t n = send(fd_, msg.c_str(), msg.size(), 0);
    if(n < 0){
      perror("send");
      return false;
    }
    return true;
  }

  bool Connect(const std::string& ip, uint16_t port){
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip.c_str());
    addr.sin_port = htons(port);
    int ret = connect(fd_, (sockaddr*)&addr, sizeof(addr));
    if(ret < 0){
      perror("connect");
      return false;
    }
    return true;
  }

  bool Close(){
    if(fd_ != -1){
      close(fd_);
    }
    return true;
  }

private:
  int fd_;
};
