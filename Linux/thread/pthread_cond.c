////////////////////////////////////////////////////////////////
// 吃面 / 做面 为例子实现条件变量的使用
// 实现线程间同步
////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int have_noodle = 0;
pthread_cond_t cond_eat;
pthread_cond_t cond_make;
pthread_mutex_t mutex;

void* eat_noodle(void* arg){
  while(1){
    pthread_mutex_lock(&mutex);
    while(have_noodle == 0){
      pthread_cond_wait(&cond_eat, &mutex);
    } // end while have_noodle == 0
    printf("delicious~~~\n");
    have_noodle = 0;
    // 再来一碗
    pthread_cond_signal(&cond_make);
    pthread_mutex_unlock(&mutex);
  } // end while 1
  return NULL;
} // end function eat_noodel

void* make_noodle(void* arg){
  while(1){
    while(have_noodle == 1){
      pthread_cond_wait(&cond_make,&mutex);
    }
    printf("make noodle~~~\n");
    have_noodle = 1;
    pthread_cond_signal(&cond_eat);
    pthread_mutex_unlock(&mutex);
  }

  return NULL;
}

int main(){
  pthread_t etid, mtid;
  int ret, i;
  // pthread_cond_init(pthread_t* restrict cond,
  //                   const pthread_condattr_t* restrict attr);
  // cond: 条件变量
  // attr: 条件属性 一般设置为 NULL 
  // pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
  
  pthread_cond_init(&cond_eat, NULL);
  pthread_cond_init(&cond_make, NULL);
  pthread_mutex_init(&mutex, NULL);

  for(i = 0; i < 4; ++i){
    ret = pthread_create(&etid, NULL, eat_noodle, NULL);
    if(ret != 0){
      printf("pthread create failed\n");
      return 1;
    }
  }
  for(i = 0; i < 4; ++i){
    ret = pthread_create(&mtid, NULL, make_noodle, NULL);
    if(ret != 0){
      printf("pthread create failed\n");
      return 1;
    }
  }

  pthread_join(etid,NULL);
  pthread_join(mtid,NULL);
    
  pthread_cond_destroy(&cond_eat);
  pthread_cond_destroy(&cond_make);
  pthread_mutex_destroy(&mutex);
    

}
