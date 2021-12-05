#include<unistd.h> 
#include<stdio.h>

int main(int argc, char* argv[] ) {

    int n = atoi(argv[1]);
    pid_t pid = fork(); 
    if(pid) {
        wait(NULL);
        printf("\nChild %d finished\n", pid);
    }
    else {
        printf("%d :", n);
        while(n != 1) {
            if(n % 2 == 0) 
                n/= 2;
            else 
                n = 3*n +1;

        printf(" %d",n);
        }
        
    }

    return 0;
}