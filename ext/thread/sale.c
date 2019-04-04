#include <stdio.h>
#include <pthread.h>
int ticketcount = 20;
pthread_mutex_t lock;
void* salewinds1(void* args)
{
    while(1)
    {
        pthread_mutex_lock(&lock); //��ΪҪ����ȫ�ֵĹ�����������Ծ�Ҫ����
        if(ticketcount > 0)  //�����Ʊ
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
        sleep(1);   	//Ҫ�ŵ��������棬����һ����ʱ����
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
    pthread_mutex_init(&lock,NULL);   //��ʼ����
    pthread_create(&pthid1,NULL,salewinds1,NULL);
    pthread_create(&pthid2,NULL,salewinds2,NULL);
    pthread_join(pthid1,NULL);
    pthread_join(pthid2,NULL);
    pthread_mutex_destroy(&lock);     //������
    return 0;
}