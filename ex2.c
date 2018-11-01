#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(void) 

{
    
    char * word = "Hello";

    if (setvbuf(stdout, NULL, _IOLBF, 0)) {
        perror("Error: Setbuf");
        exit(EXIT_FAILURE);
    }
    
    for (int x = 0; x < strlen(word); ++x) {
        printf("%c", word[x]);
        sleep(1);
    }
    
    printf("\n");
    return 0;
}
