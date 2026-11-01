# Multi-Source BFS for Radius-Constrained Voronoi Cell Partitioning

## 1. Problem Definition & Mathematical Formulation
Let $G = (V, E)$ be an unweighted, undirected graph with $n = |V|$ vertices and $m = |E|$ edges. We are provided with:
1. A designated set of $K$ service hub vertices:
   $$\mathcal{H} = \{h_1, h_2, \dots, h_K\} \subseteq V, \quad \text{indexed } 1 \le i \le K$$
2. A non-negative integer coverage radius threshold:
   $$R \ge 0$$

For any vertex pair $(u, v) \in V \times V$, let $\text{dist}(u, v)$ denote the unweighted shortest path distance (minimum number of edge hops).
For each vertex $v \in V$:
- The distance from $v$ to hub $h_i$ is $d_i(v) = \text{dist}(v, h_i)$.
- The minimum distance to any hub is:
  $$d_{\min}(v) = \min_{1 \le i \le K} d_i(v)$$

### 1.1 Radius-Constrained Voronoi Partitioning Rules
Each vertex $v \in V$ must be assigned an ownership label $\text{owner}[v] \in \{1, 2, \dots, K\} \cup \{-1\}$ such that:
1. **Coverage Threshold ($R$):**
   $$\text{If } d_{\min}(v) > R \implies \text{owner}[v] = -1 \quad (\text{outside service boundary})$$
2. **Closest Hub Assignment:**
   $$\text{If } d_{\min}(v) \le R \implies \text{owner}[v] = \arg\min_{1 \le i \le K} d_i(v)$$
3. **Deterministic Tie-Breaking:**
   If multiple hubs achieve the identical minimum distance $d_{\min}(v)$, the vertex is assigned to the hub with the smallest numerical index:
   $$\text{owner}[v] = \min \left\{ i \in \{1, \dots, K\} \;\middle|\; d_i(v) = d_{\min}(v) \right\}$$

---

## 2. Multi-Source BFS Algorithmic Design

### 2.1 Multi-Source Initialization
Instead of executing $K$ independent single-source BFS traversals (which would require $\mathcal{O}(K(V + E))$ time), we employ a unified **Multi-Source BFS**:
1. Initialize arrays:
   $$\text{dist}[v] \leftarrow \infty, \quad \text{owner}[v] \leftarrow -1 \quad \forall v \in V$$
2. Maintain a standard first-in-first-out (FIFO) queue $\mathcal{Q}$.
3. For each hub index $i = 1, 2, \dots, K$:
   - Let $u = h_i$.
   - If $\text{dist}[u] = \infty$:
     $$\text{dist}[u] \leftarrow 0, \quad \text{owner}[u] \leftarrow i, \quad \text{enqueue}(u)$$
   - Enqueueing hubs in ascending order of their identifier $i \in \{1, \dots, K\}$ ensures that among equal-distance frontiers, smaller hub indices are prioritized.

### 2.2 Level-Synchronous Expansion with Radius Pruning
While queue $\mathcal{Q}$ is non-empty:
1. Dequeue vertex $u$. Let $d = \text{dist}[u]$.
2. **Radius Pruning**: If $d = R$, do not traverse incident edges of $u$ because any unvisited neighbor would be at distance $d + 1 = R + 1 > R$.
3. For each adjacent vertex $v \in \text{Adj}(u)$:
   - **Case 1 (Unvisited neighbor):** If $\text{dist}[v] = \infty$:
     $$\text{dist}[v] \leftarrow d + 1, \quad \text{owner}[v] \leftarrow \text{owner}[u], \quad \text{enqueue}(v)$$
   - **Case 2 (Equidistant collision):** If $\text{dist}[v] = d + 1$:
     - Multiple hubs reach $v$ at the exact same distance. Enforce deterministic tie-breaking:
       $$\text{owner}[v] \leftarrow \min(\text{owner}[v], \; \text{owner}[u])$$

---

## 3. Complexity Analysis
- **Graph Traversal Time**: Every vertex is enqueued at most once, and each undirected edge $(u, v)$ is inspected at most twice (once from each endpoint).
  $$\mathcal{T}(V, E) = \mathcal{O}(|V| + |E|)$$
- **Tie-Breaking Overhead**: Equidistant collisions are handled in $\mathcal{O}(1)$ comparisons per edge examination.
- **Total Time Complexity**: $\mathcal{O}(V + E)$, strictly independent of the hub count $K$.
- **Auxiliary Space Complexity**: $\mathcal{O}(V + E)$ for adjacency representation, FIFO queue, and tracking arrays `dist` and `owner`.
