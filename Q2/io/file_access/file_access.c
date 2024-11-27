#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>  // exit 함수 사용을 위한 헤더 추가
#include <string.h>  // strerror 함수 사용을 위한 헤더 추가

int main(int argc, char *argv[]){
    int ret_val;
    int mode_array[4] = {R_OK, W_OK, X_OK, F_OK};
    const char *mode_str[4] = {"existent", "readable", "writable", "executable"};
    const char *mode_err[4] = {"Existence check", "Readability check", "Writability check", "Executability check"};
    int i;

    if(argc < 2){
        fprintf(stderr, "Usage: file_access filename\n");
        exit(1);
    }

    printf("File \"%s\":", argv[1]);

    for(i = 0; i < 4; i++){
        errno = 0;  // errno 초기화
        ret_val = access(argv[1], mode_array[i]);
        if(ret_val == 0){
            printf("%s ", mode_str[i]);  // 출력에 공백 추가
        }else if(ret_val == -1){
            fprintf(stderr, "%s: %s\n", mode_err[i], strerror(errno));  // 오류 메시지 수정
        }
    }
    printf("\n");
}
