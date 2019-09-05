#pragma once
#include <vector>
#include <functional>
#include <sys/epoll.h>
#include "tcp_socket.hpp"

#define CHECK_RET(exp) if(!(exp)){ \
  return false; \
}

typedef std::function<void (const std::string& req, std::string* resp)> Handler;

class Epoll{
public:
  Epoll(){
    epoll_fd_ = epoll_create(10);
  }

  ~Epoll(){
    close(epoll_fd_);
  }

  bool Add(const TcpSocket& sock){
    int fd = sock.GetFd();
    printf("[Epoll Add] fd = %d\n", fd);
    epoll_event ev;
    ev.data.fd = fd;
    ev.events = EPOLLIN;
    int ret = epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, fd, &ev);
    if(ret < 0){
      perror("epoll_ctl ADD");
      return false;
    }
    return true;
  }

  bool Del(const TcpSocket& sock){
    int fd = sock.GetFd();
    printf("[Epoll Del] fd = %d\n", fd);
    int ret = epoll_ctl(epoll_fd_, EPOLL_CTL_DEL, fd, NULL);
    if(ret < 0){
      perror("epoll_ctl DEL");
      return false;
    }
    return true;
  }

  bool Wait(std::vector<TcpSocket>* output){
    output->clear();
    epoll_event events[1000];
    int nfds = epoll_wait(epoll_fd_, events, sizeof(events)/sizeof(events[0]), -1);
    if(nfds < 0){
      perror("epoll_wait");
      return false;
    }
    for(int i = 0; i < nfds; ++i){
      TcpSocket sock(events[i].data.fd);
      output->push_back(sock);
    }
    return true;
  }

private:
  int epoll_fd_;
};

class TcpEpollServer{
public:
  TcpEpollServer(const std::string& ip, uint16_t port)
    :ip_(ip)
    ,port_(port){}
  bool Start(Handler handler){
    // 1. 创建一个socket
    TcpSocket listen_sock;
    CHECK_RET(listen_sock.Socket())
    // 2. 绑定端口号
    CHECK_RET(listen_sock.Bind(ip_,port_));
    // 3. 进行监听
    CHECK_RET(listen_sock.Listen());
    // 4. 创建一个 epoll 对象
    Epoll epoll;
    epoll.Add(listen_sock);
    // 5. 进入主循环
    while(1){
      // 6. 进行 epoll_wait
      std::vector<TcpSocket> output;
      if(!epoll.Wait(&output)){
        continue;
      }
      // 7. 根据就绪的文件描述符的种类决定如何处理
      for(size_t i = 0; i < output.size(); ++i){
        if(output[i].GetFd() == listen_sock.GetFd()){
          TcpSocket new_sock;
          listen_sock.Accept(&new_sock);
          epoll.Add(new_sock);
        }else{
          // 如果是 new_sock, 就进行一次读写
          std::string req;
          std::string resp;
          bool ret = output[i].Recv(&req);
          if(!ret){
            // 需要把不用的 socket 关闭
            epoll.Del(output[i]);
            output[i].Close();
            continue;
          }
          handler(req, &resp); 
          output[i].Send(resp);
        }

      } // end for
    } // end while
  } // end function Start
private:
  std::string ip_;
  uint16_t port_;
};
