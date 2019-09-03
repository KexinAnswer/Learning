#include "udp_client.hpp"

int main(int argc, char* argv[]){
  if(argc != 2){
    printf("Usage ./client [ip] \n");
  }
  UdpClient client(argv[1],9090);

  while(1){
    printf("请输入:");
    fflush(stdout);
    char req[1024] = {0};
    scanf("%s", req);
    
    client.SendTo(req);
    std::string resp;
    client.RecvFrom(&resp);
    printf("resp: %s\n", resp.c_str());
  }

  return 0;
}
