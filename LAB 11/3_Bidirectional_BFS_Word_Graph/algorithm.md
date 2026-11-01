# Bidirectional BFS for Shortest Transformation Sequence in a Word Graph

## 1. Problem Definition & Mathematical Formulation
Let $\Sigma = \{\text{'a'}, \text{'b'}, \dots, \text{'z'}\}$ be the lowercase Latin alphabet of size $|\Sigma| = 26$.
We are given:
- A dictionary of $N$ unique words $\mathcal{D} = \{w_1, w_2, \dots, w_N\} \subset \Sigma^L$, where every word has identical length $L$.
- A source word $A \in \Sigma^L$ and a destination word $B \in \mathcal{D}$.

Define the Hamming distance $d_H(u, v)$ between two words $u, v \in \Sigma^L$ as the number of character positions at which they differ:
$$d_H(u, v) = \sum_{j=1}^L \mathbf{1}_{\{u[j] \neq v[j]\}}$$

### 1.1 Word Graph Representation
Construct an implicit undirected word graph $G = (V, E)$ where:
- Vertex set: $V = \mathcal{D} \cup \{A\}$.
- Edge set: $E = \{(u, v) \in V \times V \mid d_H(u, v) = 1\}$.

A transformation sequence of length $k$ is an ordered sequence of words:
$$P = \langle W_0, W_1, W_2, \dots, W_k \rangle$$
satisfying:
1. $W_0 = A$ and $W_k = B$.
2. $W_i \in \mathcal{D}$ for all $1 \le i \le k$.
3. $(W_{i-1}, W_i) \in E$ for all $1 \le i \le k$.

The objective is to find the minimum number of mutations $k^*$, corresponding to the shortest path distance $\text{dist}_G(A, B)$. If no connected path exists, return $-1$.

---

## 2. Algorithmic Formulation: Bidirectional Breadth-First-Search

### 2.1 The Combinatorial Curse of Unidirectional Search
In a standard forward BFS originating at $A$, each word has $L \times 25$ potential single-character mutations. If the shortest path has length $k$, the search tree explores:
$$\mathcal{O}\left(b^k\right) \quad \text{states}, \quad \text{where } b \le 25L$$
For $k = 6$ and $L = 5$, $b^k \approx 125^6 \approx 3.8 \times 10^{12}$, creating an intractable search space.

### 2.2 Bidirectional Search Frontiers & Exponential Reduction
Bidirectional BFS maintains two simultaneous search frontiers:
1. **Forward Frontier ($\mathcal{F}_{\text{fwd}}$)** expanding from $A$.
2. **Backward Frontier ($\mathcal{F}_{\text{bwd}}$)** expanding from $B$.

By expanding the two frontiers inward until they collide at an intermediate junction word $M \in V$:
$$\mathcal{O}\left(2 \cdot b^{k/2}\right) = \mathcal{O}\left(b^{k/2}\right)$$
The search space is reduced exponentially from $b^k$ to $2b^{k/2}$. For $k = 6$, $2 \cdot 125^3 \approx 3.9 \times 10^6$ operations, executing in milliseconds.

### 2.3 Optimal Frontier Expansion & Collision Detection
1. **Hash Table Lookup**: Insert dictionary words into a hash table with open addressing / chaining using polynomial rolling hashing for $\mathcal{O}(L)$ membership queries.
2. **Frontier Balancing**: In each iteration, pop and expand all nodes at the current level of the **smaller** active frontier:
   $$\text{Choose } \mathcal{F}^* = \arg\min\left(|\mathcal{F}_{\text{fwd}}|, |\mathcal{F}_{\text{bwd}}|\right)$$
3. **Neighbor Generation**: For each word $W$ in $\mathcal{F}^*$, substitute character $W[j]$ with each letter $c \in \Sigma \setminus \{W[j]\}$ for $1 \le j \le L$.
4. **Collision**: If a generated mutated word $W'$ is already present in the opposing frontier:
   $$\text{Shortest Path Length } k^* = \text{dist}_{\text{fwd}}(W') + \text{dist}_{\text{bwd}}(W')$$
   Terminate search immediately and backtrack through `parent_fwd` and `parent_bwd` to reconstruct the exact mutation sequence.

---

## 3. Complexity Analysis
- **Neighbor Generation per Node**: Exactly $25 \times L$ mutated string candidates.
- **Lookup Complexity**: $\mathcal{O}(L)$ string hashing and comparison per candidate.
- **Overall Search Time Complexity**:
  $$\mathcal{O}\left(b^{\lceil k/2 \rceil} \cdot L\right) \ll \mathcal{O}(b^k \cdot L)$$
- **Auxiliary Space Complexity**: $\mathcal{O}(N \cdot L)$ to store dictionary strings, hash indices, and frontier queues.
