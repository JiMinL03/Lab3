#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h> 

#define MAX_READ 10

int main(int argc, char *argv[]) {
    int fd;
    int size = 0;
    ssize_t pointer;
    char buf[MAX_READ];

    if (argc < 2) {
        fprintf(stderr, "Usage: file_size filename\n");
        exit(1); 
    }

    // 파일 열기
    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        perror("Error opening file");
        exit(1);  
    }

    while ((pointer = read(fd, buf, MAX_READ)) > 0) {
        size += pointer;  
    }

    if (pointer == -1) {
        perror("Error reading file");
        close(fd);
        exit(1);
    }

    printf("File size: %d bytes\n", size);

    close(fd); 
    return 0;
}
