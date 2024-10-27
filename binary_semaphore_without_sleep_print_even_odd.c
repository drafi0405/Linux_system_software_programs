#include<pthread.h>
#include<stdio.h>
#include<semaphore.h>
#define MAX 10
int count=0;
sem_t even_sem;
sem_t odd_sem;
void *even(void *arg){
    while(count <= MAX){
        sem_wait(&even_sem);
        if(count%2 == 0 && count<=MAX){
             printf("even thread %ld: count %d\n", pthread_self(), count);
             count++;
        }
        sem_post(&odd_sem);
    }
}
void *odd(void *arg){
    while(count <= MAX){
        sem_wait(&odd_sem);
        if(count%2 != 0 && count<=MAX){
            printf("odd thread %ld: count %d\n", pthread_self(), count);
            count++;
        }
        sem_post(&even_sem);
    }
}
int main(){
    sem_init(&even_sem, 0, 1);
    sem_init(&odd_sem, 0, 0);
    pthread_t t1,t2;
    pthread_create(&t1, NULL, even, NULL);
    pthread_create(&t2, NULL, odd, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    sem_destroy(&even_sem);
    sem_destroy(&odd_sem);
    return 0;
}