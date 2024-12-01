#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define MSGSIZE 128
#define KEY 12345

struct msgbuf {
    long mtype;
    char mtext[MSGSIZE];
};

int main() {
    int msgid;
    pid_t pid;
    struct msgbuf message;

    if ((msgid = msgget(KEY, 0666 | IPC_CREAT)) == -1) {
        perror("msgget failed");
        exit(1);
    }

    pid = fork();

    if (pid == 0) {
        while (1) {
            if (msgrcv(msgid, &message, sizeof(message.mtext), 0, 0) == -1) {
                perror("msgrcv failed");
                exit(1);
            }
            if (strcmp(message.mtext, "exit") == 0) break;
            printf("Received: %s\n", message.mtext);
        }
    } else if (pid > 0) {
        while (1) {
            printf("Enter message (or 'exit' to quit): ");
            fgets(message.mtext, MSGSIZE, stdin);
            message.mtext[strcspn(message.mtext, "\n")] = 0;
            message.mtype = 1;
            if (msgsnd(msgid, &message, sizeof(message.mtext), 0) == -1) {
                perror("msgsnd failed");
                exit(1);
            }
            if (strcmp(message.mtext, "exit") == 0) break;
        }
    } else {
        perror("fork failed");
        exit(1);
    }

    if (pid > 0) {
        wait(NULL);
        msgctl(msgid, IPC_RMID, NULL);
    }

    return 0;
}
