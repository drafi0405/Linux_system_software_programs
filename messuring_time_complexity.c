#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main() {
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    sleep(2);
    // Code block to measure
    
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", cpu_time_used);

    return 0;
}
