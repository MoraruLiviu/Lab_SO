#include<unistd.h> 
#include<sys/types.h> 
#include<fcntl.h> 
#include<sys/stat.h> 
#include<stdio.h> 
#include<errno.h> 
#include<sys/mman.h> 
#include<sys/wait.h> 
#include<stdlib.h>

int main(int argc, char* argv[]) {

    if (argc == 1) {
        printf("Nu au fost date numere.\n");
        perror(NULL); 
        return errno;
    }

    size_t PAGE_SIZE = getpagesize();

    size_t shm_size = (argc - 1) * PAGE_SIZE;
    char shm_name[] = "collatz_shm";

    int shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

    if (shm_fd < 0) { 
        perror(NULL); 
        return errno;
    }

    if(ftruncate(shm_fd, shm_size) == -1) {
        perror(NULL);
        shm_unlink(shm_name);
        return errno;
    }

    int* buffer = (int*) mmap(0, shm_size, PROT_READ| PROT_WRITE, MAP_SHARED, shm_fd, 0);
    int i;
    for(i=1; i<argc; ++i) {
        pid_t PID = fork();

        if(PID < 0) {
            printf("Fork number %d failed\n", i);
        }
        if (PID==0){
            int* sir = buffer + ( (i-1) * PAGE_SIZE / sizeof(int));

            if(sir == MAP_FAILED) {
                return -1;
            }

            int number = atoi(argv[i]);
            int size = 0;

            while (number !=1) {
                ++size;
                sir[size]=number;

                if( number%2 == 0 )
                    number/=2;
                else
                    number=number*3+1;
            
            }
        
            ++size;
            sir[size] =1;
            sir[0] = size;
            
            printf("Child %d done with parent %d \n", getpid(), getppid());
            return 0;
        }
    }

    for(i=1; i<argc; ++1) {
        wait(NULL);
    }

    for (i=1; i<argc; ++i){
        int* sir = buffer + (i-1) * PAGE_SIZE / sizeof(int);
        int size = sir[0];
        printf("%d: ", sir[1]);
        for(int j = 2; i<=size); ++j){
            printf("%d ", sir[j]);
        }
        printf("\n");
    }

    printf ("Parent %d done with parent %d\n", getpid());
    munmap(buffer, shm_size);
    close(shm_fd);
    shm_unlink(shm_name);
    return 0;
}