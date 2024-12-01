#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main() {
    // 파일을 열기 (쓰기 모드)
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    // 표준 출력을 "output.txt" 파일로 리디렉션
    if (dup2(fd, 1) == -1) {
        perror("dup2");
        exit(1);
    }

    // 이제 printf의 출력은 화면 대신 "output.txt"로 기록됩니다.
    printf("This will be written to output.txt\n");

    close(fd);  // 파일 디스크립터 닫기
    return 0;
}
