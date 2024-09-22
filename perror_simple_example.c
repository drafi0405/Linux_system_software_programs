#include <stdio.h>
//#include <errno.h>

int main() {
    FILE *file = fopen("nonexistent_file.txt", "r");
    
    if (file == NULL) {
        printf("Error opening file\n");
        perror("Error opening file");  // Outputs a meaningful error message
    }

    return 0;
}
