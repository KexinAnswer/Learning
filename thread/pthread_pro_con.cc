///////////////////////////////////////////////////////////////
// 生产者 消费者模型
//   1. 实现线程安全的队列，对外提供线程安全的数据入队出队操作
//   2. 创建线程，分别作为生产者与消费者数据入队或者数据出队
///////////////////////////////////////////////////////////////


#include <iostream>
#include <unistd.h>
#include <queue>
#include <pthread.h>

#define MAX_QUEUE 10

class BlockQueue{
public:
  BlockQueue(int capacity = MAX_QUEUE)
    :_capacity(capacity){
      pthread_mutex_init(&_mutex, NULL);
      pthread_cond_init(&_cond_pro , NULL);
      pthread_cond_init(&_cond_con,NULL);
    }

  ~BlockQueue(){
    pthread_mutex_destroy(&_mutex);
    pthread_cond_destroy(&_cond_pro);
    pthread_cond_destroy(&_cond_con);
  }

  void QueuePush(int data){
    QueueLock();
    while(QueueIsFull()){
      ProWait();
    }
    _queue.push(data);;
    ConWakeUp();
    QueueUnLock();
  }

  void QueuePop(int* data){
    QueueLock();
    while(QueueIsEmpty()){
      ConWait();
    }
    *data = _queue.front();
    _queue.pop();
    ProWakeUp();
    QueueUnLock();
  }

private:
  void QueueLock(){
    pthread_mutex_lock(&_mutex);
  }

  void QueueUnLock(){
    pthread_mutex_unlock(&_mutex);
  }

  void ConWait(){
    pthread_cond_wait(&_cond_con,&_mutex);
  }

  void ConWakeUp(){
    pthread_cond_signal(&_cond_con);
  }

  void ProWait(){
    pthread_cond_wait(&_cond_pro, &_mutex);
  }

  void ProWakeUp(){
    pthread_cond_signal(&_cond_pro);
  }

  bool QueueIsFull(){
    return (_queue.size() == _capacity);
  }

  bool QueueIsEmpty(){
    return (_queue.size() == 0);
  }
private:
  std::queue<int> _queue;
  int _capacity;  // 队列中节点最大数量

  // 线程安全实现成员
  pthread_mutex_t _mutex;
  pthread_cond_t _cond_pro;
  pthread_cond_t _cond_con;
};

void* thr_consumer(void* arg){
  BlockQueue* q = (BlockQueue*) arg;
  while(1){
    int data;
    q->QueuePop(&data);
    std::cout << "consumer" << pthread_self() << "get data:" << data << std::endl;
  }
  return NULL;
}

int i = 0;
pthread_mutex_t mutex;

void* thr_productor(void* arg){
  BlockQueue* q = (BlockQueue*) arg;
  while(1){
    pthread_mutex_lock(&mutex);
    q->QueuePush(i++);
    std::cout << "productor:" << pthread_self() << "put data" << i << std::endl;
    pthread_mutex_unlock(&mutex);
  }

  return NULL;
}


int main() {
  BlockQueue q;

  pthread_t ctid[4], ptid[4];
  int i, ret;

  pthread_mutex_init(&mutex, NULL);
  for(i = 0; i < 4; ++i){
    ret = pthread_create(&ctid[i], NULL, thr_consumer, (void*)&q);
    if(ret != 0){
      printf("pthread create failed\n");
      return 1;
    }
  }

  for(i = 0; i < 4; ++i){
    ret = pthread_create(&ptid[i], NULL, thr_productor, (void*)&q);
    if(ret != 0){
      printf("pthread create failed\n");
      return 1;
    }
  }

  for(i = 0; i < 4; ++i){
    pthread_join(ctid[i], NULL);
  }
  for(i = 0; i < 4; ++i){
    pthread_join(ptid[i], NULL);
  }
  pthread_mutex_destroy(&mutex);
  return 0;

}


