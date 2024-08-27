#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
typedef struct {
    int num;
    char *str;
    int result;
}S;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

void *thread1_fun(void *arg){
    pthread_mutex_lock(&mutex1);
    printf("thread1 locking mutex1\n");
    sleep(1);
    pthread_mutex_lock(&mutex2);
    printf("thread1 locking mutex2\n");
     S *ts = (S*)arg;
     ts->num = 10;
     ts->result = ts->num * ts->num;
     ts->str = "thread1 execution completed";
     printf("thread1 working on critical session\n");
    pthread_mutex_unlock(&mutex2);
    printf("thread1 unlocking mutex2\n");
    pthread_mutex_unlock(&mutex1);
    printf("thread1 unlocking mutex1\n");
    return(ts);
}
void *thread2_fun(void *arg){
    sleep(1);
    pthread_mutex_lock(&mutex1);
    printf("thread2 locking mutex1\n");
    sleep(1);
    pthread_mutex_lock(&mutex2);
    printf("thread2 locking mutex2\n");
    S *ts2 = (S *)arg;
    ts2->result = ts2->num * ts2->num * ts2->num;
    ts2->str = "thread2 execution completed";
     printf("thread2 working on critical session\n");
     
    pthread_mutex_unlock(&mutex2);
    printf("thread2 unlocking mutex2\n");
    pthread_mutex_unlock(&mutex1);
    printf("thread2 unlocking mutex1\n");
    return(ts2);
}   
int main()
{
    pthread_t thread1, thread2;
    S *ts1 = malloc(sizeof(S));
    pthread_create(&thread1, NULL, thread1_fun, ts1);
    pthread_create(&thread2, NULL, thread2_fun, ts1);
    
    pthread_join(thread1, (void **)&ts1);
    printf("%s %d \n\n", ts1->str, ts1->result);
    pthread_join(thread2, (void **)&ts1);
    printf("%s %d \n\n", ts1->str, ts1->result);

    return 0;
}