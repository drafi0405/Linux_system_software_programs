/* Token bucket Algarithm to handle 10 request*/
#include<stdio.h>
#include<time.h>
#include<unistd.h>
typedef struct{
    int tokens;
    int capacity;
    double fillrate;
    double last_time;
}bucket;
double getCurrentTime(){
    return (double)time(NULL);
}
void initializeBucket(bucket *tbucket){
    double currentTime = getCurrentTime();
    double timeCollapse = currentTime - tbucket->last_time;
    tbucket->tokens += timeCollapse * tbucket->fillrate;
    if(tbucket->tokens > tbucket->capacity){
        tbucket->tokens = tbucket->capacity;
    }
    tbucket->last_time = getCurrentTime();
}
int handleReq(bucket *tbucket){
    initializeBucket(tbucket);
    if(tbucket->tokens >= 1){
        tbucket->tokens -= 1;
        printf("req processing token count %d\n", tbucket->tokens);
        return 1;
    }else{
        printf("No tokens to the request\n");
        return 0;
    }
}
int main(int argc, char *argv[]){
    bucket tbucket;
    tbucket.tokens = 5;
    tbucket.capacity = 5;
    tbucket.fillrate = 1.0; //per second
    tbucket.last_time = getCurrentTime();
    for(int i=0;i<10;i++){
        handleReq(&tbucket);
        sleep(1);
    }
    return 0;
}