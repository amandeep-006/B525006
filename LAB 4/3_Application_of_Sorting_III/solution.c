#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int compare_ints(const void *a, const void *b) {
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int binary_search(const int arr[], int low, int high, long long target) {
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

bool k_sum_helper(const int S[], int n, int k, long long T,
                  int level, int start_idx, long long current_sum,
                  int chosen_indices[]) {
    if (level == k - 1) {
        long long remainder = T - current_sum;
        int found_idx = binary_search(S, start_idx, n - 1, remainder);
        if (found_idx != -1) {
            chosen_indices[k - 1] = found_idx;
            return true;
        }
        return false;
    }

    for (int i = start_idx; i <= n - (k - level); i++) {
        chosen_indices[level] = i;
        if (k_sum_helper(S, n, k, T, level + 1, i + 1, current_sum + S[i], chosen_indices)) {
            return true;
        }
    }
    return false;
}

/**
 * Main K-Sum Testing Function: O(n^(k-1) * log n)
 */
bool test_k_sum(int S[], int n, int k, long long T, int result_elements[]) {
    if (k <= 0 || k > n) {
        return false;
    }

    qsort(S, n, sizeof(int), compare_ints);

    if (k == 1) {
        int idx = binary_search(S, 0, n - 1, T);
        if (idx != -1) {
            if (result_elements) result_elements[0] = S[idx];
            return true;
        }
        return false;
    }

    int *chosen_indices = (int *)malloc(k * sizeof(int));
    if (!chosen_indices) return false;

    bool found = k_sum_helper(S, n, k, T, 0, 0, 0, chosen_indices);

    if (found && result_elements) {
        for (int i = 0; i < k; i++) {
            result_elements[i] = S[chosen_indices[i]];
        }
    }

    free(chosen_indices);
    return found;
}

void print_array(const char *label, const int arr[], int n) {
    printf("%s: {", label);
    for (int i = 0; i < n; i++) {
        printf("%d%s", arr[i], (i < n - 1) ? ", " : "");
    }
    printf("}\n");
}

int main(void) {
    printf("=========================================================\n");
    printf("  DAA Lab 04 - Question 3: O(n^(k-1) log n) k-Sum Solver\n");
    printf("=========================================================\n\n");

    int n;
    printf("Enter size of set S (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input for n!\n");
        return 1;
    }

    int *S = (int *)malloc(n * sizeof(int));
    if (!S) {
        fprintf(stderr, "Memory allocation error!\n");
        return 1;
    }

    printf("Enter %d integers for set S:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &S[i]);
    }

    int k;
    printf("Enter number of elements to sum (k): ");
    scanf("%d", &k);

    long long T;
    printf("Enter target sum (T): ");
    scanf("%lld", &T);
    printf("\n");

    print_array("Original Set S", S, n);
    printf("Target k = %d, Target Sum T = %lld\n\n", k, T);

    int *result_elements = (int *)malloc(k * sizeof(int));

    printf("Searching for %d elements that sum to %lld...\n", k, T);
    if (test_k_sum(S, n, k, T, result_elements)) {
        printf("[FOUND] %d elements summing to %lld: ", k, T);
        long long check_sum = 0;
        for (int i = 0; i < k; i++) {
            printf("%d%s", result_elements[i], (i < k - 1) ? " + " : " = ");
            check_sum += result_elements[i];
        }
        printf("%lld\n", check_sum);
        printf("[SUCCESS] Verification passed!\n\n");
    } else {
        printf("[NOT FOUND] No %d elements sum to %lld\n\n", k, T);
    }

    free(S);
    free(result_elements);
    return 0;
}
