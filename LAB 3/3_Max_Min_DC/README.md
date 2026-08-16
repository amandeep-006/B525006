# Question 3: Max and Min using Divide and Conquer (D&C) Approach

## Problem Statement
Using the divide and conquer approach, develop an algorithm to find the maximum and minimum elements in an array of size $n$ so that the number of comparisons will be bounded by $\frac{3n}{2}$. Implement your algorithm in C to validate the result.

---

## Formal Algorithm (Pseudocode)

```text
Algorithm: FIND-MIN-MAX-DC(A, low, high)
Input: Array A[low ... high]
Output: (min, max) pair of minimum and maximum elements in A[low ... high]

1. if low == high then
2.     return (A[low], A[low])               // Base Case 1: 0 comparisons
3. end if

4. if high == low + 1 then
5.     if A[low] < A[high] then              // Base Case 2: 1 comparison
6.         return (A[low], A[high])
7.     else
8.         return (A[high], A[low])
9.     end if
10. end if

11. // Divide step:
12. mid = floor((low + high) / 2)

13. // Conquer step:
14. (min1, max1) = FIND-MIN-MAX-DC(A, low, mid)
15. (min2, max2) = FIND-MIN-MAX-DC(A, mid + 1, high)

16. // Combine step: 2 comparisons
17. if min1 < min2 then overall_min = min1
18. else overall_min = min2

19. if max1 > max2 then overall_max = max1
20. else overall_max = max2

21. return (overall_min, overall_max)
```

---

## Mathematical Derivation of Comparisons

Let $T(n)$ be the number of element comparisons for an array of size $n = 2^k$:

$$T(n) = \begin{cases} 0 & \text{if } n = 1 \\ 1 & \text{if } n = 2 \\ 2 T(n/2) + 2 & \text{if } n > 2 \end{cases}$$

Expanding the recurrence by substitution:
$$T(n) = 2 T(n/2) + 2$$
$$T(n) = 2(2 T(n/4) + 2) + 2 = 4 T(n/4) + 4 + 2$$
$$T(n) = 2^{k-1} T(2) + \sum_{i=1}^{k-1} 2^i$$
$$T(n) = \frac{n}{2} \cdot 1 + 2(2^{k-1} - 1) = \frac{n}{2} + 2\left(\frac{n}{2} - 1\right) = \frac{n}{2} + n - 2 = \frac{3n}{2} - 2$$

Thus:
$$T(n) = \frac{3n}{2} - 2 < \frac{3n}{2}$$

### Comparison with Linear Approach:
- **Linear Scan**: Requires $2(n - 1) = 2n - 2$ comparisons.
- **Divide and Conquer**: Requires $\frac{3n}{2} - 2$ comparisons.
- **Savings**: Approximately $25\%$ fewer comparisons.

---

## Sample Output

```text
Array (Size 8): 22 13 -5 88 90 4 76 31 
Results:
  D&C Approach    -> Min:  -5 | Max:  90 | Comparisons: 10
  Linear Approach -> Min:  -5 | Max:  90 | Comparisons: 14
  Theoretical D&C Bound (3n/2): 12.0 | Actual D&C Formula (3n/2 - 2): 10
  [VALIDATED] D&C comparisons (10) <= 3n/2 (12.0)
```

---

## How to Compile and Run

```bash
# Navigate to this folder
cd Question_3_Max_Min_DC

# Compile
gcc main.c -o main

# Run
./main
```
