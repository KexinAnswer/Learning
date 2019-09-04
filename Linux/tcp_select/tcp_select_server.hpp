#pragma once
#include <vector>
#include <unordered_map>
#include <functional>
#include <sys/select.h>
#include "tcp_socket.hpp"

inline void PrintFdSet(fd_set* fds, int max_fd){
  printf("select fds:");
  for(int i = 0; i < max_fd + 1; ++i){
    if(!FD_ISSET(i, fds)){
      continue;
    }
    printf("%d ", i);
  }
  printf("\n");
}

typedef std::function<void (const std::string& req, std::string* resp)> Handler;

class Selector{
public:
  Selector(){
    max_fd_ = 0;
    FD_ZERO(&read_fds_);
  }

  bool Add(const TcpSocket& sock){
    int fd = sock.GetFd();
    printf("[Selector::Add] %d\n", fd);
    if(fd_map_.find(fd) != fd_map_.end()){
      printf("Add failed! fd has in Selector\n");
      return false;
    }
    fd_map_[fd] = sock;
    FD_SET(fd, &read_fds_);
    if(fd > max_fd_){
      max_fd_ = fd;
    }
    return true;
  }

  bool Del(const TcpSocket& sock){
    int fd = sock.GetFd();
    printf("[Selector::Del] %d\n", fd);
    if(fd_map_.find(fd) != fd_map_.end()){
      printf("Del failed! fd has not in Selector\n");
      return false;
    }
    fd_map_.erase(fd);
    FD_CLR(fd, &read_fds_);

    // 重新找到最大的文件描述符
    for(int i = max_fd_; i >= 0; --i){
      if(!FD_ISSET(i, &read_fds_)){
        continue;
      }
      max_fd_ = i;
      break;
    }
    return true;
  }

  bool Wait(std::vector<TcpSocket>* output){
    output->clear();
    // 创建一个临时变量 否则原来的结构会被覆盖掉
    fd_set tmp = read_fds_;

    // DEBUG
    // PrintFdSet(&tmp, max_fd_ + 1);
    
    int nfds = select(max_fd_ + 1, &tmp, NULL, NULL, NULL);
    if(nfds < 0){
      perror("select");
      return false;
    }
    for(int i = 0; i < max_fd_ + 1; ++i){
      if(!FD_ISSET(i, &tmp)){
        continue;
      }
      output->push_back(fd_map_[i]);
    }
    return true;
  }
  
private:
  fd_set read_fds_;
  int max_fd_;
  std::unordered_map<int, TcpSocket> fd_map_;
};

class TcpSelectServer{
public:
  TcpSelectServer(const std::string& ip, uint16_t port)
    :ip_(ip)
    ,port_(port){}

  bool Start(Handler handler){
    // 1. 创建socket
    TcpSocket listen_sock;
    bool ret = listen_sock.Socket();
    if(!ret){
      return false;
    }

    // 2. 绑定端口号
    ret = listen_sock.Bind(ip_,port_);
    if(!ret){
      return false;
    }
    // 3. 进行监听
    ret = listen_sock.Listen();
    if(!ret){
      return false;
    }
    // 4. 创建 Selector 对象
    Selector selector;
    selector.Add(listen_sock);
    // 5. 进入循环事件
    while(1){
      std::vector<TcpSocket> output;
      bool ret = selector.Wait(&output);
      if(!ret){
        continue;
      }
      // 6. 根据就绪的文件描述符的差别，决定后续的处理逻辑
      for(size_t i = 0; i < output.size(); ++i){
        if(output[i].GetFd() == listen_sock.GetFd()){
          // 如果就绪的文件描述符是 listen_sock 就执行 accept 并加入到 selector 中
          TcpSocket newsock;
          listen_sock.Accept(&newsock, NULL, NULL);
          selector.Add(newsock);
        }else{
          // 如果就绪的文件描述符是 new_sock 那就进行一次请求的处理
          std::string req, resp;
          bool ret = output[i].Recv(&req);
          if(!ret){
            selector.Del(output[i]);
            output[i].Close();
            continue;
          }
          // 调用业务函数计算响应
          handler(req, &resp);
          output[i].Send(resp);
        } // end else
      } // end for

    } // end while
    return true;
  }

private:
  std::string ip_;
  uint16_t port_;
};
