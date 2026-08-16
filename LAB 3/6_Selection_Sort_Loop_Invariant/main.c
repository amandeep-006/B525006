#include <stdio.h>
#define MAX_SIZE 100

// Function to print array contents
void printArray(int arr[], int n) {
    printf("[ ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("]\n");
}

// Selection Sort function demonstrating Loop Invariants
int selectionSort(int arr[], int n) {
    int comparisons = 0;

    printf("\n===============================================================\n");
    printf("        STEP-BY-STEP EXECUTION & LOOP INVARIANT TRACE          \n");
    printf("===============================================================\n");

    for (int i = 0; i < n - 1; i++) {
        printf("\n--- Pass %d (i = %d) ---\n", i + 1, i);
        
        // Display current sorted and unsorted parts
        printf("  [Invariant Check]\n");
        printf("    Sorted subarray   A[0..%d] : [ ", i - 1);
        for (int k = 0; k < i; k++) printf("%d ", arr[k]);
        printf("]\n");

        printf("    Unsorted subarray A[%d..%d] : [ ", i, n - 1);
        for (int k = i; k < n; k++) printf("%d ", arr[k]);
        printf("]\n");

        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            comparisons++;
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }

        printf("    Smallest element in unsorted part: %d (at index %d)\n", arr[min_idx], min_idx);

        // Swap minimum element with element at index i
        if (min_idx != i) {
            int temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
            printf("    Action: Swapped A[%d] (%d) with A[%d] (%d)\n", i, arr[min_idx], min_idx, arr[i]);
        } else {
            printf("    Action: Element %d is already at correct index %d (No swap needed)\n", arr[i], i);
        }

        printf("    Array state after Pass %d: ", i + 1);
        printArray(arr, n);
    }

    return comparisons;
}

int main() {
    int arr[MAX_SIZE];
    int n;

    printf("===============================================================\n");
    printf("   DAA Lab 03 - Question 6: Selection Sort & Loop Invariants   \n");
    printf("===============================================================\n\n");

    // Taking user input
    printf("Enter number of elements (n): ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_SIZE) {
        printf("Invalid input size. Please enter a value between 1 and %d.\n", MAX_SIZE);
        return 1;
    }

    printf("Enter %d integers separated by spaces:\n", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            printf("Invalid element input.\n");
            return 1;
        }
    }

    printf("\nOriginal Array: ");
    printArray(arr, n);

    // Perform sorting
    int total_comparisons = selectionSort(arr, n);

    // Display sorted result
    printf("\n===============================================================\n");
    printf("Sorted Array  : ");
    printArray(arr, n);

    // Complexity Validation
    int theoretical_comparisons = n * (n - 1) / 2;
    printf("\nComparisons Made        : %d\n", total_comparisons);
    printf("Theoretical [n(n-1)/2]  : %d\n", theoretical_comparisons);

    if (total_comparisons == theoretical_comparisons) {
        printf("Validation Result       : PASSED (Exact match with Theta(n^2))\n");
    }

    printf("\n===============================================================\n");
    printf("                       THEORETICAL SUMMARY                     \n");
    printf("===============================================================\n");
    printf("1. Loop Invariant:\n");
    printf("   At the start of iteration i, subarray A[0..i-1] contains the\n");
    printf("   i smallest elements in sorted order, with all elements in\n");
    printf("   A[0..i-1] <= all elements in A[i..n-1].\n\n");
    printf("2. Why only (n - 1) elements?\n");
    printf("   After placing the first (n-1) smallest elements, the last\n");
    printf("   element A[n-1] is guaranteed to be the maximum and is already\n");
    printf("   in its correct position. An n-th pass would be redundant.\n\n");
    printf("3. Time Complexity in Theta-notation:\n");
    printf("   - Total comparisons = sum_{i=0}^{n-2} (n - 1 - i) = n(n-1)/2.\n");
    printf("   - Worst-case running time = Theta(n^2).\n");
    printf("   - Best-case running time  = Theta(n^2) (not any better, as the\n");
    printf("     inner loop scans all remaining elements regardless of order).\n");
    printf("===============================================================\n");

    return 0;
}
