//Leaky backet algarithm, making sure packet outflow rate is always consistant as 3
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#define OUTRATE 3
#define SIZE 5
void leaky(int *bucketCount){
    if(*bucketCount > 0){
        if(*bucketCount > OUTRATE){
            *bucketCount -= OUTRATE;  
            printf("%d packets egressed and bucket count is %d\n", OUTRATE, *bucketCount);
        }else{
            for(int i=0;i<5;i++){
                if( (*bucketCount-i) <= SIZE && (*bucketCount-i) > 0 )
                    *bucketCount-=i;
            }
        }
    }else{
        printf("bucket is empty\n");
    }
}
void packetArrival(int packetCount, int *bucketCount){
    printf("%d packets arrived ", packetCount);
    if((*bucketCount+packetCount) <= SIZE ){
        *bucketCount += packetCount;
        printf("%d packets added to bucket and bucket count is %d\n",packetCount, *bucketCount);
    }else if(*bucketCount+packetCount > SIZE){
            printf("bucket is overflowing as bucket count is %d celling to packat count as ", packetCount+*bucketCount);
            for(int i=0;i<5;i++){
                if( ((*bucketCount+packetCount)-i) <= SIZE && ((*bucketCount+packetCount)-i) > 0 )
                     *bucketCount = (*bucketCount+packetCount) - i;
            }
            printf("%d\n", *bucketCount);
    }
}
int main(){
    int bucketCount = 0;
    int packetCount;
    for(int i=0;i<5;i++){
        packetCount = rand()%6+1;
        packetArrival(packetCount, &bucketCount);
        
        leaky(&bucketCount);
        sleep(1);
    }
   return 0; 
}