#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void){
    pid_t pid = fork();
    int status;
    wait(&status);

    if(pid == 0){
        printf("The child process.\n");
        exit(0);
    }else{
        printf("The parent process.\n");
    }
    return 0;
}
