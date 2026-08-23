#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    bool found;
    int a;
    int b;
} PairResult;

int compare_ints(const void *a, const void *b) {
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

/**
 * Dual Sort + Two Pointer O(n log n) Algorithm
 */
PairResult find_pair_two_pointer(int S1[], int S2[], int n, int x) {
    PairResult res = {false, 0, 0};

    // Step 1: Sort both arrays in O(n log n)
    qsort(S1, n, sizeof(int), compare_ints);
    qsort(S2, n, sizeof(int), compare_ints);

    // Step 2: Two pointer scan in O(n)
    int i = 0;        // Start of S1
    int j = n - 1;    // End of S2

    while (i < n && j >= 0) {
        long long current_sum = (long long)S1[i] + (long long)S2[j];
        if (current_sum == x) {
            res.found = true;
            res.a = S1[i];
            res.b = S2[j];
            return res;
        } else if (current_sum < x) {
            i++;
        } else {
            j--;
        }
    }

    return res;
}

void print_array(const char *name, const int arr[], int n) {
    printf("%s = {", name);
    for (int i = 0; i < n; i++) {
        printf("%d%s", arr[i], (i < n - 1) ? ", " : "");
    }
    printf("}\n");
}

int main(void) {
    printf("=========================================================\n");
    printf("  DAA Lab 04 - Question 2: O(n log n) Pair Sum across Sets\n");
    printf("=========================================================\n\n");

    int n;
    printf("Enter size of sets S1 and S2 (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input for n!\n");
        return 1;
    }

    int *S1 = (int *)malloc(n * sizeof(int));
    int *S2 = (int *)malloc(n * sizeof(int));
    if (!S1 || !S2) {
        fprintf(stderr, "Memory allocation error!\n");
        return 1;
    }

    printf("Enter %d integers for Set S1:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &S1[i]);
    }

    printf("Enter %d integers for Set S2:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &S2[i]);
    }

    int target_x;
    printf("Enter target sum (x): ");
    scanf("%d", &target_x);
    printf("\n");

    printf("Input Sets (size n = %d):\n", n);
    print_array("S1", S1, n);
    print_array("S2", S2, n);
    printf("\n");

    printf("Search for target x = %d:\n", target_x);
    PairResult res = find_pair_two_pointer(S1, S2, n, target_x);

    if (res.found) {
        printf("[FOUND] Valid pair: %d (from S1) + %d (from S2) = %d\n", res.a, res.b, target_x);
        printf("[SUCCESS] Verification passed!\n\n");
    } else {
        printf("[NOT FOUND] No pair adds up to %d\n\n", target_x);
    }

    free(S1);
    free(S2);
    return 0;
}
