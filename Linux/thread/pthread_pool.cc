//////////////////////////////////////////////////////////////
//
// 线程池的实现
// 创建任务类
// 创建线程池类
//  1. 创建线程
//  2. 创建线程安全队列
//
//////////////////////////////////////////////////////////////

#include <iostream>
#include <queue>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>

typedef bool (*task_callback)(int data);

class Task{
public:
  Task(){
  }
  
  Task(int data, task_callback handler){
    _data = data;
    _handler = handler;
  }

  ~Task(){
  }

public:
  void SetTask(int data, task_callback handler){
    _data = data;
    _handler = handler;
  }

  bool Run(){
    return _handler(_data);
  }
private:
  int _data;
  task_callback _handler;
};

#define MAX_THR 5
#define MAX_QUE 10

class ThreadPool{
public:
  ThreadPool(int qmax = MAX_QUE, int tmax = MAX_THR)
    :_thr_max(tmax)
    ,_thr_cur(tmax)
    ,_capacity(qmax){
      pthread_mutex_init(&_mutex, NULL);
      pthread_cond_init(&_cond_con, NULL);
      pthread_cond_init(&_cond_pro, NULL);
    }

  ~ThreadPool(){
    pthread_mutex_destroy(&_mutex);
    pthread_cond_destroy(&_cond_con);
    pthread_cond_destroy(&_cond_pro);
  }
public:
  static void* thr_start(void* arg){
    ThreadPool* pool = (ThreadPool*) arg;

    while(1){
      pool->QueueLock();
      while(pool->QueueIsEmpty()){
        pool->ConWait();
      }
    }
    Task tt;
    pool->QueuePop(&tt);
    pool->ProWakeUp();
    pool->QueueLock();
    // 为防止处理时间过长导致其他线程无法获取锁
    // 因此解锁之后才进行处理
    tt. Run();
  }

  bool ThreadPoolInit(){
    pthread_t tid;
    int ret , i;
    for(i = 0; i < _thr_max; ++i){
      ret = pthread_create(&tid, NULL, thr_start,(void*)this);
      if(ret != 0){
        std::cout << "thread create error!\n";
        return false;
      }
      pthread_detach(tid);
    }
    return true;
  }

  void AddTask(Task tt){
    // 向线程池添加任务
    QueueLock();
    while(QueueIsFull()){
      ProWait();
    }

    QueuePush(tt);
    ConWakeUp();
    QueueUnLock();
  }

  void ThreadPoolQuit(){
    // 退出线程池中所有的线程
    _quit_flag = true;
    while(_thr_cur > 0){
      ConWakeUpAll();
      usleep(1000);
    }
    return;
  }
     
private:
  void QueuePush(Task tt){
    _queue.push(tt);
  }

  void QueuePop(Task* tt){
    *tt = _queue.front();
    _queue.pop();
  }

  void QueueLock(){
    pthread_mutex_lock(&_mutex);
  }

  void QueueUnLock(){
    pthread_mutex_unlock(&_mutex);
  }

  void ProWait(){
    pthread_cond_wait(&_cond_pro, &_mutex);
  }

  void ProWakeUp(){
    pthread_cond_signal(&_cond_pro);
  }

  void ConWait(){
    // 进入这个函数表示没有任务
    if(_quit_flag == true){
      // 若线程池要求退出
      _thr_cur--;

      std::cout << "thread:" << pthread_self() << "exit\n";

      pthread_mutex_unlock(&_mutex);
      pthread_exit(NULL);
    }

    pthread_cond_wait(&_cond_con, &_mutex);
  }

  void ConWakeUp(){
    pthread_cond_signal(&_cond_con);
  }

  void ConWakeUpAll(){
    pthread_cond_broadcast(&_cond_con);
  }

  bool QueueIsFull(){
    return (_queue.size() == _capacity);
  }

  bool QueueIsEmpty(){
    return (_queue.size() == 0);
  }

private:
  int _thr_max;
  int _thr_cur;
  bool _quit_flag;
  std::queue<Task> _queue;
  int _capacity;
  pthread_mutex_t _mutex;
  pthread_cond_t _cond_pro;
  pthread_cond_t _cond_con;
};


bool task_handler(int data){
  srand(time(NULL));
  int sec = rand() % 5;
  std::cout << "thread:" << pthread_self() << "sleep" << sec << "second" << std::endl;
  sleep(sec);
  return true;
}

int main(){
  ThreadPool pool;
  Task tt[10];

  pool.ThreadPoolInit();
  int i ;
  for(i = 0; i < 10; ++i){
    tt[i].SetTask(i, task_handler);
    pool.AddTask(tt[i]);
  }

  pool.ThreadPoolQuit();
  return 0;
}























