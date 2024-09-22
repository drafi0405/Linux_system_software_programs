#include<stdio.h>
#include<stdlib.h>
int main(){
    FILE *fp;
    fp = fopen("simple.txt", "w");
    if(fp == NULL){
        printf("file open failed\n");
    }
    fprintf(fp, "helloworld!");
    fclose(fp);
    fp = fopen("simple.txt", "r");
    if(fp == NULL)
        exit(1);
    char input[20];
    fscanf(fp, "%s", input);
    printf("%s",input);
    return 0;
}