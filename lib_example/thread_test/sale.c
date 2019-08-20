#include <stdio.h>
#include <pthread.h>
int ticketcount = 20;
pthread_mutex_t lock;
void* salewinds1(void* args)
{
    while(1)
    {
        pthread_mutex_lock(&lock); //因为要访问全局的共享变量，所以就要加锁
        if(ticketcount > 0)  //如果有票
        {
				printf("windows1 start sale ticket!the ticket is:%d\n",ticketcount);
            	sleep(3);
            	ticketcount --;
				printf("sale ticket finish!,the last ticket is:%d\n",ticketcount);
        }
        else
        {
            pthread_mutex_unlock(&lock);
            pthread_exit(NULL);
        }
        pthread_mutex_unlock(&lock);
        sleep(1);   	//要放到锁的外面，让另一个有时间锁
    }
}
void* salewinds2(void* args)
{
    while(1)
    {
        pthread_mutex_lock(&lock);
        if(ticketcount>0)
        {
				printf("windows2 start sale ticket!the ticket is:%d\n",ticketcount);
            	sleep(3);
            	ticketcount --;
				printf("sale ticket finish!,the last ticket is:%d\n",ticketcount);
        }
        else
        {
            pthread_mutex_unlock(&lock);
            pthread_exit(NULL);
        }
        pthread_mutex_unlock(&lock);
        sleep(1);
    }

}
int main()	
{
    pthread_t pthid1 = 0;
    pthread_t pthid2 = 0;
    pthread_mutex_init(&lock,NULL);   //初始化锁
    pthread_create(&pthid1,NULL,salewinds1,NULL);
    pthread_create(&pthid2,NULL,salewinds2,NULL);
    pthread_join(pthid1,NULL);
    pthread_join(pthid2,NULL);
    pthread_mutex_destroy(&lock);     //销毁锁
    return 0;
}