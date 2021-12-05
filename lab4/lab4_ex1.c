#include<unistd.h> 
#include<stdio.h>

int main() {

    pid_t pid = fork();

    if(pid) {
        printf("Parent PID: %d  Child PID: %d\n", getpid(), pid);
        wait(NULL); 
        printf("Child %d finished\n", pid);
    }
    else {
        char *argv[] = {"ls","-l", NULL}; 
        execve("/bin/Ls", argv, NULL);
    }
    return 0;
}