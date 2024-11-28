/*
주어진 디렉토리 내에 존재하는 파일과 디렉토리를 나열하고, 
디렉토리의 경우 재귀적으로 방문해서 그 디렉토리 내에 존재하는 파일과 디렉토리를 나열하는 프로그램을 작성하시오. 
즉, “ls –R” 명령과 동일한 결과를 보이도록 하시오.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

void list_directory(const char *dir_name) {
    DIR *pdir;
    struct dirent *pde;
    char path[1024];
    struct stat statbuf;

    pdir = opendir(dir_name);
    if (pdir == NULL) {
        perror("opendir");
        return;
    }

    printf("%s:\n", dir_name);

    while ((pde = readdir(pdir)) != NULL) {
        strcpy(path, dir_name);
        if (path[strlen(path) - 1] != '/') {
            strcat(path, "/");
        }
        strcat(path, pde->d_name);

        if (stat(path, &statbuf) == 0) {
            printf("%s\n", pde->d_name);

            if (S_ISDIR(statbuf.st_mode)) {
                if (strcmp(pde->d_name, ".") != 0 && strcmp(pde->d_name, "..") != 0) {
                    list_directory(path);
                }
            }
        } else {
            perror("stat");
        }
    }

    closedir(pdir);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s dirname\n", argv[0]);
        exit(1);
    }

    list_directory(argv[1]);
    return 0;
}
