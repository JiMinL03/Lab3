#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h> //오류처리

int main(int argc, char *argv[]){
    int fd;
    char *buf = "This is a test.\n";
    ssize_t cnt;
    int flags = O_WRONLY|O_CREAT|O_APPEND;
    mode_t mode = S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH;

    if(argc<2){
        printf("stderr, Usage: file_append filename\n");
        exit(2);
    }

    if((fd = open(argv[1], flags, mode))== -1){ //파일 열기 실패
        perror("open");
        exit(1);
    }

    //파일 여는 데 성공했다면 ..
    cnt = write(fd, buf, strlen(buf));
    //fd : 파일 기술자
    //buf : 자료가 복사되어질 문자 배열의 포인터
    printf("write count = %d\n", cnt);
    

    close(fd);
}