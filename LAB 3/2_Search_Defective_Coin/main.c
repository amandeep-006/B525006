#include <stdio.h>
#include <stdbool.h>

static int weighing_count = 0;

// Simulates a balance weighing scale between two sets of coins
// Returns: -1 if left pan is lighter, 1 if right pan is lighter, 0 if equal
int balanceScale(double coins[], int l1, int r1, int l2, int r2) {
    weighing_count++;
    double left_sum = 0.0, right_sum = 0.0;

    for (int i = l1; i <= r1; i++) left_sum += coins[i];
    for (int i = l2; i <= r2; i++) right_sum += coins[i];

    if (left_sum < right_sum) return -1;
    if (left_sum > right_sum) return 1;
    return 0;
}

// Divide & Conquer function to find defective coin
// Returns the index of the defective coin, or -1 if all coins are genuine
int findDefectiveCoin(double coins[], int low, int high, int known_genuine) {
    int count = high - low + 1;

    // Base Case 1: Single coin left
    if (count == 1) {
        if (known_genuine != -1) {
            // Compare with known genuine coin to verify if it is lighter
            int res = balanceScale(coins, low, low, known_genuine, known_genuine);
            if (res == -1) return low; // defective
            return -1;                 // genuine
        }
        return -1; // cannot be defective without reference if total n=1 and equal
    }

    // Base Case 2: Exactly 2 coins
    if (count == 2) {
        int res = balanceScale(coins, low, low, high, high);
        if (res == -1) return low;
        if (res == 1) return high;

        // If equal, neither is lighter than the other.
        // Check against known genuine coin if available
        if (known_genuine != -1) {
            int chk = balanceScale(coins, low, low, known_genuine, known_genuine);
            if (chk == -1) return low;
        }
        return -1; // All genuine
    }

    // General Divide & Conquer step:
    int half = count / 2; // Size of each pan
    int l1 = low, r1 = low + half - 1;
    int l2 = low + half, r2 = low + 2 * half - 1;

    int scale_result = balanceScale(coins, l1, r1, l2, r2);

    if (scale_result == -1) {
        // Left pan is lighter -> defective coin is in left pan
        // All coins in right pan are genuine; use l2 as known genuine
        return findDefectiveCoin(coins, l1, r1, l2);
    } else if (scale_result == 1) {
        // Right pan is lighter -> defective coin is in right pan
        // All coins in left pan are genuine; use l1 as known genuine
        return findDefectiveCoin(coins, l2, r2, l1);
    } else {
        // Both pans balance! All coins in [low ... low + 2*half - 1] are genuine.
        // If count was even, then ALL coins in [low...high] are genuine.
        if (count % 2 == 0) {
            return -1;
        }

        // If count was odd, only 1 coin remains unweighed at index 'high'.
        // Compare it directly against a known genuine coin (e.g. index low).
        int res = balanceScale(coins, high, high, low, low);
        if (res == -1) {
            return high; // The odd coin is defective
        }
        return -1; // All coins are genuine
    }
}

void runTestCase(int n, int defective_index, double standard_wt, double defective_wt) {
    double coins[100];
    for (int i = 0; i < n; i++) {
        coins[i] = standard_wt;
    }
    if (defective_index >= 0 && defective_index < n) {
        coins[defective_index] = defective_wt;
    }

    weighing_count = 0;
    int found_index = findDefectiveCoin(coins, 0, n - 1, -1);

    printf("\n---------------------------------------------------------------\n");
    printf("Total Coins: %d | Actual Defective Coin Index: %d\n", n, defective_index);
    if (found_index != -1) {
        printf("Result: Defective (lighter) coin FOUND at index %d (Weight: %.1f)\n", found_index, coins[found_index]);
    } else {
        printf("Result: NO defective coin found. All coins are perfectly weighted (%.1f).\n", standard_wt);
    }
    printf("Scale weighings used: %d (Theoretical Bound: <= log2(%d) + 2)\n", weighing_count, n);
}

int main() {
    double standard_weight = 10.0;
    double lighter_weight = 9.2;

    printf("===============================================================\n");
    printf("     DAA Lab 03 - Question 2: Search the Defective Coin       \n");
    printf("===============================================================\n");

    // Case 1: Defective coin in odd number of coins
    runTestCase(9, 6, standard_weight, lighter_weight);

    // Case 2: Defective coin in even number of coins
    runTestCase(16, 3, standard_weight, lighter_weight);

    // Case 3: Defective coin is the odd remaining coin
    runTestCase(11, 10, standard_weight, lighter_weight);

    // Case 4: No defective coin present (worker made perfect coins)
    runTestCase(12, -1, standard_weight, lighter_weight);

    printf("\n===============================================================\n");
    printf("Complexity Analysis:\n");
    printf("- At each recursive step, array size is halved (n -> n/2).\n");
    printf("- Number of pan weighings per step = 1.\n");
    printf("- Base case / confirmation weighing <= 1.\n");
    printf("- Total weighings <= ceil(log2 n) + 1 = O(log2 n).\n");
    printf("===============================================================\n");

    return 0;
}
