#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef enum {
    COLOR_RED = 0,
    COLOR_BLUE = 1,
    COLOR_YELLOW = 2,
    COLOR_UNKNOWN = -1
} Color;

typedef struct {
    int number;
    Color color;
} Item;

const char* color_to_string(Color c) {
    switch (c) {
        case COLOR_RED: return "Red";
        case COLOR_BLUE: return "Blue";
        case COLOR_YELLOW: return "Yellow";
        default: return "Unknown";
    }
}

Color parse_color(const char *str) {
    if (str[0] == 'R' || str[0] == 'r') return COLOR_RED;
    if (str[0] == 'B' || str[0] == 'b') return COLOR_BLUE;
    if (str[0] == 'Y' || str[0] == 'y') return COLOR_YELLOW;
    return COLOR_UNKNOWN;
}

/**
 * Stable O(n) sort by color: Red -> Blue -> Yellow
 */
void stable_color_sort(const Item input[], int n, Item output[]) {
    int count[3] = {0, 0, 0};

    // Step 1: Count frequency of each color
    for (int i = 0; i < n; i++) {
        count[input[i].color]++;
    }

    // Step 2: Compute starting index for each color bucket
    int pos[3];
    pos[COLOR_RED] = 0;
    pos[COLOR_BLUE] = count[COLOR_RED];
    pos[COLOR_YELLOW] = count[COLOR_RED] + count[COLOR_BLUE];

    // Step 3: Distribute items into output array
    for (int i = 0; i < n; i++) {
        Color c = input[i].color;
        output[pos[c]++] = input[i];
    }
}

bool verify_output(const Item output[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (output[i].color > output[i + 1].color) {
            return false;
        }
        if (output[i].color == output[i + 1].color && output[i].number > output[i + 1].number) {
            return false;
        }
    }
    return true;
}

void print_items(const char* label, const Item arr[], int n) {
    printf("%s (size = %d):\n", label, n);
    for (int i = 0; i < n; i++) {
        printf("  [%2d] (Number: %3d, Color: %-6s)\n", i, arr[i].number, color_to_string(arr[i].color));
    }
    printf("\n");
}

int main(void) {
    printf("=========================================================\n");
    printf("  DAA Lab 04 - Question 1: O(n) Stable Color Sorting\n");
    printf("=========================================================\n\n");

    int n;
    printf("Enter number of items (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input for n!\n");
        return 1;
    }

    Item *input = (Item *)malloc(n * sizeof(Item));
    Item *sorted = (Item *)malloc(n * sizeof(Item));
    if (!input || !sorted) {
        fprintf(stderr, "Memory allocation error!\n");
        return 1;
    }

    printf("Enter %d items as pairs of (number color_char):\n", n);
    printf("(Colors: R for Red, B for Blue, Y for Yellow)\n");
    for (int i = 0; i < n; i++) {
        char color_str[10];
        printf("Item #%d (number color): ", i + 1);
        if (scanf("%d %s", &input[i].number, color_str) != 2) {
            fprintf(stderr, "Invalid item input!\n");
            free(input);
            free(sorted);
            return 1;
        }
        input[i].color = parse_color(color_str);
        if (input[i].color == COLOR_UNKNOWN) {
            fprintf(stderr, "Unknown color '%s'! Use R, B, or Y.\n", color_str);
            free(input);
            free(sorted);
            return 1;
        }
    }
    printf("\n");

    print_items("Input Array (pre-sorted by number)", input, n);

    stable_color_sort(input, n, sorted);

    print_items("Output Array (sorted by color, numbers stable)", sorted, n);

    if (verify_output(sorted, n)) {
        printf("[SUCCESS] Verification Passed: Output is stably sorted by color!\n\n");
    } else {
        printf("[FAILURE] Verification Failed: Output is not properly sorted!\n\n");
    }

    free(input);
    free(sorted);
    return 0;
}
