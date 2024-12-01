#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char *argv[]){ //creat 안 쓰고 open 파일이 없을 때 빈 파일 생성하는 기능 쓴듯.
    int fd;
    char *buf;
    ssize_t cnt;
    int flags = O_WRONLY|O_CREAT|O_TRUNC;
    mode_t mode = S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH;

    if(argc<2){
        fprintf(stderr, "Usage: file_creat filename\n");
        exit(1);
    }

    if((fd = open(argv[1], flags, mode))==-1){ // S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH
        perror("open"); 
        exit(1);
    }

    cnt = write(fd, buf, strlen(buf));
    printf("write count = %d\n", cnt);
    close(fd);
}