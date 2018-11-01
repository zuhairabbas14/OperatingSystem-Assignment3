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
  
    char *path1 = "./ex1.txt";
    char *path2 = "./ex1.memcpy.txt";
    int myFile = open(path1, O_RDWR);
    
    if (myFile < 0) {
        perror("Error: Can't open");
        exit(EXIT_FAILURE);
    }

    struct stat fileStat = {};
    if (fstat(path1, &fileStat)) {
        perror("Error: Fstat");
        exit(EXIT_FAILURE);
    };

    int second_path = open(path2, O_RDWR);

    if (second_path < 0) {
        perror("Error: Can't open");
        exit(EXIT_FAILURE);
    }

    void *mapping1 = mmap(NULL, fileStat.st_size, PROT_WRITE | PROT_READ, MAP_SHARED, path1, 0);
    void *mapping2 = mmap(NULL, fileStat.st_size, PROT_WRITE | PROT_READ, MAP_SHARED, second_path, 0);

    if (ftruncate(second_path, fileStat.st_size)) {
        perror("Error: Truncate");
        exit(EXIT_FAILURE);
    }

    memcpy(mapping2, mapping1, fileStat.st_size);

}
