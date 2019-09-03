#include "tcp_client.hpp"

int main(int argc, char* argv[]){
  if(argc != 2){
    printf("Usage ./client [ip]\n");
  }

  TcpClient client;
  bool ret = client.Connect(argv[1], 9090);
  if(!ret){
    printf("Connect Failed!\n");
    return 1;
  }
  while(1){
    printf("请输入:");
    fflush(stdout);
    char req[1024] = {0};
    scanf("%s", req);
    client.Send(req);
    std::string resp;
    client.Recv(&resp);
  printf("resp:%s\n", resp.c_str());
  }
  return 0;
}
