#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 1024

int main(void) {
    char *sentence = "Hello, World! This is a typing practice.";
    char input[BUFSIZE];
    int error_count = 0;
    int total_chars = 0;

    printf("다음 문장을 입력하세요:\n");
    printf("%s\n", sentence);

    printf("입력: ");
    fgets(input, BUFSIZE, stdin);

    // 입력에서 개행 문자 제거
    input[strcspn(input, "\n")] = '\0';

    for (int i = 0; sentence[i] != '\0' && input[i] != '\0'; i++) {
        if (sentence[i] != input[i]) {
            error_count++;
            printf("오류! '%c'를 입력하셔야 합니다.\n", sentence[i]);
        }
        total_chars++;
    }

    // 만약 입력이 주어진 문장보다 짧으면, 나머지 문자 오류
    if (strlen(input) < strlen(sentence)) {
        error_count += strlen(sentence) - strlen(input);
    }

    printf("\n타이핑 연습 종료!\n");
    printf("잘못 입력한 횟수: %d\n", error_count);
    printf("전체 문자 수: %d\n", total_chars);

    return 0;
}
