#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <semaphore.h>

#define MaxItems 2
#define BufferSize 2

sem_t avail;
sem_t fill;
int in = 0;
int out = 0;
int buffer[BufferSize];
pthread_mutex_t mutex;

void *producer(void *pro) {
    int item;
    for(int i = 0; i < MaxItems; i++){
        item = rand();
        sem_wait(&avail);
        pthread_mutex_lock(&mutex);
        buffer[in] = item;
        printf("Producer%d: create items %d at %d\n", *((int *)pro),buffer[in],in);
        in = (in+1)%BUFSIZ;
        pthread_mutex_unlock(&mutex);
        sem_post(&fill);
    }
}

void *consumer(void *con){
    for(int i = 0; i < MaxItems; i++) {
        sem_wait(&fill);
        pthread_mutex_lock(&mutex);
        int item = buffer[out];
        printf("Consumer %d:Remove Item %d from %d\n",*((int *)con),item,out);
        out = (out+1)%BufferSize;
        pthread_mutex_unlock(&mutex);
        sem_post(&avail);
    }
}

int main() {
    int shm_fd = shm_open("table", O_RDWR, 0666);
    int* table = mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    pthread_t prod[2],cons[2];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&avail,0,BUFSIZ);
    sem_init(&fill,0,0);

    int a[2] = {1,2};
    for(int i = 0; i < 2; i++) {
        pthread_create(&prod[i], NULL, (void *)producer,(void *)&a[i]);
    }
    for(int i = 0; i < 2; i++) {
        pthread_create(&cons[i], NULL, (void *)consumer,(void *)&a[i]);
    }
    for(int i = 0; i < 2; i++) {
        pthread_join(prod[i], NULL);
    }
    for(int i = 0; i < 2; i++) {
        pthread_join(cons[i], NULL);
    }
}

pthread_mutex_destroy(&mutex);
sem_destroy(&avail);
sem_destroy(&fill);
return 0;

}