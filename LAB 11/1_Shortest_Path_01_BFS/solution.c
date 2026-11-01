#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INF 1000000000

typedef struct Edge {
    int to, weight;
    struct Edge *next;
} Edge;

typedef struct {
    int u, parity;
} State;

typedef struct {
    State *data;
    int head, tail;
} Deque;

Deque* create_deque(int cap) {
    Deque *dq = (Deque *)malloc(sizeof(Deque));
    dq->data = (State *)malloc((2 * cap + 5) * sizeof(State));
    dq->head = dq->tail = cap;
    return dq;
}

void push_front(Deque *dq, State s) { dq->data[--dq->head] = s; }
void push_back(Deque *dq, State s) { dq->data[dq->tail++] = s; }
State pop_front(Deque *dq) { return dq->data[dq->head++]; }
bool is_empty(Deque *dq) { return dq->head == dq->tail; }

void add_edge(Edge **adj, int u, int v, int w) {
    Edge *e = (Edge *)malloc(sizeof(Edge));
    e->to = v; e->weight = w; e->next = adj[u]; adj[u] = e;
}

int main(void) {
    int V, E, S, C;
    printf("Enter number of vertices (V), edges (E), source (S), and odd penalty (C): ");
    if (scanf("%d %d %d %d", &V, &E, &S, &C) != 4 || V <= 0 || E < 0 || S < 1 || S > V || C < 0) {
        fprintf(stderr, "Invalid input parameters!\n");
        return 1;
    }
    Edge **adj = (Edge **)calloc(V + 1, sizeof(Edge *));
    printf("Enter %d directed edges as 'u v w' (where w is 0 or 1):\n", E);
    for (int i = 1; i <= E; i++) {
        int u, v, w;
        printf("  Edge %d: ", i);
        if (scanf("%d %d %d", &u, &v, &w) != 3 || u < 1 || u > V || v < 1 || v > V || (w != 0 && w != 1)) {
            fprintf(stderr, "Invalid edge input!\n");
            return 1;
        }
        add_edge(adj, u, v, w);
    }
    int dist[V + 1][2];
    for (int i = 1; i <= V; i++) dist[i][0] = dist[i][1] = INF;
    dist[S][0] = 0;
    Deque *dq = create_deque(4 * V + 10);
    push_back(dq, (State){S, 0});
    while (!is_empty(dq)) {
        State cur = pop_front(dq);
        int u = cur.u, p = cur.parity;
        for (Edge *e = adj[u]; e; e = e->next) {
            int v = e->to, w = e->weight, np = p ^ w;
            if (dist[u][p] + w < dist[v][np]) {
                dist[v][np] = dist[u][p] + w;
                if (w == 0) push_front(dq, (State){v, np});
                else push_back(dq, (State){v, np});
            }
        }
    }
    printf("\n--- Shortest Path on Parity-Constrained Graph ---\n");
    printf(" Vertex | Even-Path W(P) | Odd-Path W(P)+C | Min Effective Cost | Status\n");
    printf("--------+----------------+-----------------+--------------------+-------------\n");
    for (int v = 1; v <= V; v++) {
        int c_even = dist[v][0];
        int c_odd = (dist[v][1] == INF) ? INF : dist[v][1] + C;
        int best = (c_even < c_odd) ? c_even : c_odd;
        if (best >= INF) {
            printf("  #%4d |      INF       |       INF       |        INF         | Unreachable\n", v);
        } else {
            const char *par = (c_even <= c_odd) ? "Even Parity" : "Odd Parity";
            char s_even[16], s_odd[16];
            if (c_even == INF) snprintf(s_even, sizeof(s_even), "INF");
            else snprintf(s_even, sizeof(s_even), "%d", c_even);
            if (c_odd == INF) snprintf(s_odd, sizeof(s_odd), "INF");
            else snprintf(s_odd, sizeof(s_odd), "%d", c_odd);
            printf("  #%4d |      %4s      |      %4s       |        %4d        | Reachable (%s)\n",
                   v, s_even, s_odd, best, par);
        }
    }
    printf("------------------------------------------------------------------------------\n");
    for (int i = 1; i <= V; i++) {
        Edge *curr = adj[i];
        while (curr) { Edge *tmp = curr; curr = curr->next; free(tmp); }
    }
    free(adj); free(dq->data); free(dq);
    return 0;
}
