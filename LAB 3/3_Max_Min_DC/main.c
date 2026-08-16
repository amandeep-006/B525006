#include <stdio.h>

// Global comparison counters for testing
static int dc_comparisons = 0;
static int linear_comparisons = 0;

// Divide and Conquer function to find Min and Max
void findMinMaxDC(int arr[], int low, int high, int *min, int *max) {
    int min1, max1, min2, max2;

    // Base Case 1: Only 1 element
    if (low == high) {
        *min = arr[low];
        *max = arr[low];
        return;
    }

    // Base Case 2: Exactly 2 elements
    if (high == low + 1) {
        dc_comparisons++;
        if (arr[low] < arr[high]) {
            *min = arr[low];
            *max = arr[high];
        } else {
            *min = arr[high];
            *max = arr[low];
        }
        return;
    }

    // Recursive Case: Divide array into two halves
    int mid = low + (high - low) / 2;

    findMinMaxDC(arr, low, mid, &min1, &max1);
    findMinMaxDC(arr, mid + 1, high, &min2, &max2);

    // Combine step: 2 comparisons
    dc_comparisons++;
    *min = (min1 < min2) ? min1 : min2;

    dc_comparisons++;
    *max = (max1 > max2) ? max1 : max2;
}

// Standard Linear Search approach for comparison
void findMinMaxLinear(int arr[], int n, int *min, int *max) {
    *min = arr[0];
    *max = arr[0];
    linear_comparisons = 0;

    for (int i = 1; i < n; i++) {
        linear_comparisons++;
        if (arr[i] < *min) {
            *min = arr[i];
        }
        linear_comparisons++;
        if (arr[i] > *max) {
            *max = arr[i];
        }
    }
}

void testArray(int arr[], int n) {
    int min_dc, max_dc;
    int min_lin, max_lin;

    dc_comparisons = 0;
    findMinMaxDC(arr, 0, n - 1, &min_dc, &max_dc);
    findMinMaxLinear(arr, n, &min_lin, &max_lin);

    printf("\nArray (Size %d): ", n);
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    printf("Results:\n");
    printf("  D&C Approach    -> Min: %3d | Max: %3d | Comparisons: %2d\n", min_dc, max_dc, dc_comparisons);
    printf("  Linear Approach -> Min: %3d | Max: %3d | Comparisons: %2d\n", min_lin, max_lin, linear_comparisons);
    printf("  Theoretical D&C Bound (3n/2): %.1f | Actual D&C Formula (3n/2 - 2): %d\n", 1.5 * n, (3 * n) / 2 - 2);

    if (dc_comparisons <= (1.5 * n)) {
        printf("  [VALIDATED] D&C comparisons (%d) <= 3n/2 (%.1f)\n", dc_comparisons, 1.5 * n);
    }
}

int main() {
    printf("===============================================================\n");
    printf("   DAA Lab 03 - Question 3: Max & Min using Divide & Conquer   \n");
    printf("===============================================================\n");

    int arr1[] = {22, 13, -5, 88, 90, 4, 76, 31};
    testArray(arr1, 8);

    int arr2[] = {100, 45, 12, 67, 89, 3, 29, 999, -15, 42, 77, 80, 5, 230, 19, 50};
    testArray(arr2, 16);

    printf("\n===============================================================\n");
    printf("                    RECURRENCE & COMPLEXITY                    \n");
    printf("===============================================================\n");
    printf("Recurrence Relation:\n");
    printf("  T(n) = 0                 if n = 1\n");
    printf("  T(n) = 1                 if n = 2\n");
    printf("  T(n) = 2*T(n/2) + 2      if n > 2\n\n");
    printf("Solving by substitution for n = 2^k:\n");
    printf("  T(n) = 2*T(n/2) + 2\n");
    printf("       = 2*(2*T(n/4) + 2) + 2 = 4*T(n/4) + 4 + 2\n");
    printf("       = ... = (n/2)*T(2) + 2*(n/2 - 1)\n");
    printf("       = n/2 * 1 + n - 2 = (3n / 2) - 2\n\n");
    printf("Hence, the total comparisons are bounded by 3n/2.\n");
    printf("===============================================================\n");

    return 0;
}
