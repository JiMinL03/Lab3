#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

const char *endstring = ".";

int main(int argc, char *argv[]){
    int fd;
    off_t hole_size; //파일 내에서 이동할 위치, 0은 파일의 처음
    off_t size;

    if(argc < 3){
        printf("stderr, Usage: file_hole filename size\n");
        exit(1);
    }

    if((fd = open(argv[1], O_RDWR)) == -1){
        perror("open");
        exit(1);
    }

    hole_size = atoi(argv[2]);
    size = lseek(fd, 0, SEEK_END);
    printf("Before : %s's size = %ld\n", argv[1], size);

    lseek(fd, hole_size, SEEK_SET); //지정한 위치에 endstring을 쓴다. (문자 덮어씌움)
    write(fd, endstring, 1);

    size = lseek(fd, 0, SEEK_END);
    printf("After : %s's size = %ld\n", argv[1], size);

    close(fd);
}
