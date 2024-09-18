#include<stdio.h>
#include<unistd.h>
int main(){
    int pid = fork();
    if(pid == 0){
        printf("child process %d", getpid());
         execl("/bin/ls", "ls", "-l", NULL);
    }
    if(pid > 0){
        //wait(NULL);
        sleep(5);
        printf("parent process %d", getpid());
    }
    return 0;
}