#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4

typedef struct {
    int** A;
    int** B;
    int** C;
    int m;
    int n;
    int p;
    int start_row;
    int end_row;
} ThreadData ;

void* multiply_matrix (void *arg){
    ThreadData* data = (ThreadData*) arg;
    for (int i = data->start_row; i < data->end_row; i++){
        for(int j = 0; j < data->p;j++){
            data->C[i][j] = 0;
            for(int k = 0; k < data->n; k++){
                data->C[i][j] += data->A[i][k] * data->B[k][j];
            }
        }
    }
    return NULL;
}

void print_matrix(int **matrix, int m, int n){
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main(){

    //Memory Allocation
    int m = 4, n = 3, p = 2;
    int **A = (int **)malloc(m * sizeof(int *));
    int **B = (int **)malloc(n * sizeof(int *));
    int **C = (int **)malloc(m * sizeof(int *));
    
    for (int i = 0; i < m; i++) {
        A[i] = (int *)malloc(n * sizeof(int));
        C[i] = (int *)malloc(p * sizeof(int));
    }
    
    for (int i = 0; i < n; i++) {
        B[i] = (int *)malloc(p * sizeof(int));
    }
    
    // Initialize matrices A and B
    A[0][0] = 1; A[0][1] = 2; A[0][2] = 3;
    A[1][0] = 4; A[1][1] = 5; A[1][2] = 6;
    A[2][0] = 7; A[2][1] = 8; A[2][2] = 9;
    A[3][0] = 10; A[3][1] = 11; A[3][2] = 12;
    
    B[0][0] = 1; B[0][1] = 2;
    B[1][0] = 3; B[1][1] = 4;
    B[2][0] = 5; B[2][1] = 6;

    //Create array of threads
    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];

    //Divide the work among the threads
    int rows_per_thread = m / NUM_THREADS;
    for(int i = 0; i < NUM_THREADS; i++){
        thread_data[i].A = A;
        thread_data[i].B = B;
        thread_data[i].C= C;
        thread_data[i].m = m;
        thread_data[i].n = n;
        thread_data[i].p = p;
        thread_data[i].start_row = i * rows_per_thread;
        thread_data[i].end_row = (i == NUM_THREADS -1) ? m : (i+1) * rows_per_thread;

        pthread_create(&threads[i], NULL, multiply_matrix, &thread_data[i]);
    }

    //Join Threads
    for (int i = 0; i < NUM_THREADS; i++){
        pthread_join(threads[i], NULL);
    }

    //Print the result
    print_matrix(C, m, p);

    // //Free Memory
    for (int i = 0; i < m; i++) free(A[i]);
    for (int i = 0; i < n; i++) free(B[i]);
    for (int i = 0; i < m; i++) free(C[i]);
    free(A);
    free(B);
    free(C);

    return 0;

}