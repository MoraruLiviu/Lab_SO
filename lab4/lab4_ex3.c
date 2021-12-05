#include<unistd.h> 
#include<stdio.h>


int main(int argc, char* argv[] ) {
    char s[32];
    int n;
    int i;
    for(i = 1; i <=argc; ++i) {
        pid_t pid = fork(); 
        if(pid== 0){
            strcpy(s,argv[i]);
            n=0;
            for(i=0;i<strlen(s); ++i) {
                n=n*10+s[i] - '0';
            }
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

    for(i=0; i<argc; ++i) {
        wait(NULL);
    }
    printf("\nChild %d with Parent %d finished\n", getpid(), getppid());
    return 0;
}
