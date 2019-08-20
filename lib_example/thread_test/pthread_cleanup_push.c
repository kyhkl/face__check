#include <stdio.h>
#include <pthread.h>

void clean1(void *arg)
{
    printf("in clean1: %d\n", (int)arg);
}

void clean2(void *arg)
{
    printf("in clean2: %d\n", (int)arg);
}

void clean3(void *arg)
{
    printf("in clean3: %d\n", (int)arg);
}

void *p_main(void *arg)
{
    int i;

    pthread_cleanup_push(clean1, (void *)1111);//注册这个函数在线程将要结束前执行
    pthread_cleanup_push(clean2, (void *)2222);//先注册的函数在后面执行
    pthread_cleanup_push(clean3, (void *)3333);//类似栈区的操作，先入后出

    for(i = 0; i < 3; i++)
    {
        printf("%d in p_main: i = %d\n",(int)arg, i);
        usleep(500 * 1000);
    }
    
    /*pthread_exit(0);  //在退出前没有执行POP函数，则之前注册的PUSH函数会全部执行*/
    
    pthread_cleanup_pop(1);//执行之前注册的函数 参数1：执行 参数0：忽略
    pthread_cleanup_pop(0);//执行之前注册的函数 参数1：执行 参数0：忽略
    pthread_cleanup_pop(1);//执行之前注册的函数 参数1：执行 参数0：忽略
    pthread_exit(0);
}


//线程同步

//尤其是对文件操作

//通过信号量




int main(void)
{
    int ret;
    pthread_t id;

    ret = pthread_create(&id, NULL, p_main, (void *)1234);
    if(ret)
    {
        perror("pthread_create");
        return -1;
    }

    pthread_join(id, NULL); //主线程阻塞，等待子线程执行完退出再继续下面操作
    return 0;
}

