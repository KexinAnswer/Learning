#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>

int ticket = 100;
pthread_mutex_t mutex;

void* pthreadEntry(void* arg){
  char* id = (char*)arg;
  while(1){
    pthread_mutex_lock(&mutex);
    if(ticket > 0){
      usleep(1000);
      printf("%s sells ticket: %d\n", id, ticket);
      ticket--;
      pthread_mutex_unlock(&mutex);
    }else{
      pthread_mutex_unlock(&mutex);
      break;
    }
  }
  return NULL;
}

int main(){
  pthread_t tid1;
  pthread_t tid2;
  pthread_t tid3;
  pthread_t tid4;

  pthread_mutex_init(&mutex, NULL);

  pthread_create(&tid1, NULL, pthreadEntry, "pthread1");
  pthread_create(&tid2, NULL, pthreadEntry, "pthread2");
  pthread_create(&tid3, NULL, pthreadEntry, "pthread3");
  pthread_create(&tid4, NULL, pthreadEntry, "pthread4");

  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  pthread_join(tid3, NULL);
  pthread_join(tid4, NULL);
  
  pthread_mutex_destroy(&mutex);

  return 0;
}

