#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<semaphore.h>
#define MAX 10
int count=0;
//pthread_mutex_t mutex;
//pthread_cond_t cond_even;
//pthread_cond_t cond_odd;
sem_t sem;
void *even(void *arg){
    while(count <= MAX){
        //pthread_mutex_lock(&mutex);
        sleep(2);
        if(count%2 != 0){
            sem_wait(&sem);
            //pthread_cond_wait(&cond_even, &mutex);
        }
        if(count <= MAX){
            printf("even thread %ld: count %d\n", pthread_self(), count);
            count++;
        }
        sem_post(&sem);
        //(&mutex);
    }
}
void *odd(void *arg){
    while(count <= MAX){
        //pthread_mutex_lock(&mutex);
        sleep(2);
        if(count%2 == 0){
            sem_wait(&sem);
        }
        if(count <= MAX){
            printf("odd thread %ld: count %d\n", pthread_self(), count);
            count++;
        }
        sem_post(&sem);
        //pthread_cond_signal(&cond_even);
        //pthread_mutex_unlock(&mutex);
    }
}
int main(){
    //pthread_mutex_init(&mutex, NULL);
    //pthread_cond_init(&cond_even, NULL);
    //pthread_cond_init(&cond_odd, NULL);
    sem_init(&sem, 0, 0);
    pthread_t t1,t2;
    pthread_create(&t1, NULL, even, NULL);
    pthread_create(&t2, NULL, odd, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    //pthread_mutex_destroy(&mutex);
    //pthread_cond_destroy(&cond_even);
    //pthread_cond_destroy(&cond_odd);
    sem_destroy(&sem);
    return 0;
}