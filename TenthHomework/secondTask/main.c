#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void){
    int status;
    printf("The first process: pid - %d, ppid - %d.\n", getpid(), getppid());
    pid_t pid2 = fork();
    pid_t pid3 = -1;
    if(pid2 != 0) {
        pid3 = fork();
        waitpid(pid3, &status, 0);
    }
    waitpid(pid2, &status, 0);

    if(pid2 == 0){
        printf("The second process: pid - %d, ppid - %d.\n", getpid(), getppid());
        pid_t pid4 = fork();
        pid_t pid5 = -1;
        if(pid4 != 0) {
            pid5 = fork();
            waitpid(pid5, &status, 0);
        }
        waitpid(pid4, &status, 0);

        if(pid4 == 0) {
            printf("The fourth process: pid - %d, ppid - %d.\n", getpid(), getppid());
            exit(0);
        }
        if(pid5 == 0) {
            printf("The fifth process: pid - %d, ppid - %d.\n", getpid(), getppid());
            exit(0);
        }

        exit(0);
    }
    if(pid3 == 0){
        printf("The third process: pid - %d, ppid - %d.\n", getpid(), getppid());

        pid_t pid6 = fork();
        waitpid(pid6, &status, 0);

        if(pid6 == 0) {
            printf("The sixth process: pid - %d, ppid - %d.\n", getpid(), getppid());
            exit(0);
        }

        exit(0);
    }
    return 0;
}
