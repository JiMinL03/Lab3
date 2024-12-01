#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
//텍스트 파일 내용 복사 프로그램
int main(int argc, char *argv[]){
    FILE *src;
    FILE *dst;
    char ch;
    int count = 0;

    if(argc < 3){
        printf("Usage: file_copy source_file destination_filn\n");
        exit(1);
    }

    if((src = fopen(argv[1], "r"))==NULL){
        perror("fopen:src");
        exit(1);
    }

    if((dst = fopen(argv[2], "w"))==NULL){
        perror("fopen:dst");
        exit(1);
    }

    while(!feof(src)){ //feof는 파일의 끝을 확인하는 함수
        ch = (char) fgetc(src); //파일 src에서 한 문자를 읽어옴
        if(ch != EOF){ //만약 ch가 파일의 끝이 아니라면
            fputc((int)ch, dst); //ch에 저장된 문자를 dst 파일에 쓴다.
        }
        count++;
    }

    fclose(src);
    fclose(dst);
}