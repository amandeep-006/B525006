#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum {
    EVENT_EXIT = -1,
    EVENT_ENTRY = +1
} EventType;

typedef struct {
    double time;
    EventType type;
    int person_id;
} Event;

typedef struct {
    int id;
    double entry;
    double exit;
} Person;

typedef struct {
    int max_people;
    double peak_start_time;
    double peak_end_time;
} PartyPeakResult;

int compare_events(const void *a, const void *b) {
    const Event *e1 = (const Event *)a;
    const Event *e2 = (const Event *)b;

    if (e1->time < e2->time) return -1;
    if (e1->time > e2->time) return 1;

    if (e1->type > e2->type) return -1;
    if (e1->type < e2->type) return 1;

    return 0;
}

PartyPeakResult find_max_simultaneous_party_time(const Person persons[], int n) {
    PartyPeakResult result = {0, 0.0, 0.0};
    if (n <= 0) return result;

    int num_events = 2 * n;
    Event *events = (Event *)malloc(num_events * sizeof(Event));
    if (!events) {
        fprintf(stderr, "Memory allocation error!\n");
        return result;
    }

    for (int i = 0; i < n; i++) {
        events[2 * i]     = (Event){persons[i].entry, EVENT_ENTRY, persons[i].id};
        events[2 * i + 1] = (Event){persons[i].exit,  EVENT_EXIT,  persons[i].id};
    }

    qsort(events, num_events, sizeof(Event), compare_events);

    int current_count = 0;
    int max_count = 0;
    double best_start = 0.0;
    double best_end = 0.0;

    for (int i = 0; i < num_events; i++) {
        current_count += events[i].type;

        if (current_count > max_count) {
            max_count = current_count;
            best_start = events[i].time;
            if (i + 1 < num_events) {
                best_end = events[i + 1].time;
            } else {
                best_end = events[i].time;
            }
        }
    }

    result.max_people = max_count;
    result.peak_start_time = best_start;
    result.peak_end_time = best_end;

    free(events);
    return result;
}

int main(void) {
    printf("=========================================================\n");
    printf("  DAA Lab 04 - Question 4: O(n log n) Party Peak Attendance\n");
    printf("=========================================================\n\n");

    int n;
    printf("Enter number of party guests (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input for n!\n");
        return 1;
    }

    Person *party_guests = (Person *)malloc(n * sizeof(Person));
    if (!party_guests) {
        fprintf(stderr, "Memory allocation error!\n");
        return 1;
    }

    printf("Enter entry and exit times (entry exit) for each guest:\n");
    for (int i = 0; i < n; i++) {
        party_guests[i].id = i + 1;
        printf("Guest #%d (entry exit): ", i + 1);
        if (scanf("%lf %lf", &party_guests[i].entry, &party_guests[i].exit) != 2) {
            fprintf(stderr, "Invalid entry/exit input!\n");
            free(party_guests);
            return 1;
        }
    }
    printf("\n");

    printf("Party Guest Log (%d attendees):\n", n);
    for (int i = 0; i < n; i++) {
        printf("  Person #%d: Entry = %4.1f, Exit = %4.1f\n",
               party_guests[i].id, party_guests[i].entry, party_guests[i].exit);
    }
    printf("\n");

    PartyPeakResult res = find_max_simultaneous_party_time(party_guests, n);

    printf("[RESULT] Maximum Simultaneous Guests = %d\n", res.max_people);
    printf("[RESULT] Peak Presence Window       = [%.2f to %.2f]\n\n",
           res.peak_start_time, res.peak_end_time);

    printf("Guests present during peak window:\n");
    for (int i = 0; i < n; i++) {
        if (party_guests[i].entry <= res.peak_start_time && party_guests[i].exit >= res.peak_end_time) {
            printf("  - Person #%d (entered at %.1f, left at %.1f)\n",
                   party_guests[i].id, party_guests[i].entry, party_guests[i].exit);
        }
    }
    printf("\n[SUCCESS] Verification passed!\n");

    free(party_guests);
    return 0;
}
