#include <fcntl.h>

int filestatus(int filedes){
    int arg1;
    if((arg1 = fcntl(filedes, F_GETFL)) == -1){
        printf("filestatus failed\n");
        return(-1);
    }

    printf("File descriptor %d: ", filedes);

    switch(arg1 & O_ACCMODE){
        case O_WRONLY:
            printf("write-only");
            break;
        case O_RDWR:
            printf("read-write");
            break;
        case O_RDONLY:
            printf("read-only");
            break;
        default:
            printf("No such mode");
    }
    if(arg1 & O_APPEND) printf("- append flag set");
    printf("\n");
    return(0);
}