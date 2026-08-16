# Question 2: Search the Defective Coin

## Problem Statement
Imagine you are working as a quality-control engineer for a coin manufacturing company. All $n$ coins must have identical weights. A worker dropped a potentially defective (lighter) coin into a pile of $n-1$ perfect coins. The coin could be lighter due to over-shaping or could be perfect.

Using a balance weighing scale, design and implement a **Divide and Conquer** algorithm to find the lighter (defective) coin or report that none is lighter in at most $\log_2 n + c$ scale weighings (for a constant $c$).

---

## Formal Algorithm (Pseudocode)

```text
Algorithm: FIND-DEFECTIVE-COIN(coins, low, high, known_genuine)
Input:
  - coins[0 ... n-1]: Array of coin weights
  - low, high: Range of candidate coin indices
  - known_genuine: Index of a confirmed genuine coin (-1 if none identified yet)
Output:
  - Index of the defective (lighter) coin, or -1 if all coins are genuine.

1. count = high - low + 1

2. if count == 1 then
3.     if known_genuine != -1 then
4.         if BALANCE-SCALE(coins[low], coins[known_genuine]) < 0 then
5.             return low          // Found defective coin
6.         end if
7.     end if
8.     return -1                   // Coin is genuine (no defective coin)
9. end if

10. if count == 2 then
11.    result = BALANCE-SCALE(coins[low], coins[high])
12.    if result < 0 then return low
13.    else if result > 0 then return high
14.    else if known_genuine != -1 then
15.        if BALANCE-SCALE(coins[low], coins[known_genuine]) < 0 then return low
16.    end if
17.    return -1                   // Both are genuine
18. end if

19. // Divide & Conquer Step:
20. half = floor(count / 2)
21. left_start = low, left_end = low + half - 1
22. right_start = low + half, right_end = low + 2 * half - 1

23. scale_result = BALANCE-SCALE(coins[left_start ... left_end], coins[right_start ... right_end])

24. if scale_result < 0 then
25.     // Left pan is lighter -> defective coin is in left pan
26.     // Right pan coins are known genuine -> pass right_start as known_genuine
27.     return FIND-DEFECTIVE-COIN(coins, left_start, left_end, right_start)

28. else if scale_result > 0 then
29.     // Right pan is lighter -> defective coin is in right pan
30.     // Left pan coins are known genuine -> pass left_start as known_genuine
31.     return FIND-DEFECTIVE-COIN(coins, right_start, right_end, left_start)

32. else
33.     // Both pans balance! All coins on pans are genuine.
34.     if count mod 2 == 0 then
35.         return -1               // All coins in range are genuine
36.     end if

37.     // If odd, the single remaining coin is at index 'high'
38.     if BALANCE-SCALE(coins[high], coins[low]) < 0 then
39.         return high             // The odd coin is defective
40.     end if
41.     return -1                   // No defective coin
42. end if
```

---

## Step-by-Step Divide & Conquer Strategy

1. **Divide**:
   - Given $k$ candidate coins, split them into two equal groups of size $m = \lfloor k/2 \rfloor$:
     - **Left Pan**: $m$ coins
     - **Right Pan**: $m$ coins
     - **Remainder**: $1$ coin (if $k$ is odd) or $0$ coins (if $k$ is even).

2. **Conquer / Weigh**:
   - Place $m$ coins on each pan of the balance scale:
     - **Left Pan is lighter**: Defective coin is in the Left Pan. Recurse on Left Pan ($m$ coins). The Right Pan coins are proven genuine and can serve as a reference.
     - **Right Pan is lighter**: Defective coin is in the Right Pan. Recurse on Right Pan ($m$ coins). The Left Pan coins are proven genuine.
     - **Pans Balance**: All $2m$ coins on both pans are genuine.
       - If $k$ is even ($k = 2m$): **No defective coin exists** in the pile.
       - If $k$ is odd: The single remaining coin at `high` is tested against a known genuine coin (1 extra weighing). If lighter, it is defective; otherwise, **no defective coin exists**.

3. **Base Cases ($k = 1$ or $k = 2$)**:
   - Compare candidates against each other or against a confirmed genuine coin to conclude in $1$ weighing.

---

## Complexity Analysis & $\log_2 n + c$ Proof

- **Recurrence Relation for Weighings $W(n)$**:
  $$W(n) = W\left(\left\lfloor\frac{n}{2}\right\rfloor\right) + 1$$
- **Base Conditions**:
  - $W(1) \le 1$
  - $W(2) \le 2$
- **Total Weighings**:
  $$W(n) \le \lceil \log_2 n \rceil + 1 \le \log_2 n + 2$$
  Setting constant $c = 2$, the algorithm is strictly bounded by:
  $$W(n) \le \log_2 n + c$$
- **Time Complexity**: $O(\log_2 n)$.

---

## Sample Test Runs

```text
===============================================================
     DAA Lab 03 - Question 2: Search the Defective Coin       
===============================================================

---------------------------------------------------------------
Total Coins: 9 | Actual Defective Coin Index: 6
Result: Defective (lighter) coin FOUND at index 6 (Weight: 9.2)
Scale weighings used: 3 (Theoretical Bound: <= log2(9) + 2)

---------------------------------------------------------------
Total Coins: 16 | Actual Defective Coin Index: 3
Result: Defective (lighter) coin FOUND at index 3 (Weight: 9.2)
Scale weighings used: 4 (Theoretical Bound: <= log2(16) + 2)

---------------------------------------------------------------
Total Coins: 11 | Actual Defective Coin Index: 10
Result: Defective (lighter) coin FOUND at index 10 (Weight: 9.2)
Scale weighings used: 2 (Theoretical Bound: <= log2(11) + 2)

---------------------------------------------------------------
Total Coins: 12 | Actual Defective Coin Index: -1
Result: NO defective coin found. All coins are perfectly weighted (10.0).
Scale weighings used: 1 (Theoretical Bound: <= log2(12) + 2)
```

---

## How to Compile and Run

```bash
# Navigate to this folder
cd Question_2_Search_Defective_Coin

# Compile
gcc main.c -o main

# Run
./main
```
