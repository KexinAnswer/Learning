/*=============================================================== 
*   Copyright (C) . All rights reserved.")
*   文件名称： 
*   创 建 者：zhang
*   创建日期：
*   描    述：线程终止 
*       
================================================================*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *thr_start(void *arg)
{
    //pthread_self(void)
    //  获取调用线程ID
    pthread_detach(pthread_self());
    sleep(5);
    pthread_exit("nihaoa~~");
    while(1) {
        printf("i am ordinary thread\n");
        sleep(1);
        //void pthread_exit(void *retval);
        //退出调用线程，谁调用，谁退出
        //retval:   线程退出返回值
        //pthread_exit(NULL);
    }
    return NULL;
}
int main (int argc, char *argv[])
{
    pthread_t tid;

    int ret = pthread_create(&tid, NULL, thr_start, NULL);
    if (ret != 0) {
        printf("thread create error\n");
        return -1;
    }
    //int pthread_cancel(pthread_t thread);
    //  取消线程，退出的线程被动取消
    //  thread：    要取消的线程id
    //pthread_cancel(tid);
    
    //int pthread_join(pthread_t thread, void **retval);
    //  阻塞等待指定线程退出
    //  thread：    线程id
    //  retval：    用于获取线程退出返回值
    
    //int pthread_detach(pthread_t thread);
    //  分离指定的线程
    pthread_detach(tid);

    char *ptr = NULL;
    pthread_join(tid, (void**)&ptr);
    printf("ordinary thread exit val:%s\n", ptr);
    while(1) {
        printf("i am main thread\n");
        sleep(1);
    }
    return 0;
}
