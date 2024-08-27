#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#define QSIZE 10
#define POOLSIZE 4
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_var=PTHREAD_COND_INITIALIZER;
typedef struct{
    void (*func)(void *);
    void *arg;
}Task;
Task queue[QSIZE];
int qsize = 0;

void simplefunc(void *arg){
    printf("executing the worker thread %lu with arg %d\n", pthread_self(), *(int*)arg);
}
void *pthread_pool_worker(void *arg){
    while(1){
        pthread_mutex_lock(&mutex);
        if(qsize == 0){
            pthread_cond_wait(&cond_var, &mutex);
        }
        Task task= queue[--qsize];
        sleep(1);
        pthread_mutex_unlock(&mutex);
        task.func(task.arg);
    }
}
void pthread_init(pthread_t *threads){
    for(int i=0;i<POOLSIZE;i++)
        pthread_create(&threads[i], NULL, pthread_pool_worker, NULL);
}
void add_task_to_worker_thread(void (*func)(void*), void *arg){
    pthread_mutex_lock(&mutex);
    queue[qsize++] = (Task){simplefunc, arg};
    pthread_cond_signal(&cond_var);
    pthread_mutex_unlock(&mutex);
}
int main(int argc, char *argv[]){
    pthread_t threads[POOLSIZE];
    pthread_init(threads);
    for(int i=0;i<QSIZE;i++){
        int *arg = malloc(sizeof(int));
        *arg = i;
        add_task_to_worker_thread(simplefunc, arg);
    }
    for(int i=0;i<POOLSIZE;i++){
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_var);
    return 0;
}
