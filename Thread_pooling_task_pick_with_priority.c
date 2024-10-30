#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#define POOLSIZE 5
#define QSIZE 10
pthread_mutex_t mutex;
pthread_cond_t cond_var;
typedef struct t{
    void (*func)(void *, int );
    int *arg;
    int priority;
}Task;
Task queue[QSIZE];
int qindex=0;
void simplefunc(void *arg, int priority){
    printf("executing worker thread %lu with arg %d having priority %d\n", pthread_self(), *(int *)arg, priority);
}
void add_task_to_Q(void (*func)(void *arg, int), int *arg, int priority){
        pthread_mutex_lock(&mutex);
        if(qindex < QSIZE){
            queue[qindex++]=(Task){func,arg,priority};
            pthread_cond_signal(&cond_var);
        }else if(qindex > QSIZE){
            printf("Queue is full\n");
        }
        pthread_mutex_unlock(&mutex);
}
void *worker_function(void *arg){
    while(1){
        pthread_mutex_lock(&mutex);
        if(qindex == 0){
            pthread_cond_wait(&cond_var, &mutex);
        }
        Task task = queue[--qindex];
        pthread_mutex_unlock(&mutex);
        task.func(task.arg,task.priority);
    }
}
void init_threads(pthread_t p[]){
    for(int i=0;i<POOLSIZE;i++){
        pthread_create(&p[i],NULL,worker_function,NULL);
    }
}
int main(){
    pthread_t t[POOLSIZE];
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_var, NULL);
    init_threads(t);
    for(int i=0;i<QSIZE;i++){
        int *arg = malloc(sizeof(int));
        *arg = i;
        int priority = rand()%10;
        add_task_to_Q(simplefunc, arg, priority);
    }
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_var);
    return 0;
}

