# Question 6: Use of Loop Invariants in Sorting (Selection Sort)

## Problem Statement
Consider sorting $n$ numbers stored in an array $A[1 \dots n]$ by first finding the smallest element of $A[1 \dots n]$ and exchanging it with $A[1]$. Then, find the smallest element of $A[2 \dots n]$, and exchange it with $A[2]$. Continue in this manner for the first $(n - 1)$ elements of $A$.

1. Write a pseudocode for this algorithm.
2. What loop invariant does this algorithm maintain?
3. Why does it need to run for only the first $(n - 1)$ elements, rather than for all $n$ elements?
4. Give the worst-case running time of the above sorting algorithm in $\Theta$-notation.
5. Is the best-case running time any better?
6. Implement your algorithm in C to validate your claim.

---

## 1. Pseudocode

```text
SELECTION-SORT(A, n):
    for i = 1 to n - 1 do
        min_idx = i
        for j = i + 1 to n do
            if A[j] < A[min_idx] then
                min_idx = j
            end if
        end for
        if min_idx != i then
            exchange A[i] with A[min_idx]
        end if
    end for
```

---

## 2. Loop Invariant and Correctness Proof

### Loop Invariant:
> **At the start of each iteration of the outer `for` loop (index $i$), the subarray $A[1 \dots i-1]$ contains the $(i-1)$ smallest elements of the original array in sorted ascending order, and every element in $A[1 \dots i-1]$ is less than or equal to every element in the remaining subarray $A[i \dots n]$.**

### Proof:
- **Initialization (Base Case)**:
  Prior to the first iteration ($i = 1$), the subarray $A[1 \dots 0]$ is empty. An empty subarray trivially contains the $0$ smallest elements in sorted order. Thus, the loop invariant holds prior to the first iteration.

- **Maintenance (Inductive Step)**:
  During iteration $i$, the inner loop finds the index $\text{min\_idx}$ of the smallest element in $A[i \dots n]$. The algorithm then swaps $A[i]$ with $A[\text{min\_idx}]$.
  Since all elements in $A[i \dots n]$ were already greater than or equal to all elements in $A[1 \dots i-1]$, the new element placed at $A[i]$ is:
  1. Greater than or equal to every element in $A[1 \dots i-1]$.
  2. Less than or equal to every element in the remaining subarray $A[i+1 \dots n]$.
  
  Therefore, the extended subarray $A[1 \dots i]$ now contains the $i$ smallest elements of the original array in sorted order. Incrementing $i$ for the next iteration preserves the invariant.

- **Termination**:
  The loop terminates when $i = n$. By the invariant, the subarray $A[1 \dots n-1]$ contains the $(n-1)$ smallest elements in sorted order, and every element in $A[1 \dots n-1]$ is $\le A[n]$. Therefore, the single remaining element $A[n]$ must be the largest element and is already in its correct final position. Thus, the entire array $A[1 \dots n]$ is sorted.

---

## 3. Why Run for Only the First $(n - 1)$ Elements?

When the first $(n - 1)$ smallest elements are sorted and placed into positions $A[1 \dots n-1]$, all elements in $A[1 \dots n-1]$ are $\le A[n]$. The only remaining element at position $n$ has no other elements left to compare against and is mathematically guaranteed to be the maximum element. Executing a loop iteration for $i = n$ would perform zero inner comparisons and a redundant swap with itself.

---

## 4. Worst-Case Running Time

In each iteration $i$, the inner loop performs $(n - i)$ comparisons:
$$\sum_{i=1}^{n-1} (n - i) = (n - 1) + (n - 2) + \dots + 1 = \frac{n(n - 1)}{2} = \frac{n^2 - n}{2} = \Theta(n^2)$$

The number of swaps is at most $n - 1 = O(n)$.
Thus, the worst-case running time is **$\Theta(n^2)$**.

---

## 5. Is the Best-Case Running Time Any Better?

**No.** Even if the input array is already sorted, the algorithm does not terminate early. The inner loop must still scan all elements from $j = i+1$ to $n$ to identify the minimum element.
The total number of comparisons in the best case remains:
$$\frac{n(n - 1)}{2} = \Theta(n^2)$$

Hence, the best-case running time is **$\Theta(n^2)$**, exactly identical to the worst case.

---

## 6. Sample Input & Output

```text
Enter number of elements (n): 5
Enter 5 integers separated by spaces:
64 25 12 22 11

Original Array: [ 64 25 12 22 11 ]

===============================================================
        STEP-BY-STEP EXECUTION & LOOP INVARIANT TRACE          
===============================================================

--- Pass 1 (i = 0) ---
  [Invariant Check]
    Sorted subarray   A[0..-1] : [ ]
    Unsorted subarray A[0..4] : [ 64 25 12 22 11 ]
    Smallest element in unsorted part: 11 (at index 4)
    Action: Swapped A[0] (64) with A[4] (11)
    Array state after Pass 1: [ 11 25 12 22 64 ]

--- Pass 2 (i = 1) ---
  [Invariant Check]
    Sorted subarray   A[0..0] : [ 11 ]
    Unsorted subarray A[1..4] : [ 25 12 22 64 ]
    Smallest element in unsorted part: 12 (at index 2)
    Action: Swapped A[1] (25) with A[2] (12)
    Array state after Pass 2: [ 11 12 25 22 64 ]

--- Pass 3 (i = 2) ---
  [Invariant Check]
    Sorted subarray   A[0..1] : [ 11 12 ]
    Unsorted subarray A[2..4] : [ 25 22 64 ]
    Smallest element in unsorted part: 22 (at index 3)
    Action: Swapped A[2] (25) with A[3] (22)
    Array state after Pass 3: [ 11 12 22 25 64 ]

--- Pass 4 (i = 3) ---
  [Invariant Check]
    Sorted subarray   A[0..2] : [ 11 12 22 ]
    Unsorted subarray A[3..4] : [ 25 64 ]
    Smallest element in unsorted part: 25 (at index 3)
    Action: Element 25 is already at correct index 3 (No swap needed)
    Array state after Pass 4: [ 11 12 22 25 64 ]

===============================================================
Sorted Array  : [ 11 12 22 25 64 ]

Comparisons Made        : 10
Theoretical [n(n-1)/2]  : 10
Validation Result       : PASSED (Exact match with Theta(n^2))
```

---

## How to Compile and Run

```bash
# Navigate to this folder
cd Question_6_Selection_Sort_Loop_Invariant

# Compile
gcc main.c -o main

# Run
./main
```
