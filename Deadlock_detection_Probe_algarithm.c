/*Types of Deadlock detection algarithms
   1)  WFG - Wait for Graph P1-->P2-->P1, if cycle find Deadlock exists otherwise no
   2)  Bankers Algarithms, works on safe-state and unsafe state, allocate all required resouce instances to the multiple processes, simulate Allocation resouce algarithm, process them if all processes end with same state no deadlock exists
   3)  Resource allocation graph  like WFG
   4)  Probe Algarithm, P1(waiting for resource R2) sends a probe message to P2 to get resource R2 (which is lockaed currently by it), P2 forwards it to P3(which is holding S3) to get S3, if Same message comes back to P1, lock exists
   5)  Resource allocation matric method
//simple c Probe algarithm method*/
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
