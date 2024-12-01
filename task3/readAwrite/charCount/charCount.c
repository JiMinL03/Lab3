#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFSIZE 512

int main(){
    char buffer[BUFSIZE];
    int filedes;
    ssize_t nread; //데이터 크기 또는 읽은 바이트 수를 표현함
    long total = 0;

    if( (filedes = open("anotherfile", O_RDONLY)) == -1){ //anotherfile 이라는 파일의 연다.
        printf("error in opening anotherfile\n");
        exit(1);
    }

    while ((nread = read(filedes, buffer, BUFSIZE))>0){
        //filedes : 파일 오픈으로 부터 얻은 파일 기술자
        //buffer : 자료가 복사되어질 문자 배열의 포인터
        //BUFSIZE : 파일로부터 읽혀질 바이트의 수
        total += nread; //오픈한 파일의 문자 수 세기 프로그램
    }

    printf("total chars in anotherfile: %ld\n", total);
    exit(0);
}