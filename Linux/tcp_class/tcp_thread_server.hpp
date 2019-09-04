#pragma once
#include "tcp_socket.hpp"
#include <functional>

#define CHECK_RET(exp) if(!(exp)){ \
  return false; \
}


typedef std::function<void(const std::string& req, std::string* resp)>Handler;

class TcpThreadServer{
public:
  TcpThreadServer(){}

  ~TcpThreadServer(){
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
  struct ThreadEntryArg{
    TcpSocket client_socket;
    Handler handler;
    std::string ip;
    uint16_t port;
  };

  static void* ThreadEntry(void* arg){
    ThreadEntryArg* argument = (ThreadEntryArg*) arg;
    TcpSocket& client_sock = argument->client_socket;
    std::string& ip = argument->ip;
    uint16_t port = argument->port;
    Handler handler = argument->handler;
    while(1){
      // a) 读取请求
      std::string req;
      int r = client_sock.Recv(&req);
      if(r < 0){
        continue;
      }
      if(r == 0){
        client_sock.Close();
        printf("[%s:%d]对端关闭了连接!\n",ip.c_str(),port);
        break;
      }
      printf("[%s:%d] 客户端发送了: %s\n", ip.c_str(), port,req.c_str());
      // b) 根据请求计算响应
      std::string resp;
      handler(req,&resp);
      // c) 把响应写回客户端
      client_sock.Send(resp);
    }
    delete argument;

  }

  void ProcessConnect(TcpSocket& client_socket,Handler handler, const std::string&ip, uint16_t port){
    pthread_t tid;
    ThreadEntryArg* arg = new ThreadEntryArg;
    arg->client_socket = client_socket;
    arg->handler = handler;
    arg->port = port;
    arg->ip = ip;
    pthread_create(&tid, NULL , ThreadEntry, (void*)arg);
    pthread_detach(tid);
  }

private:
  TcpSocket listen_socket_;
};
