#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int getargs(char *cmd, char **argv);

int main() {
    char buf[256];
    char *argv[50];
    int narg;
    pid_t pid;

    while (1) {
        printf("shell> ");
        fflush(stdout);  // 출력 버퍼를 비우기

        // 사용자 입력 받기 (gets 대신 fgets 사용)
        if (fgets(buf, sizeof(buf), stdin) == NULL) {
            break;  // EOF나 입력 오류 발생 시 종료
        }
        buf[strcspn(buf, "\n")] = '\0';  // 개행 문자 제거

        narg = getargs(buf, argv);  // 입력된 명령어와 인자를 분리

        // 자식 프로세스를 생성하고 명령어 실행
        pid = fork();
        if (pid == 0) {
            // 자식 프로세스에서 명령어 실행
            execvp(argv[0], argv);
            perror("execvp failed");  // execvp 실패 시 출력
            exit(1);  // 자식 프로세스 종료
        } else if (pid > 0) {
            // 부모 프로세스는 자식 프로세스의 종료를 기다림
            wait(NULL);
        } else {
            perror("fork failed");
        }
    }

    return 0;
}

int getargs(char *cmd, char **argv) {
    int narg = 0;

    // 입력된 명령어에서 공백을 기준으로 인자 분리
    while (*cmd) {
        if (*cmd == ' ' || *cmd == '\t') {
            *cmd++ = '\0';  // 공백 문자 만나면 문자열 종료
        } else {
            argv[narg++] = cmd++;
            while (*cmd != '\0' && *cmd != ' ' && *cmd != '\t') {
                cmd++;  // 공백, 탭을 만날 때까지 계속 진행
            }
        }
    }

    argv[narg] = NULL;  // execvp에서 종료를 인식할 수 있도록 NULL 추가
    return narg;
}
