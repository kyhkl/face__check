#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>

#define MAX     5

pthread_mutex_t mutex;//定义互斥锁

/*
 *pthread_mutex_init(&mutex, NULL);
 *pthread_mutex_destroy(&mutex);
 */

void handler(int fd, char *name)
{
    int count = 0, i;
    char buf[1024];

    while (count < MAX)
    {
        pthread_mutex_lock(&mutex); //加锁，当一个线程占有该锁，则另一个要等待到占用锁的线程解锁
        snprintf(buf, sizeof(buf), "%s pthread_id %8x count = %5d\n", name, pthread_self(), count++);
        for (i = 0; i < strlen(buf); i++)
        {
            write(fd, &buf[i], 1);
            usleep(10);
        }
        pthread_mutex_unlock(&mutex);
        usleep(1);
    }
}

void *do_work(void *data)
{
    handler(*(int *)data, "child");//操作函数

    return NULL;
}

int main(int argc, char *argv[])
{
    int fd;
    pthread_t id;

    pthread_mutex_init(&mutex, NULL);

    fd = open("test_pthread", O_RDWR | O_CREAT | O_TRUNC);
    if (fd == -1)
        perror("open");

    if (pthread_create(&id, NULL, do_work, (void *)&fd))
        perror("pthread_create");

    handler(fd, "parent");//操作函数

    pthread_join(id, NULL);//阻塞主线程，等待子线程将最后一次循环执行
    
    return 0;
}
