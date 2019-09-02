// UDP SERVER

#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(){
  // 1.创建一个socket
  int sock = socket(AF_INET, SOCK_DGRAM, 0);
  if(sock < 0){
    perror("socket");
    return 1;
  }
  // 2. 准备 sockaddr_in
  sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  server_addr.sin_port = htons(9090);

  // 3. 客户端直接发送数据
  while(1){
    char buf[1024] = {0};
    printf("请输入一段内容:");
    fflush(stdout);
    scanf("%s", buf);
    ssize_t n = sendto(sock, buf, strlen(buf), 0 , (sockaddr*)&server_addr, sizeof(server_addr));
    if(n < 0){
      perror("sendto");
      continue;
    }
    char buf_output[1024] = {0};
    n = recvfrom(sock, buf_output, sizeof(buf_output)-1, 0 , NULL, NULL);
    if(n < 0){
      perror("sendto");
      continue;
    }
    printf("server resp: %s\n", buf_output);
  }
  return 0;
  
}
