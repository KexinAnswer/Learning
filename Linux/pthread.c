// 线程控制的相关函数
// 1. 创建线程
// 2. 终止线程
// 3. 等待线程
// 4. 线程分离


#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int g_count = 0;

void* pthreadEntry(void* arg){
  int count = 5;
  while(count--){
    printf("I am thread g_count = %d\n", g_count++);
    pthread_t self = pthread_self();
    printf("pthread_self = %lu\n", self);
    sleep(1);
  }
}

int main(){
  pthread_t tid;
  // 第二个参数设置线程属性
  // 第三个为 void* 的函数指针
  pthread_create(&tid, NULL,pthreadEntry, NULL );

  // pthread_join(tid, NULL);
  while(1){
    sleep(1);
    printf("I am main\n");
  }

  // pthread_join(tid, NULL);

  return 0;
}
