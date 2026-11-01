#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct AdjNode {
    int to;
    struct AdjNode *next;
} AdjNode;

void add_edge(AdjNode **adj, int u, int v) {
    AdjNode *node = (AdjNode *)malloc(sizeof(AdjNode));
    node->to = v;
    node->next = adj[u];
    adj[u] = node;
}

int main(void) {
    int V, E, K, R;
    printf("Enter vertices (V), edges (E), number of hubs (K), and radius limit (R): ");
    if (scanf("%d %d %d %d", &V, &E, &K, &R) != 4 || V <= 0 || E < 0 || K <= 0 || K > V || R < 0) {
        fprintf(stderr, "Invalid input parameters!\n");
        return 1;
    }
    int *hubs = (int *)malloc((K + 1) * sizeof(int));
    printf("Enter %d designated hub vertices (1-indexed):\n", K);
    for (int i = 1; i <= K; i++) {
        printf("  Hub %d vertex: ", i);
        if (scanf("%d", &hubs[i]) != 1 || hubs[i] < 1 || hubs[i] > V) {
            fprintf(stderr, "Invalid hub vertex!\n");
            free(hubs);
            return 1;
        }
    }
    AdjNode **adj = (AdjNode **)calloc(V + 1, sizeof(AdjNode *));
    printf("Enter %d undirected edges as 'u v':\n", E);
    for (int i = 1; i <= E; i++) {
        int u, v;
        printf("  Edge %d: ", i);
        if (scanf("%d %d", &u, &v) != 2 || u < 1 || u > V || v < 1 || v > V) {
            fprintf(stderr, "Invalid edge input!\n");
            free(hubs);
            return 1;
        }
        add_edge(adj, u, v);
        add_edge(adj, v, u);
    }
    int *dist = (int *)malloc((V + 1) * sizeof(int));
    int *owner = (int *)malloc((V + 1) * sizeof(int));
    for (int i = 1; i <= V; i++) {
        dist[i] = -1;
        owner[i] = -1;
    }
    int *queue = (int *)malloc((V + 5) * sizeof(int));
    int head = 0, tail = 0;
    for (int i = 1; i <= K; i++) {
        int h = hubs[i];
        if (dist[h] == -1) {
            dist[h] = 0;
            owner[h] = i;
            queue[tail++] = h;
        }
    }
    while (head < tail) {
        int u = queue[head++];
        if (dist[u] >= R) continue;
        for (AdjNode *edge = adj[u]; edge; edge = edge->next) {
            int v = edge->to;
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                owner[v] = owner[u];
                queue[tail++] = v;
            } else if (dist[v] == dist[u] + 1) {
                if (owner[u] < owner[v]) {
                    owner[v] = owner[u];
                }
            }
        }
    }
    printf("\n--- Voronoi Cell Partitioning & Ownership Results ---\n");
    printf(" Vertex | Assigned Hub | Distance d_min | Hub Node | Coverage Status\n");
    printf("--------+--------------+----------------+----------+--------------------------\n");
    for (int v = 1; v <= V; v++) {
        if (owner[v] == -1 || dist[v] > R) {
            printf("  #%4d |     None     |      INF       |    --    | Uncovered (d_min > R)\n", v);
        } else {
            printf("  #%4d |    Hub %2d    |       %2d       | Node %2d  | Covered within Radius %d\n",
                   v, owner[v], dist[v], hubs[owner[v]], R);
        }
    }
    printf("--------------------------------------------------------------------------\n");
    free(hubs); free(dist); free(owner); free(queue);
    for (int i = 1; i <= V; i++) {
        AdjNode *curr = adj[i];
        while (curr) { AdjNode *tmp = curr; curr = curr->next; free(tmp); }
    }
    free(adj);
    return 0;
}
