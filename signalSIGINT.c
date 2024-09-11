#include <stdio.h>
#include <signal.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
void signal_handler(int sig){
    printf("signal caught %d\n", sig);
    printf("stopping print\n");
    exit(1);
}
int main()
{
    signal(SIGINT, signal_handler);
    while(1){
        for(int i=0;i<INT_MAX;i++){
            printf("%d",i);
            sleep(0.1);
        }
    }
    return 0;
}