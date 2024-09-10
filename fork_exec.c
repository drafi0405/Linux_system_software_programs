#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>

int main(){
    pid_t pid;
    pid = fork();
    if(pid ==0){
        printf("child process id is %d\n",getpid());
        execlp("ls","ls","-l",NULL);
        exit(1);
    }
    if(pid>0){
        printf("parent process id is %d, awaiting for child process to finish\n",getpid());
        wait(NULL);
        printf("child process finished\n");
    }
}