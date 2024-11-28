#include <stdlib.h>
int main(){
    int exit_status;

    printf("enter exit status: ");
    scanf("%d", &exit_status);
    exit(exit_status);
    //echo $? 명령으로 종료 상태 확인
}