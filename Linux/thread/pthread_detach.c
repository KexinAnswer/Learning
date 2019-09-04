#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void* pthreadEntry(void* arg){
  pthread_detach(pthread_self());
  int count = 5;
  while(count--){
    printf("pthread_detch\n");
    sleep(1);
  }

  return NULL;
}

int main(){
  pthread_t tid;
  pthread_create(&tid, NULL, pthreadEntry, NULL);
  sleep(1);
  printf("In main\n");

  int ret = 0;

  // if(pthread_join(tid, NULL)){
  //   printf("pthread wait success!\n");
  //   ret = 0;
  // }else{
  //   printf("pthread wait fail\n");
  //   ret = 1;
  // }

  return ret;
}
