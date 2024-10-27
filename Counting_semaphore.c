#include<stdio.h>
#include<semaphore.h>
#include<unistd.h>
#include<pthread.h>
sem_t semaphore;
int count=0;
void *access_resource(void *arg){
    int thread_num = *((int*)(arg));
    sem_wait(&semaphore);
    sleep(3);
    count++;
    printf("%d thread is accessing resource count %d\n",thread_num, count);
    sem_post(&semaphore);
}
int main(){
    pthread_t t[5];
    int pthread_num[]={1,2,3,4,5};
    sem_init(&semaphore, 0, 4);
    for(int i=0;i<5;i++)
        pthread_create(&t[i],NULL,access_resource,&pthread_num[i]);
    for(int i=0;i<5;i++)
        pthread_join(t[i], NULL);
    sem_destroy(&semaphore);
    return 0;
}