#include <stdio.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <string.h>

char buffer[128];

void * p_main(void * arg)
{
    printf("this is child pthread\n");
    printf("child,the tid = %lu\n",pthread_self());
    printf("getpid =%d \n",getpid());
    printf("child buffer:%s\n",buffer);
    printf("pass argv is %d\n",*(int *)arg);
    sleep(3);
    pthread_exit(NULL);   //线程退出   
}

//　　第一个参数为指向线程标识符的指针。
//　　第二个参数用来设置线程属性。
//　　第三个参数是线程运行函数的起始地址。
//　　最后一个参数是运行函数的参数

int main(void)
{
    pthread_t id; 
    int ret;
    int test = 10;
    ret = pthread_create(&id, NULL, p_main, (void *)&test);//线程创建函数
    if(ret)  //主线程
    {
        perror("pthread create");
        return -1;
    }    
    printf("parent: id is = %lu\n",id);
    printf("parent,the tid = %lu\n",pthread_self());
    printf("getpid =%d \n",getpid());
    memcpy(buffer,"pthread",8);
    printf("wait pthread\n");
    //等待所有的子线程执行完退出了，这时才退出主线程
    pthread_join(id,NULL);
    printf("pthread exit\n");
    
    return 0;
}

