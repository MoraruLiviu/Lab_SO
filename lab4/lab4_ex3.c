#include<unistd.h> 
#include<stdio.h>


int main(int argc, char* argv[] ) {

    for(int i = 1; i <=argc; ++i) {
        pid_t pid = fork(); 
        if(pid== 0){
            int n = atoi(argv[1]);
            printf("%d : %d", n,n);

            while(n != 1) {
                if(n % 2 == 0) 
                    n /= 2;
                else
                    n = 3*n +1;
                printf(" %d", n);
            }
            printf("\nChild %d with Parent %d finished\n", getpid(), getppid());
            return 0;
        }
    }

    for(int i=0; i<argc; ++1) {
        wait(NULL);
    }
    printf("\nChild %d with Parent %d finished\n", getpid(), getppid());
    return 0;
}
