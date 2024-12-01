#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

#define MAX_READ 2

int main(int argc, char *argv[]) {
    int src_fd;
    int dst_fd;
    char buf[MAX_READ];
    ssize_t rcnt;
    ssize_t tot_cnt = 0;
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

    if (argc < 3) {
        fprintf(stderr, "Usage: file_copy src_file dest_file\n");
        exit(1);
    }

    if ((src_fd = open(argv[1], O_RDONLY)) == -1) {
        perror("src open");
        exit(1);
    }

    if ((dst_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, mode)) == -1) {
        perror("dst open");
        exit(1);
    }

    while ((rcnt = read(src_fd, buf, MAX_READ)) > 0) { 
        //파일을 읽음 1바이트씩 읽어서 쓴다. (while문이기 떄문에 전체 파일이 복사되는 것이다.)
        //read로부터 0이 반환되면 파일의 끝을 의미함. 따라서 0이 될 때까지 반복문을 돌려 전체 파일을 복사함.
        ssize_t wc = write(dst_fd, buf, rcnt); //dst_fd에 rcnt를 입력함
        if (wc == -1) {
            perror("write");
            exit(1);
        }
        tot_cnt += wc;
    }

    if (rcnt < 0) {
        perror("read");
        exit(1);
    }

    printf("total write count = %ld\n", tot_cnt);

    close(src_fd);
    close(dst_fd);

    return 0;
}
