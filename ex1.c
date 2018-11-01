#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>


int main(void) 

{
    char *print_str = "This is a nice day";
    char *path = "./ex1.txt";
    int myFile = open(path, O_RDWR);
    size_t strSize = strlen(print_str);
    
    
    if (myFile < 0) {
        perror("Error: Can't open");
        exit(EXIT_FAILURE);
    }

    if (ftruncate(myFile, strSize)) {
        perror("Error: Truncate");
        exit(EXIT_FAILURE);
    }

    void *mapping = mmap(NULL, strSize, PROT_READ | PROT_WRITE, MAP_SHARED, myFile, 0);
    
    if (mapping == MAP_FAILED) {
        perror("Error: Mapping");
        exit(EXIT_FAILURE);
    }
    
    memcpy(mapping, print_str, strSize);

}
