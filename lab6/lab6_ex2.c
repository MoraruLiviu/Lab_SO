#include<stdio.h>
#include<errno.h>
#include<pthread.h>
#include<stdlib.h>

int A[10][10], B[10][10];
int rowsA, collumnsA, rowsB, collumnsB;
int i,j;
void* multiply(void* arguments) {

    int* args = (int*) arguments;
    int* sum = malloc (sizeof(int));
    *sum = 0;

    for(i = 0; i<rowsB; ++i) {
        *sum += A[args[0]][i] * B[i][args[1]];
    }

    return sum;
}

int main() {

    int Res[10][10];
    FILE *inputFile = fopen("matrice.in","r");

    fscanf(inputFile, "%d%d", &rowsA, &collumnsA);
    for(i = 0; i<rowsA; ++i) {
        for(j = 0; j<collumnsA; ++j) {
            fscanf(inputFile, "%d", &A[i][j]);
        }
    }
    fscanf(inputFile, "%d%d", &rowsB, &collumnsB);
    for(i = 0; i<rowsB; ++i) {
        for(j = 0; j<collumnsB; ++j) {
            fscanf(inputFile, "%d", &B[i][j]);
        }
    }

    if(collumnsA != rowsB) {
        printf("Incompatible matrixes");
        return -1;
    }

    pthread_t threads[rowsA*columnsB];
    int ThreadIndex = 0;

    for(i =0; i<rowsA; ++i) {
        for(j =0; j<columnsB;++j) {
            int * arguments = malloc(sizeof(int)*2);
            arguments[0] = i;
            arguments[1] = j;

            if(pthread_create(&threads[ThreadIndex++], NULL, multiply, arguments)) {
                perror(NULL);
                return errno;
            }
        }
    }

    ThreadIndex = 0;
    for(i =0; i<rowsA; ++i) {
        for(j =0; j<columnsB;++j) {
            
            void* result;
            if(pthread_join(threads[ThreadIndex++], &result)) {
                perror(NULL);
                return errno;
            }

            Res[i][j] = *((int*)result);
        }
    }

    for(i=0; i<rowsA; ++i) {
        for(j = 0; j<columnsB; ++j) {
            printf("%d", Res[i][j]);
        }
        printf("\n");
    }
    fclose(inputFile);
    return 0;
}