//Probe algarithm
#include <stdio.h>
#include <stdbool.h>
#define N 3
typedef struct{
    int id;
    int waitingFor;
}Process;
bool is_deadlock(Process processes[]){
    for(int i=0;i<3;i++){
        int origin = i;
        int target = processes[i].waitingFor;
        while(origin++ < N && target != -1){
            if(i == target){
                printf("Deadlock is detected\n");
                printf("processing the processes ");
                for(int j=0;j<N;j++){
                    printf("%d ", processes[j].id);
                }
                return true;
            }
            target = processes[target].waitingFor;
        }
    }
    return false;
}
int main(){
    Process processes[] = {
        {0,1},
        {1,2},
        {2,3}
    };
    if(!is_deadlock(processes)){
        printf("No dead lock\n");
    }
    return 0;
}