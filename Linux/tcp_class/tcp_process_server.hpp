#pragma once
#include "tcp_socket.hpp"
#include <functional>

#define CHECK_RET(exp) if(!(exp)){ \
  return false; \
}


typedef std::function<void(const std::string& req, std::string* resp)>Handler;

class TcpProcessServer{
public:
  TcpProcessServer(){}

  ~TcpProcessServer(){
    listen_socket_.Close();
  }

  bool Start(const std::string& ip, uint16_t port, Handler handler){
    // 1. 创建一个 socket
    CHECK_RET(listen_socket_.Socket());
    // 2. 绑定 ip 和 端口号
    CHECK_RET(listen_socket_.Bind(ip,port));
    // 3. 进行监听
    CHECK_RET(listen_socket_.Listen());
    printf("Server Start!\n");
    // 4. 进入主循环
    while(true){
      TcpSocket client_socket;
      std::string ip;
      uint16_t port;
      bool ret = listen_socket_.Accept(&client_socket,&ip,&port);
      if(!ret){
        continue;
      }
      printf("[%s:%d]客户端建立了连接！\n", ip.c_str(),port);
      ProcessConnect(client_socket,handler,  ip, port);
    }
  }

private:
  void ProcessConnect(TcpSocket& client_socket, Handler handler, const std::string& ip, uint16_t port){
    // 1. 创建一个子进程
    pid_t ret = fork();
    // 2. 父进程直接结束这个函数
    if(ret > 0){
      // father
      client_socket.Close();
      return;
    }
    // 3. 子进程循环做以下事情
    while(true){
      // a) 读取请求
      std::string req;
      int r = client_socket.Recv(&req);
      if(r < 0){
        continue;
      }
      if(r == 0){
        client_socket.Close();
        printf("[%s:%d]对端关闭了连接!\n",ip.c_str(),port);
        break;
      }
      printf("[%s:%d] 客户端发送了: %s\n", ip.c_str(), port,req.c_str());
      // b) 根据请求计算响应
      std::string resp;
      handler(req,&resp);
      // c) 把响应写回客户端
      client_socket.Send(resp);
    }
    client_socket.Close();
    exit(0);
  }

private:
  TcpSocket listen_socket_;
};
