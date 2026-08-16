# Question 1: Binary Search vs Ternary Search

## Problem Statement
In binary search, an $n$-element list is divided into nearly two equal halves, while in ternary search, it is divided into nearly three equal intervals. Then the search will be in one of the intervals. Design and implement a C program to search for an element $x$ in a sorted list of size $n$ using binary and ternary search. Justify and validate that binary search is better than ternary search via your implementation.

---

## Formal Algorithms (Pseudocode)

### 1. Binary Search
```text
BINARY-SEARCH(A, n, key):
    low = 0, high = n - 1
    while low <= high do
        mid = low + floor((high - low) / 2)
        if A[mid] == key then
            return mid
        else if key < A[mid] then
            high = mid - 1
        else
            low = mid + 1
        end if
    end while
    return -1
```

### 2. Ternary Search
```text
TERNARY-SEARCH(A, n, key):
    low = 0, high = n - 1
    while low <= high do
        mid1 = low + floor((high - low) / 3)
        mid2 = high - floor((high - low) / 3)
        if A[mid1] == key then
            return mid1
        else if A[mid2] == key then
            return mid2
        else if key < A[mid1] then
            high = mid1 - 1
        else if key > A[mid2] then
            low = mid2 + 1
        else
            low = mid1 + 1
            high = mid2 - 1
        end if
    end while
    return -1
```

---

## Theoretical Justification: Why Binary Search is Better

Although Ternary Search reduces the search space by a factor of 3 at each step (leading to a smaller tree height $\log_3 n$ compared to $\log_2 n$), it requires **more comparisons per step** to determine which third contains the key.

### Comparison Analysis:
1. **Binary Search**:
   - Number of recursive levels (tree height): $\lceil \log_2 n \rceil$
   - Number of comparisons per level: At most $2$ (checking `arr[mid] == key` and `key < arr[mid]`)
   - **Worst-Case Comparisons**:
     $$C_{\text{binary}}(n) \approx 2 \log_2 n$$

2. **Ternary Search**:
   - Number of recursive levels (tree height): $\lceil \log_3 n \rceil = \frac{\log_2 n}{\log_2 3} \approx \frac{\log_2 n}{1.585} \approx 0.631 \log_2 n$
   - Number of comparisons per level: At most $4$ (checking `arr[mid1] == key`, `arr[mid2] == key`, `key < arr[mid1]`, and `key > arr[mid2]`)
   - **Worst-Case Comparisons**:
     $$C_{\text{ternary}}(n) \approx 4 \log_3 n = 4 \times \frac{\log_2 n}{\log_2 3} \approx 4 \times 0.631 \log_2 n \approx 2.52 \log_2 n$$

### Conclusion:
Since $2.00 \log_2 n < 2.52 \log_2 n$, **Binary Search performs fewer comparisons than Ternary Search** in the worst case and is thus more efficient in practice for searching keys in arrays.

---

## Sample Output

```text
--- Test Scenario: Element Not Present (Worst Case) (Key = 50) ---
Binary  Search -> Found at index: -1 | Comparisons:  8
Ternary Search -> Found at index: -1 | Comparisons: 12
Result: Binary Search took fewer or equal comparisons (8 vs 12).
```

---

## How to Compile and Run

```bash
# Navigate to this folder
cd Question_1_Binary_vs_Ternary_Search

# Compile
gcc main.c -o main

# Run
./main
```
