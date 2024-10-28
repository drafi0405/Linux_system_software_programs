#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
pthread_rwlock_t rwlock;
int sharedata=0;
void *reader(void *arg){
    int threadnum = *((int*)arg);
    while(1){
        pthread_rwlock_rdlock(&rwlock);
        printf("reader %d reading the data %d\n",threadnum, sharedata);
        pthread_rwlock_unlock(&rwlock);
        sleep(2);
    }
}
void *writer(void *arg){
    int threadnum = *((int*)arg);
    while(1){
        pthread_rwlock_wrlock(&rwlock);
        sharedata++;
        printf("writer %d writing the data %d\n",threadnum, sharedata);
        pthread_rwlock_unlock(&rwlock);
        sleep(4);
    }
}
int main(){
    int readernum[]={1,2,3};
    int writernum[]={1,2};
    pthread_t rt[3];
    pthread_t wt[2];
    pthread_rwlock_init(&rwlock, NULL);
    for(int i=0;i<3;i++)
        pthread_create(&rt[i],NULL,reader, &readernum[i]);
    for(int i=0;i<2;i++)
        pthread_create(&wt[i],NULL,writer, &writernum[i]);
    for(int i=0;i<3;i++)
        pthread_join(rt[i], NULL);
    for(int i=0;i<2;i++)
        pthread_join(wt[i], NULL);
    pthread_rwlock_destroy(&rwlock);
    return 0;
}