#include <stdio.h>
#include <pthread.h>
#define MAX 10
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_var = PTHREAD_COND_INITIALIZER;
int count = 1;

void *even(void *arg){
    while(count < MAX){
        pthread_mutex_lock(&mutex);
        
        if(count % 2 != 0){
            pthread_cond_wait(&cond_var, &mutex);
        }
        printf("print in even %d\n", count++);
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond_var);
    }
}
void *odd(void *arg){
    while(count < MAX){
        pthread_mutex_lock(&mutex);
        
        if(count % 2 == 0){
            pthread_cond_wait(&cond_var, &mutex);
        }
        printf("print odd %d\n", count++);
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond_var);
    }
}
int main(int *argc, char *argv[]){
    pthread_t t1, t2;
    pthread_create(&t1, NULL, even, NULL);
    pthread_create(&t2, NULL, odd, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}