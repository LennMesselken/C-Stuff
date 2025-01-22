#include <stdio.h>
#include <stdlib.h>

void multiply_matrices(int** A, int** B, int** C, int m, int n, int p){
    for (int i = 0; i < m; i++){
        for (int j = 0; j < p; j++){
            C[i][j] = 0;
            for (int k = 0; k < n; k++){
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
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
    //Make Memory Space for Matrix
    int m = 2, n = 3, p = 2;
    int** A = (int**) malloc(m * sizeof(int *));
    int** B = (int**) malloc(n * sizeof(int *));
    int** C = (int**) malloc(m * sizeof(int *));

    for (int i = 0; i < m; i++){
        A[i] = (int*) malloc(n * sizeof(int));
        C[i] = (int*) malloc(p * sizeof(int));
    }

    for (int i = 0; i < n; i++){
        B[i] = (int*) malloc(p * sizeof(int));
    }

    //Assign Matrix
    A[0][0] = 1; A[0][1] = 2; A[0][2] = 3;
    A[1][0] = 4; A[1][1] = 5; A[1][2] = 6;
    
    B[0][0] = 7; B[0][1] = 8;
    B[1][0] = 9; B[1][1] = 10;
    B[2][0] = 11; B[2][1] = 12;

    multiply_matrices(A, B, C, m, n, p);
    print_matrix(C, m, p);

    // Free memory
    for (int i = 0; i < m; i++) free(A[i]);
    for (int i = 0; i < n; i++) free(B[i]);
    for (int i = 0; i < m; i++) free(C[i]);
    free(A);
    free(B);
    free(C);
}