#include <stdio.h>
#include <pthread.h>

void *p_main(void *arg)
{
    printf("this is pthread\n");
    sleep(3);
    printf("after sleep\n");
}

int main(void)
{
    pthread_t id;
    int ret;

    ret = pthread_create(&id, NULL, p_main, NULL);
    if(ret)
    {
        perror("pthread create");
        return -1;
    }

    sleep(1);
    pthread_cancel(id);

    sleep(3);

    return 0;
}
