#include <stdio.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <signal.h>

void report1(int sig)
{
    printf("report 1:the sig is = %d\n,thread id = %lu\n",sig,pthread_self());
}

void report2(int sig)
{
    printf("report 2 :the sig is = %d\n,thread id = %lu\n",sig,pthread_self());
}


void * p_main1(void *arg)
{
    signal(SIGUSR1,report1);
    signal(SIGINT,report1);
    
    printf("child1,the tid = %lu,pid =%d \n",pthread_self(),getpid());
    while(1);
}

void *p_main2(void *arg)
{
    signal(SIGUSR1,report2);
    signal(SIGUSR2,report2);
    
    printf("child2,the tid = %lu,pid =%d \n",pthread_self(),getpid());
    while(1);
}


int main(void)
{
    pthread_t id1, id2;  //
    int ret;

    ret = pthread_create(&id1, NULL, p_main1, NULL);//线程创建函数
    if(ret)  //主线程
    {
        perror("pthread create");
        return -1;
    }
    
    ret = pthread_create(&id2, NULL, p_main2, NULL);//线程创建函数
    if(ret)  //主线程
    {
        perror("pthread create");
        return -1;
    }

    printf("parent,the tid = %lu,pid =%d \n",pthread_self(),getpid());
    sleep(5);
    pthread_kill(id1,SIGUSR1);
    sleep(5);
    pthread_kill(id2,SIGUSR1);

    sleep(5);
    pthread_kill(id2,SIGUSR2);
    sleep(5);
    pthread_kill(id1,SIGINT);   

    pthread_join(id1,NULL);
    pthread_join(id2,NULL);
    return 0;
}
