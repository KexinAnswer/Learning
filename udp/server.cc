// UDP SERVER

#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(){
  // 1. 先创建一个一个 socket
  int sock = socket(AF_INET, SOCK_DGRAM, 0);
  if(sock < 0){
    perror("socket");
    return 1;
  }
  // 2. 把当前的 socket 绑定上一个 ip + 端口号
  sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr("0.0.0.0");
  addr.sin_port = htons(9090);
  int ret = bind(sock,(sockaddr*)&addr, sizeof(addr));
  if(ret < 0){
    perror("bind");
    return 1;
  }
  printf("server start!\n");
  // 3. 处理服务器接收到的请求
  while(true){
    // a) 读取客户请求
    // 面向数据包的函数接收
    sockaddr_in peer;
    socklen_t len = sizeof(peer);
    char buf [1024] = {0};
    ssize_t n = recvfrom(sock, buf, sizeof(buf)-1, 0, (sockaddr*)&peer, &len);
    if(n < 0){
      perror("recvfrom");
      continue;
    }
    buf[n] = '\0';
    printf("[%s:%d] buf : %s\n", inet_ntoa(peer.sin_addr), ntohs(peer.sin_port), buf);
    
    // b) 根据请求计算响应
    
    // c) 把响应写回客户端
    n = sendto(sock, buf, strlen(buf), 0, (sockaddr*)&peer, len);
    if(n < 0){
      perror("sendto");
      continue;
    }
  }
  // 4. 关闭 socket
  close(sock);
  return 0;
}
