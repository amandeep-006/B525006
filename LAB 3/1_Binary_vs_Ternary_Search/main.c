#include <stdio.h>

// Function for Binary Search
// Returns index if found, -1 if not found. Updates comparison count.
int binarySearch(int arr[], int n, int key, int *comparisons) {
    int low = 0, high = n - 1;
    *comparisons = 0;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        (*comparisons)++;
        if (arr[mid] == key) {
            return mid;
        }

        (*comparisons)++;
        if (key < arr[mid]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return -1;
}

// Function for Ternary Search
// Returns index if found, -1 if not found. Updates comparison count.
int ternarySearch(int arr[], int n, int key, int *comparisons) {
    int low = 0, high = n - 1;
    *comparisons = 0;

    while (low <= high) {
        int mid1 = low + (high - low) / 3;
        int mid2 = high - (high - low) / 3;

        (*comparisons)++;
        if (arr[mid1] == key) {
            return mid1;
        }

        (*comparisons)++;
        if (arr[mid2] == key) {
            return mid2;
        }

        (*comparisons)++;
        if (key < arr[mid1]) {
            high = mid1 - 1;
        } else {
            (*comparisons)++;
            if (key > arr[mid2]) {
                low = mid2 + 1;
            } else {
                low = mid1 + 1;
                high = mid2 - 1;
            }
        }
    }
    return -1;
}

void testSearch(int arr[], int n, int key, const char *scenario) {
    int bin_comps = 0, ter_comps = 0;
    int bin_idx = binarySearch(arr, n, key, &bin_comps);
    int ter_idx = ternarySearch(arr, n, key, &ter_comps);

    printf("\n--- Test Scenario: %s (Key = %d) ---\n", scenario, key);
    printf("Binary  Search -> Found at index: %2d | Comparisons: %2d\n", bin_idx, bin_comps);
    printf("Ternary Search -> Found at index: %2d | Comparisons: %2d\n", ter_idx, ter_comps);
    if (bin_comps <= ter_comps) {
        printf("Result: Binary Search took fewer or equal comparisons (%d vs %d).\n", bin_comps, ter_comps);
    } else {
        printf("Result: Ternary Search took %d comparisons vs Binary %d.\n", ter_comps, bin_comps);
    }
}

int main() {
    int n = 15;
    int arr[] = {2, 5, 8, 12, 16, 23, 38, 45, 56, 67, 78, 89, 91, 95, 99};

    printf("===============================================================\n");
    printf("     DAA Lab 03 - Question 1: Binary vs Ternary Search        \n");
    printf("===============================================================\n");
    printf("Array elements (%d items): ", n);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Test cases:
    testSearch(arr, n, 2, "Element at Beginning");
    testSearch(arr, n, 45, "Element near Middle");
    testSearch(arr, n, 99, "Element at End");
    testSearch(arr, n, 50, "Element Not Present (Worst Case)");

    printf("\n===============================================================\n");
    printf("                    THEORETICAL JUSTIFICATION                  \n");
    printf("===============================================================\n");
    printf("1. Binary Search divides the search space into 2 parts:\n");
    printf("   - Height of decision tree = log2(n)\n");
    printf("   - Comparisons per level   <= 2\n");
    printf("   - Worst case comparisons  = 2 * log2(n) ~= 2.00 * log2(n)\n\n");
    printf("2. Ternary Search divides the search space into 3 parts:\n");
    printf("   - Height of decision tree = log3(n) = (log2(n) / log2(3))\n");
    printf("   - Comparisons per level   <= 4\n");
    printf("   - Worst case comparisons  = 4 * log3(n) = (4 / 1.585) * log2(n) ~= 2.52 * log2(n)\n\n");
    printf("Conclusion: Since 2.00 * log2(n) < 2.52 * log2(n), Binary Search\n");
    printf("is asymptotically and practically more efficient than Ternary Search.\n");
    printf("===============================================================\n");

    return 0;
}
