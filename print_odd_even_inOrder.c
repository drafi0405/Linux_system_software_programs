#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#define MAX 10
pthread_mutex_t lock;
pthread_cond_t cond;
int turn = 0;
void *even(void *arg){
    for(int i=0;i<=MAX;i+=2){
        pthread_mutex_lock(&lock);
        while(turn != 0){
            pthread_cond_wait(&cond, &lock);
        }
        printf("even %d\n",i);
        turn=1;
        pthread_cond_signal(&cond);
        //usleep(100000);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}
void *odd(void *arg){
    for(int i=1;i<=MAX;i+=2){
        pthread_mutex_lock(&lock);
        while(turn!=1){
            pthread_cond_wait(&cond, &lock);
        }
        printf("odd %d\n",i);
        turn=0;
        pthread_cond_signal(&cond);
        //usleep(100000);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}
int main(){
    pthread_t t1,t2;
    pthread_mutex_init(&lock,NULL);
    pthread_cond_init(&cond,NULL);
    pthread_create(&t1, NULL, even, NULL);
    pthread_create(&t1, NULL, odd, NULL);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
    return 0;
}