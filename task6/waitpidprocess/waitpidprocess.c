#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
//waitpid를 사용하여 자식의 퇴장 상태를 어떻게 알아내는지 보여준다.
int main(){
    pid_t pid;
    int status, exit_status;

    if((pid = fork()) < 0){
        perror("fork failed");
        exit(1); 
    }
    if(pid == 0){
        sleep(4);
        exit(5);
    }
    /* 부모코드: 자식이 퇴장했는지 확인한다. 퇴장하지 않았으면 1초동안 잠든 후 다시 검사 */
    while(waitpid(pid, &status, WNOHANG) == 0 ){
        printf("still waiting...\n");
        sleep(1);
    }

    if(WIFEXITED(status)){
        exit_status = WEXITSTATUS(status);
        printf("Exit status from %d was %d\n", pid, exit_status);
    }
    exit(0);
}
