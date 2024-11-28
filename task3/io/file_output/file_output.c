#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
//dup2 사용 *********!!!!!
int main(int argc, char *argv[]){
    int fd;
    char *buf = "This is a test output file.\n";
    int flags = O_WRONLY | O_CREAT | O_TRUNC;
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

    if(argc < 2){
        fprintf(stderr, "Usage: file_output filename\n");
        exit(1);
    }

    if((fd = open(argv[1], flags, mode)) ==-1){
        perror("open");
        exit(1);
    }
    
    if(dup2(fd,1) == -1){
        perror("dup2");
        exit(1);
    }

    if(close(fd) == -1){
        perror("close");
        exit(1);
    }
    //while(1,buf,strlen(buf));
    // 파일에 버퍼 내용을 쓰는 부분
    if(write(1, buf, strlen(buf)) == -1){
        perror("write");
        exit(1);
    }

    exit(0);
}