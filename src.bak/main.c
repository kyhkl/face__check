#include "config.h"
int main(int argc , char * argv[])
{
    pthread_t id; 
    int ret;
    int test = 10;
    srand( (unsigned)time( NULL ) );  
     
    ret = pthread_create(&id, NULL, capture_thread1, (void *)&test);//线程创建函数
    if(ret)  //主线程
    {
        perror("pthread create error");
        return -1;
    }  

    pthread_join(id,NULL);
}
