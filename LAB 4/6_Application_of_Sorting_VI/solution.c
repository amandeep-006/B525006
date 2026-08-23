#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    double left;
    double right;
    int id;
} Interval;

typedef enum {
    ENDPOINT_RIGHT = -1,
    ENDPOINT_LEFT  = +1
} EndpointType;

typedef struct {
    double coord;
    EndpointType type;
    int interval_id;
} Endpoint;

typedef struct {
    double point;
    int max_overlap_count;
} OverlapResult;

int compare_endpoints(const void *a, const void *b) {
    const Endpoint *e1 = (const Endpoint *)a;
    const Endpoint *e2 = (const Endpoint *)b;

    if (e1->coord < e2->coord) return -1;
    if (e1->coord > e2->coord) return 1;

    if (e1->type > e2->type) return -1;
    if (e1->type < e2->type) return 1;

    return 0;
}

OverlapResult find_max_overlapping_point(const Interval intervals[], int n) {
    OverlapResult res = {0.0, 0};
    if (n <= 0) return res;

    int num_endpoints = 2 * n;
    Endpoint *endpoints = (Endpoint *)malloc(num_endpoints * sizeof(Endpoint));
    if (!endpoints) {
        fprintf(stderr, "Memory allocation error!\n");
        return res;
    }

    for (int i = 0; i < n; i++) {
        endpoints[2 * i]     = (Endpoint){intervals[i].left,  ENDPOINT_LEFT,  intervals[i].id};
        endpoints[2 * i + 1] = (Endpoint){intervals[i].right, ENDPOINT_RIGHT, intervals[i].id};
    }

    qsort(endpoints, num_endpoints, sizeof(Endpoint), compare_endpoints);

    int current_overlap = 0;
    int max_overlap = 0;
    double best_point = intervals[0].left;

    for (int i = 0; i < num_endpoints; i++) {
        current_overlap += endpoints[i].type;
        if (current_overlap > max_overlap) {
            max_overlap = current_overlap;
            best_point = endpoints[i].coord;
        }
    }

    res.point = best_point;
    res.max_overlap_count = max_overlap;

    free(endpoints);
    return res;
}

int main(void) {
    printf("=========================================================\n");
    printf("  DAA Lab 04 - Question 6: O(n log n) Max Overlap Point\n");
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

    printf("Enter %d closed intervals as (left right) pairs:\n", n);
    for (int i = 0; i < n; i++) {
        sample[i].id = i + 1;
        printf("Interval #%d (left right): ", i + 1);
        if (scanf("%lf %lf", &sample[i].left, &sample[i].right) != 2) {
            fprintf(stderr, "Invalid interval input!\n");
            free(sample);
            return 1;
        }
    }
    printf("\n");

    printf("Input Intervals S (%d intervals):\n", n);
    for (int i = 0; i < n; i++) {
        printf("  Interval #%d: [%.1f, %.1f]\n", sample[i].id, sample[i].left, sample[i].right);
    }
    printf("\n");

    OverlapResult res = find_max_overlapping_point(sample, n);

    printf("[RESULT] Maximum Overlap Count = %d\n", res.max_overlap_count);
    printf("[RESULT] Point p with Max Overlap = %.1f\n\n", res.point);

    printf("Intervals containing point p = %.1f:\n", res.point);
    int verified_count = 0;
    for (int i = 0; i < n; i++) {
        if (sample[i].left <= res.point && res.point <= sample[i].right) {
            printf("  - Interval #%d: [%.1f, %.1f]\n", sample[i].id, sample[i].left, sample[i].right);
            verified_count++;
        }
    }

    if (verified_count == res.max_overlap_count) {
        printf("\n[SUCCESS] Maximum overlap point verified successfully!\n");
    } else {
        printf("\n[FAILURE] Verification failed!\n");
    }

    free(sample);
    return 0;
}
