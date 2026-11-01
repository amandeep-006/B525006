# Shortest Path on Parity-Constrained Graphs via 0-1 BFS

## 1. Problem Formulation & Mathematical Model
Let $G = (V, E)$ be a directed graph with $n = |V|$ vertices and $m = |E|$ edges. Every directed edge $e = (u, v) \in E$ is associated with a binary weight:
$$w(u, v) \in \{0, 1\}$$
We are given a designated source vertex $S \in V$ and a non-negative parity penalty cost $C \ge 0$.

For any directed path $P = (v_0, v_1, \dots, v_k)$ originating at $v_0 = S$ and terminating at $v_k = v$:
1. The standard path weight is:
   $$W(P) = \sum_{i=1}^k w(v_{i-1}, v_i)$$
2. The number of weight-1 edges traversed along $P$ is denoted by $k_1(P)$. Because every edge has weight $w \in \{0, 1\}$, we have the direct identity:
   $$W(P) \equiv k_1(P)$$
3. The effective parity-constrained cost of path $P$ is defined by:
   $$\text{Cost}(P) = W(P) + \begin{cases} 0 & \text{if } k_1(P) \equiv 0 \pmod 2 \quad (\text{even parity}) \\ C & \text{if } k_1(P) \equiv 1 \pmod 2 \quad (\text{odd parity}) \end{cases}$$

The objective is to compute, for every vertex $v \in V$:
$$\text{Cost}^*(v) = \min_{P \in \mathcal{P}(S, v)} \text{Cost}(P)$$
where $\mathcal{P}(S, v)$ is the set of all directed paths from $S$ to $v$. If $\mathcal{P}(S, v) = \emptyset$, vertex $v$ is reported as unreachable ($\infty$).

---

## 2. State-Space Expansion & 0-1 BFS Algorithm

### 2.1 Expanded State Graph
Because the penalty depends entirely on the parity of $k_1(P)$, we construct a state-expanded graph $G' = (V', E')$ where each original vertex $u \in V$ is duplicated into two states:
$$u \mapsto \langle u, p \rangle, \quad p \in \{0, 1\}$$
where $p = k_1(P) \pmod 2$ represents the cumulative parity of weight-1 edges traversed from $S$.

For each directed edge $(u, v) \in E$ with weight $w \in \{0, 1\}$:
- **Case 1 ($w = 0$):** Traversing $(u, v)$ adds 0 to $k_1$, preserving parity:
  $$\langle u, 0 \rangle \xrightarrow{w=0} \langle v, 0 \rangle, \quad \langle u, 1 \rangle \xrightarrow{w=0} \langle v, 1 \rangle$$
- **Case 2 ($w = 1$):** Traversing $(u, v)$ adds 1 to $k_1$, flipping parity:
  $$\langle u, 0 \rangle \xrightarrow{w=1} \langle v, 1 \rangle, \quad \langle u, 1 \rangle \xrightarrow{w=1} \langle v, 0 \rangle$$

Notice that all transition edge weights in $G'$ remain strictly in $\{0, 1\}$.

### 2.2 0-1 BFS on State Graph
Because all edge weights are in $\{0, 1\}$, Dijkstra's algorithm can be replaced with a **0-1 BFS** using a double-ended queue (deque):
1. Initialize distances $D(\langle u, p \rangle) = \infty$ for all $u \in V, p \in \{0, 1\}$.
2. Set $D(\langle S, 0 \rangle) = 0$ and push $\langle S, 0 \rangle$ into the deque.
3. While the deque is non-empty, pop state $\langle u, p \rangle$ from the front:
   - For each outgoing edge $(u, v, w)$:
     - Target parity $p' = p \oplus w$.
     - Candidate distance $d' = D(\langle u, p \rangle) + w$.
     - If $d' < D(\langle v, p' \rangle)$:
       - $D(\langle v, p' \rangle) \leftarrow d'$.
       - If $w = 0$, push $\langle v, p' \rangle$ to the **front** of the deque.
       - If $w = 1$, push $\langle v, p' \rangle$ to the **back** of the deque.

### 2.3 Optimal Cost Derivation
For each vertex $v \in V$:
- Even parity path cost: $C_{\text{even}}(v) = D(\langle v, 0 \rangle)$.
- Odd parity path cost: $C_{\text{odd}}(v) = D(\langle v, 1 \rangle) + C$.
- The optimal effective cost is:
  $$\text{Cost}^*(v) = \min\big(C_{\text{even}}(v), \; C_{\text{odd}}(v)\big)$$
If both $D(\langle v, 0 \rangle) = \infty$ and $D(\langle v, 1 \rangle) = \infty$, vertex $v$ is unreachable.

---

## 3. Complexity Analysis
- **State Space Cardinality**: $|V'| = 2|V| = 2n$.
- **Edge Cardinality**: $|E'| = 2|E| = 2m$.
- **0-1 BFS Time Complexity**: Each state is inserted into the deque at most twice and extracted once. Transitions are evaluated in constant amortized time per edge:
  $$\mathcal{O}(|V'| + |E'|) = \mathcal{O}(V + E)$$
- **Auxiliary Space Complexity**: $\mathcal{O}(V + E)$ for adjacency representation, distance arrays, and the deque.
