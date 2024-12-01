#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MSGSIZE 16

int main()
{
    char buf[MSGSIZE];
    int p[2], i;
    int pid;

    /* 파이프 열기 */
    if (pipe(p) == -1) {
        perror("pipe call failed");
        exit(1);
    }

    pid = fork();

    if (pid == 0) { /* 자식 프로세스 */
        close(p[0]);  // 읽기 끝을 닫음

        /* 파이프에 쓰기 */
        for (i = 0; i < 2; i++) {
            sprintf(buf, "Hello, world #%d", i + 1);
            write(p[1], buf, MSGSIZE);
        }
        close(p[1]);  // 쓰기 끝을 닫음
    }
    else if (pid > 0) { /* 부모 프로세스 */
        close(p[1]);  // 쓰기 끝을 닫음

        /* 파이프에서 읽기 */
        for (i = 0; i < 2; i++) {
            read(p[0], buf, MSGSIZE);
            printf("%s\n", buf);
        }
        close(p[0]);  // 읽기 끝을 닫음
    }
    else {
        perror("fork failed");
    }

    return 0;
}
