#include <stdio.h>
#include <stdlib.h>

#define MAX 64

// Helper function to add two matrices: C = A + B
void add(int n, int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

// Helper function to subtract two matrices: C = A - B
void subtract(int n, int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

// Recursive Strassen's Matrix Multiplication
void strassen(int n, int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX]) {
    // Base Case: 1x1 matrix
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;
    int A11[MAX][MAX], A12[MAX][MAX], A21[MAX][MAX], A22[MAX][MAX];
    int B11[MAX][MAX], B12[MAX][MAX], B21[MAX][MAX], B22[MAX][MAX];
    int C11[MAX][MAX], C12[MAX][MAX], C21[MAX][MAX], C22[MAX][MAX];
    int P1[MAX][MAX], P2[MAX][MAX], P3[MAX][MAX], P4[MAX][MAX];
    int P5[MAX][MAX], P6[MAX][MAX], P7[MAX][MAX];
    int tempA[MAX][MAX], tempB[MAX][MAX];

    // Divide A and B into 4 sub-matrices of size (n/2) x (n/2)
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }

    // P1 = A11 * (B12 - B22)
    subtract(k, B12, B22, tempB);
    strassen(k, A11, tempB, P1);

    // P2 = (A11 + A12) * B22
    add(k, A11, A12, tempA);
    strassen(k, tempA, B22, P2);

    // P3 = (A21 + A22) * B11
    add(k, A21, A22, tempA);
    strassen(k, tempA, B11, P3);

    // P4 = A22 * (B21 - B11)
    subtract(k, B21, B11, tempB);
    strassen(k, A22, tempB, P4);

    // P5 = (A11 + A22) * (B11 + B22)
    add(k, A11, A22, tempA);
    add(k, B11, B22, tempB);
    strassen(k, tempA, tempB, P5);

    // P6 = (A12 - A22) * (B21 + B22)
    subtract(k, A12, A22, tempA);
    add(k, B21, B22, tempB);
    strassen(k, tempA, tempB, P6);

    // P7 = (A11 - A21) * (B11 + B12)
    subtract(k, A11, A21, tempA);
    add(k, B11, B12, tempB);
    strassen(k, tempA, tempB, P7);

    // C11 = P5 + P4 - P2 + P6
    add(k, P5, P4, tempA);
    subtract(k, tempA, P2, tempB);
    add(k, tempB, P6, C11);

    // C12 = P1 + P2
    add(k, P1, P2, C12);

    // C21 = P3 + P4
    add(k, P3, P4, C21);

    // C22 = P1 + P5 - P3 - P7
    add(k, P1, P5, tempA);
    subtract(k, tempA, P3, tempB);
    subtract(k, tempB, P7, C22);

    // Assemble C from C11, C12, C21, C22
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j]         = C11[i][j];
            C[i][j + k]     = C12[i][j];
            C[i + k][j]     = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }
}

// Standard O(n^3) matrix multiplication for verification
void standardMultiply(int n, int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void printMatrix(int n, int M[MAX][MAX], const char *name) {
    printf("%s (%dx%d):\n", name, n, n);
    for (int i = 0; i < n; i++) {
        printf("  [ ");
        for (int j = 0; j < n; j++) {
            printf("%4d ", M[i][j]);
        }
        printf("]\n");
    }
}

int main() {
    int n = 4;
    int A[MAX][MAX] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 1, 2, 3},
        {4, 5, 6, 7}
    };

    int B[MAX][MAX] = {
        {8, 7, 6, 5},
        {4, 3, 2, 1},
        {1, 2, 3, 4},
        {5, 6, 7, 8}
    };

    int C_strassen[MAX][MAX];
    int C_standard[MAX][MAX];

    printf("===============================================================\n");
    printf("   DAA Lab 03 - Question 4: Strassen's Matrix Multiplication   \n");
    printf("===============================================================\n\n");

    printMatrix(n, A, "Matrix A");
    printf("\n");
    printMatrix(n, B, "Matrix B");
    printf("\n");

    strassen(n, A, B, C_strassen);
    standardMultiply(n, A, B, C_standard);

    printMatrix(n, C_strassen, "Product Matrix C (Strassen's Method)");
    printf("\n");
    printMatrix(n, C_standard, "Product Matrix C (Standard Verification)");

    // Verify correctness
    int match = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (C_strassen[i][j] != C_standard[i][j]) {
                match = 0;
                break;
            }
        }
    }

    printf("\nValidation: %s\n", match ? "PASSED (Strassen result matches standard multiplication!)" : "FAILED");
    printf("Time Complexity: T(n) = 7*T(n/2) + O(n^2) => O(n^(log2 7)) ~= O(n^2.81)\n");
    printf("===============================================================\n");

    return 0;
}
