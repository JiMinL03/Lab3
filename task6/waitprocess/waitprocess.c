#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    pid_t pid; //프로세스 아이디를 나타냄
    int status, exit_status;
    /*
    status는 자식 프로세스 종료 상태를 저장하는 변수
    exit_status는 자식 프로세스가 종료될 때 반환한 종료 상태를 저장하는 변수
    */

    if((pid = fork()) < 0){ //자식프로세스 생성이 되지 않았을 때
        perror("fork failed");
    }
    
    if(pid == 0){
        sleep(4);
        exit(5);
        /*
        자식 프로세스는 sleep(4)로 4초 동안 실행을 멈추고, 그 후 exit(5)로 종료
        exit(5)는 자식 프로세스가 종료될 때 5라는 종료 상태를 반환하는 역할
        */
    }

    if((pid = wait(&status)) == -1){
        //부모 프로세스는 wait(&status)를 호출하여 자식 프로세스가 종료될 때까지 기다림
        perror("wait failed");
        exit(2);
    }

    if(WIFEXITED(status)){
        exit_status = WEXITSTATUS(status);
        printf("Exit status from %d was %d\n", pid, exit_status);
    }
    /*
    WIFEXITED(status)는 자식 프로세스가 정상적으로 종료되었는지 확인하는 매크로.
    자식 프로세스가 정상 종료되었으면 WEXITSTATUS(status)를 사용하여 종료 상태 값을 얻을 수 있음.
    이 프로그램에서는 자식 프로세스가 exit(5)로 종료되었으므로, 종료 상태는 5.
    부모는 종료 상태를 출력함.
    */

    exit(0);
}