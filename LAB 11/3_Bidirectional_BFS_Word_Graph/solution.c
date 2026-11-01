#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define HASH_SIZE 65537

typedef struct HashNode { char word[16]; int id; struct HashNode *next; } HashNode;
HashNode* ht[HASH_SIZE];

unsigned int get_hash(const char *s) {
    unsigned int h = 5381; while (*s) h = ((h << 5) + h) + (unsigned char)(*s++);
    return h % HASH_SIZE;
}
void insert_word(const char *s, int id) {
    unsigned int h = get_hash(s);
    HashNode *node = (HashNode *)malloc(sizeof(HashNode));
    strcpy(node->word, s); node->id = id; node->next = ht[h]; ht[h] = node;
}
int find_word(const char *s) {
    for (HashNode *c = ht[get_hash(s)]; c; c = c->next) {
        if (strcmp(c->word, s) == 0) return c->id;
    }
    return -1;
}

int main(void) {
    int N, L;
    printf("Enter word length (L) and number of dictionary words (N): ");
    if (scanf("%d %d", &L, &N) != 2 || L <= 0 || L > 12 || N <= 0) return 1;
    char start_word[16], end_word[16];
    printf("Enter starting word (A) and target word (B): ");
    if (scanf("%s %s", start_word, end_word) != 2) return 1;
    char (*dict)[16] = malloc((N + 5) * sizeof(*dict));
    printf("Enter %d dictionary words:\n", N);
    int total_words = 0;
    for (int i = 0; i < N; i++) {
        printf("  Word %d: ", i + 1);
        if (scanf("%s", dict[total_words]) != 1) return 1;
        if (find_word(dict[total_words]) == -1) {
            insert_word(dict[total_words], total_words); total_words++;
        }
    }
    int end_id = find_word(end_word);
    if (end_id == -1) {
        printf("\nTarget word '%s' not in dictionary. Impossible (Mutations = -1).\n", end_word);
        free(dict); return 0;
    }
    int start_id = find_word(start_word);
    if (start_id == -1) {
        strcpy(dict[total_words], start_word);
        insert_word(start_word, total_words); start_id = total_words++;
    }
    int *dist_fwd = (int *)malloc(total_words * sizeof(int));
    int *dist_bwd = (int *)malloc(total_words * sizeof(int));
    int *parent_fwd = (int *)malloc(total_words * sizeof(int));
    int *parent_bwd = (int *)malloc(total_words * sizeof(int));
    for (int i = 0; i < total_words; i++) dist_fwd[i] = dist_bwd[i] = parent_fwd[i] = parent_bwd[i] = -1;
    int *q_fwd = (int *)malloc(total_words * sizeof(int)), *q_bwd = (int *)malloc(total_words * sizeof(int));
    int h_fwd = 0, t_fwd = 0, h_bwd = 0, t_bwd = 0, meet = -1;
    dist_fwd[start_id] = 0; q_fwd[t_fwd++] = start_id;
    dist_bwd[end_id] = 0; q_bwd[t_bwd++] = end_id;
    while (h_fwd < t_fwd && h_bwd < t_bwd) {
        bool expand_fwd = (t_fwd - h_fwd) <= (t_bwd - h_bwd);
        int u = expand_fwd ? q_fwd[h_fwd++] : q_bwd[h_bwd++];
        char temp[16]; strcpy(temp, dict[u]);
        for (int p = 0; p < L && meet == -1; p++) {
            char orig = temp[p];
            for (char c = 'a'; c <= 'z' && meet == -1; c++) {
                if (c == orig) continue;
                temp[p] = c; int v = find_word(temp);
                if (v == -1) continue;
                if (expand_fwd) {
                    if (dist_bwd[v] != -1) { dist_fwd[v] = dist_fwd[u] + 1; parent_fwd[v] = u; meet = v; }
                    else if (dist_fwd[v] == -1) { dist_fwd[v] = dist_fwd[u] + 1; parent_fwd[v] = u; q_fwd[t_fwd++] = v; }
                } else {
                    if (dist_fwd[v] != -1) { dist_bwd[v] = dist_bwd[u] + 1; parent_bwd[v] = u; meet = v; }
                    else if (dist_bwd[v] == -1) { dist_bwd[v] = dist_bwd[u] + 1; parent_bwd[v] = u; q_bwd[t_bwd++] = v; }
                }
            }
            temp[p] = orig;
        }
        if (meet != -1) break;
    }
    printf("\n--- Bidirectional BFS Transformation Sequence Results ---\n");
    if (meet == -1) {
        printf("Transformation Status: No valid sequence exists (Mutations = -1)\n");
    } else {
        int total = dist_fwd[meet] + dist_bwd[meet];
        printf("Shortest Mutations: %d (%d words) | Junction: '%s'\n\n", total, total + 1, dict[meet]);
        int path[total + 5], len = 0;
        for (int c = meet; c != -1; c = parent_fwd[c]) path[len++] = c;
        for (int i = 0; i < len / 2; i++) { int t = path[i]; path[i] = path[len - 1 - i]; path[len - 1 - i] = t; }
        for (int c = parent_bwd[meet]; c != -1; c = parent_bwd[c]) path[len++] = c;
        printf("Step-by-Step Transformation Chain:\n");
        for (int i = 0; i < len; i++) printf("  Step %2d : %s\n", i, dict[path[i]]);
    }
    printf("----------------------------------------------------------\n");
    free(dict); free(dist_fwd); free(dist_bwd); free(parent_fwd); free(parent_bwd); free(q_fwd); free(q_bwd);
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode *c = ht[i]; while (c) { HashNode *t = c; c = c->next; free(t); }
    }
    return 0;
}
