#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int start;
    int end;
} Interval;

int max_val(int a, int b) {
    return (a > b) ? a : b;
}

int compare_intervals(const void *a, const void *b) {
    const Interval *i1 = (const Interval *)a;
    const Interval *i2 = (const Interval *)b;

    if (i1->start < i2->start) return -1;
    if (i1->start > i2->start) return 1;

    if (i1->end < i2->end) return -1;
    if (i1->end > i2->end) return 1;

    return 0;
}

Interval* merge_intervals(Interval input[], int n, int *out_count) {
    if (n <= 0) {
        *out_count = 0;
        return NULL;
    }

    qsort(input, n, sizeof(Interval), compare_intervals);

    Interval *output = (Interval *)malloc(n * sizeof(Interval));
    if (!output) {
        *out_count = 0;
        return NULL;
    }

    int count = 0;
    int cur_start = input[0].start;
    int cur_end = input[0].end;

    for (int i = 1; i < n; i++) {
        if (input[i].start <= cur_end) {
            cur_end = max_val(cur_end, input[i].end);
        } else {
            output[count++] = (Interval){cur_start, cur_end};
            cur_start = input[i].start;
            cur_end = input[i].end;
        }
    }

    output[count++] = (Interval){cur_start, cur_end};
    *out_count = count;

    return output;
}

void print_intervals(const char *label, const Interval arr[], int n) {
    printf("%s: {", label);
    for (int i = 0; i < n; i++) {
        printf("(%d, %d)%s", arr[i].start, arr[i].end, (i < n - 1) ? ", " : "");
    }
    printf("}\n");
}

int main(void) {
    printf("=========================================================\n");
    printf("  DAA Lab 04 - Question 5: O(n log n) Interval Merging\n");
    printf("=========================================================\n\n");

    int n;
    printf("Enter number of intervals (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input for n!\n");
        return 1;
    }

    Interval *sample = (Interval *)malloc(n * sizeof(Interval));
    if (!sample) {
        fprintf(stderr, "Memory allocation error!\n");
        return 1;
    }

    printf("Enter %d intervals as (start end) pairs:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Interval #%d (x y): ", i + 1);
        if (scanf("%d %d", &sample[i].start, &sample[i].end) != 2) {
            fprintf(stderr, "Invalid interval input!\n");
            free(sample);
            return 1;
        }
    }
    printf("\n");

    print_intervals("Original Intervals I", sample, n);

    int merged_count = 0;
    Interval *merged = merge_intervals(sample, n, &merged_count);

    print_intervals("Merged Intervals Output", merged, merged_count);
    printf("\n[SUCCESS] Intervals merged successfully into %d disjoint intervals!\n", merged_count);

    free(sample);
    free(merged);
    return 0;
}
