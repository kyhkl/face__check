#include <stdio.h>
#include <pthread.h>


//总共是10个整数，使用子线程来修改它的内容。实现只所有的内容都会完全修改了一次之后
//才能被主线程读取并输出。
pthread_mutex_t mutex;//定义一个互斥锁变量
int a[10]={0};
void * do_work(void * arg)
{
    int i = 0;
    printf("child thread\n");
	while(1)
	{
		pthread_mutex_lock(&mutex);//上锁
		for ( i = 0; i < 10; ++i)
		{
			a[i]++;
			sleep(1);
		}
		pthread_mutex_unlock(&mutex);//解锁
		sleep(1);
	}
    printf("child put lock\n");
    pthread_exit(0);
}

int main(void)
{
    pthread_t id;
	int i;
    pthread_mutex_init(&mutex,NULL);//动态地初始化互斥锁
    pthread_create(&id,NULL,do_work,NULL);
    while(1)
    {
		pthread_mutex_lock(&mutex);
        for ( i = 0; i < 10; ++i)
        {
            printf("%d ", a[i]);
        }
        printf("\n");
		pthread_mutex_unlock(&mutex);
        sleep(1);
    }    
    printf("main thread put lock\n");
    
    pthread_join(id,NULL);
    pthread_mutex_destroy(&mutex);
    printf("main exit");
    return 0;
}
