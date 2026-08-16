#include <stdio.h>
#include <stdlib.h>

#define MAX 64

// Helper function to add two matrices
void addMatrix(int n, int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

// Helper function to subtract two matrices
void subMatrix(int n, int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

// Recursive O(n^2) multiplication for special-pattern matrices
void specialMatrixMultiply(int n, int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX]) {
    // Base Case: 1x1 matrix
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;
    int A1[MAX][MAX], A2[MAX][MAX];
    int B1[MAX][MAX], B2[MAX][MAX];

    // Extract blocks A1, A2 from A and B1, B2 from B
    // Note: A11 = A22 = A1, A12 = A21 = A2
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A1[i][j] = A[i][j];         // Top-left (M1)
            A2[i][j] = A[i][j + k];     // Top-right (M2)
            B1[i][j] = B[i][j];         // Top-left (M1)
            B2[i][j] = B[i][j + k];     // Top-right (M2)
        }
    }

    int SA[MAX][MAX], DA[MAX][MAX];
    int SB[MAX][MAX], DB[MAX][MAX];

    // Compute SA = A1 + A2, DA = A1 - A2
    // Compute SB = B1 + B2, DB = B1 - B2
    addMatrix(k, A1, A2, SA);
    subMatrix(k, A1, A2, DA);
    addMatrix(k, B1, B2, SB);
    subMatrix(k, B1, B2, DB);

    // Only TWO recursive calls needed!
    // P = (A1 + A2) * (B1 + B2) = C1 + C2
    // Q = (A1 - A2) * (B1 - B2) = C1 - C2
    int P[MAX][MAX], Q[MAX][MAX];
    specialMatrixMultiply(k, SA, SB, P);
    specialMatrixMultiply(k, DA, DB, Q);

    // Compute C1 = (P + Q) / 2 and C2 = (P - Q) / 2
    int C1[MAX][MAX], C2[MAX][MAX];
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C1[i][j] = (P[i][j] + Q[i][j]) / 2;
            C2[i][j] = (P[i][j] - Q[i][j]) / 2;
        }
    }

    // Assemble the full C matrix: [C1 C2; C2 C1]
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j]         = C1[i][j]; // Top-left
            C[i][j + k]     = C2[i][j]; // Top-right
            C[i + k][j]     = C2[i][j]; // Bottom-left
            C[i + k][j + k] = C1[i][j]; // Bottom-right
        }
    }
}

// Standard O(n^3) matrix multiplication to verify correctness
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

    // Construct 4x4 recursive special symmetric block matrices
    // Structure: M = [M1 M2; M2 M1] where each block also has [m1 m2; m2 m1]
    int A[MAX][MAX] = {
        {4, 1, 2, 3},
        {1, 4, 3, 2},
        {2, 3, 4, 1},
        {3, 2, 1, 4}
    };

    int B[MAX][MAX] = {
        {5, 2, 1, 4},
        {2, 5, 4, 1},
        {1, 4, 5, 2},
        {4, 1, 2, 5}
    };

    int C_special[MAX][MAX];
    int C_standard[MAX][MAX];

    printf("=================================================================\n");
    printf(" DAA Lab 03 - Question 5: Special-Pattern Matrix Mult [O(n^2)]   \n");
    printf("=================================================================\n\n");

    printMatrix(n, A, "Matrix A (Special Block Structure)");
    printf("\n");
    printMatrix(n, B, "Matrix B (Special Block Structure)");
    printf("\n");

    specialMatrixMultiply(n, A, B, C_special);
    standardMultiply(n, A, B, C_standard);

    printMatrix(n, C_special, "Product C (O(n^2) D&C Algorithm)");
    printf("\n");
    printMatrix(n, C_standard, "Product C (Standard Verification)");

    int match = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (C_special[i][j] != C_standard[i][j]) {
                match = 0;
                break;
            }
        }
    }

    printf("\nValidation: %s\n", match ? "PASSED (Results match identically!)" : "FAILED");
    printf("Time Complexity: T(n) = 2*T(n/2) + O(n^2) => O(n^2) by Master Theorem.\n");
    printf("=================================================================\n");

    return 0;
}
