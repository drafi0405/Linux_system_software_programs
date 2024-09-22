#include<stdio.h>
#include<stdlib.h>
int main(){
    FILE *file;
    int wbuffer[]={100,200,300,400,500};
    int buffer[5];
    file = fopen("data.txt", "w");
    if(NULL == file){
        perror("file open/create failed\n");
        exit(1);
    }
    int writecount=0;
    while(writecount < 5){
        printf("%d ",fprintf(file, "%d\n", wbuffer[writecount]));
        writecount++;
    }
    fclose(file);
    file = fopen("data.txt", "r");
    int readcount=0;
    while(readcount < 5 && fscanf(file, "%d", &buffer[readcount]) == 1){
        readcount++;
    }
    for(int i=0;i<5;i++)
        printf("buffer[%d] = %d\n", i, buffer[i]);
    fclose(file);
    return 0;
}