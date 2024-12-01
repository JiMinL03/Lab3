#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define THIS_PROCESS 1
#define THAT_PROCESS 2

int main()
{
    int fd;
    struct flock testlock;
    char buf[20];

    testlock.l_type = F_WRLCK;
    testlock.l_whence = SEEK_SET;
    testlock.l_start = 0;
    testlock.l_len = 0;

    /* open file */
    fd = open("testlock", O_RDWR | O_CREAT, 0666);
    if (fd == -1) {
        perror("open failed");
        exit(1);
    }

    /* 파일에 잠금 설정 */
    if (fcntl(fd, F_SETLKW, &testlock) == -1) {
        fprintf(stderr, "process %d: lock failed\n", THIS_PROCESS);
        exit(1);
    }

    printf("process %d: locked successfully\n", THIS_PROCESS);

    /* 데이터를 파일에 쓰기 */
    sprintf(buf, "Hello, process %d", THAT_PROCESS);
    write(fd, buf, 17);
    printf("process %d: wrote \"%s\" to testlock\n", THIS_PROCESS, buf);

    /* 5초간 대기 */
    sleep(5);

    printf("process %d: unlocking\n", THIS_PROCESS);

    /* 잠금 해제 */
    testlock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &testlock);

    close(fd);

    return 0;
}
