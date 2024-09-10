#include<stdio.h>
#include<unistd.h>
/* 
2 types: 1) anonymous pipes: create in related process using fork(), uniderectional
2) namded pipes: used in unrelated processes like files in file ssytem*/

int main(){
    int fd[2];
    pipe(fd);
    char buf[11];
    pid_t pid = fork();
    if(pid == 0){
        close(fd[0]);
        write(fd[1],"12345678910",11);
        close(fd[1]);
    } else if(pid > 0){
        close(fd[1]);
        read(fd[0],buf,11);
        close(fd[1]);
    }
    printf("%s",buf);
}