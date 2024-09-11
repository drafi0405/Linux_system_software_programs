#include<stdio.h>
#include<stdlib.h>
#include<sys/mman.h>
int main(){
    FILE *fp;
    fp=fopen("simple.txt","r");
    int fd = fileno(fp);
    char *data=(char *)mmap(0,11,PROT_READ,MAP_PRIVATE,fd,0);
    //arguments: starting address mapping usually system to choose, 
    //number of bytes to mapping
    //memory protection PROT_READ, PROT_WRITE
    //behaviour flagsMAP_SHARED
    //filedescriptor
    //offset int he file
    printf("%s\n",data);
    fclose(fp);
    return 0;
}