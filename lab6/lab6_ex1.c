#include<stdio.h>
#include<errno.h>
#include<pthread.h>
#include<string.h>
#include<stdlib.h>

void* reversingThread (void* input) {

    char* original = (char*) input;
    int length = strlen(original);
    char* reversed = malloc(sizeof(char)*(length +1));

    for(int i =0; i<length; ++i) 
        reversed[i]=original[length - i - 1];

    reversed[length] = '\0';
    return reversed;
}

int main(int argc, char* argv[]) {
    if(argc !=2) {
        printf("This program requires 2 arguments");
        return -1;
    }

    char* input = argv[1];

    pthread_t thread;
    if (pthread_create(&thread, NULL, reversingThread, input)) {
        perror(NULL);
        return errno;
    }

    void* result;
    if (pthread_join(thread, &result)) {
        perror(NULL);
        return errno;
    }

    printf("%s\n", (char*)result);

    return 0;
}