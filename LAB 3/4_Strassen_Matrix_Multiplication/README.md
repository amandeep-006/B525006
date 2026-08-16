# Question 4: Matrix Multiplication using D&C Approach (Strassen's Method)

## Problem Statement
Write a C program to multiply two square matrices of size $n \times n$ using **Strassen’s method**.

---

## Formal Algorithm (Pseudocode)

```text
Algorithm: STRASSEN(A, B, n)
Input: Square matrices A and B of size n x n (n = 2^k)
Output: Product matrix C = A * B

1. if n == 1 then
2.     C[0][0] = A[0][0] * B[0][0]
3.     return C
4. end if

5. // Divide A and B into four (n/2) x (n/2) submatrices:
6. A11, A12, A21, A22 = PARTITION(A, n/2)
7. B11, B12, B21, B22 = PARTITION(B, n/2)

8. // Compute the 7 Strassen products recursively:
9.  P1 = STRASSEN(A11, (B12 - B22), n/2)
10. P2 = STRASSEN((A11 + A12), B22, n/2)
11. P3 = STRASSEN((A21 + A22), B11, n/2)
12. P4 = STRASSEN(A22, (B21 - B11), n/2)
13. P5 = STRASSEN((A11 + A22), (B11 + B22), n/2)
14. P6 = STRASSEN((A12 - A22), (B21 + B22), n/2)
15. P7 = STRASSEN((A11 - A21), (B11 + B12), n/2)

16. // Combine results to form C:
17. C11 = P5 + P4 - P2 + P6
18. C12 = P1 + P2
19. C21 = P3 + P4
20. C22 = P1 + P5 - P3 - P7

21. C = COMBINE(C11, C12, C21, C22)
22. return C
```

---

## Complexity Analysis

- **Recurrence Relation**:
  $$T(n) = 7 T\left(\frac{n}{2}\right) + \Theta(n^2)$$
- Using Master Theorem ($a = 7, b = 2, f(n) = \Theta(n^2)$):
  $$n^{\log_b a} = n^{\log_2 7} \approx n^{2.807}$$
  Since $f(n) = O(n^{2.807 - \epsilon})$ for $\epsilon \approx 0.807 > 0$, by **Case 1 of Master Theorem**:
  $$T(n) = \Theta(n^{\log_2 7}) \approx O(n^{2.81})$$

---

## Sample Output

```text
Matrix A (4x4):
  [    1    2    3    4 ]
  [    5    6    7    8 ]
  [    9    1    2    3 ]
  [    4    5    6    7 ]

Matrix B (4x4):
  [    8    7    6    5 ]
  [    4    3    2    1 ]
  [    1    2    3    4 ]
  [    5    6    7    8 ]

Product Matrix C (Strassen's Method) (4x4):
  [   39   43   47   51 ]
  [  111  115  119  123 ]
  [   93   88   83   78 ]
  [   93   97  101  105 ]

Validation: PASSED (Strassen result matches standard multiplication!)
```

---

## How to Compile and Run

```bash
# Navigate to this folder
cd Question_4_Strassen_Matrix_Multiplication

# Compile
gcc main.c -o main

# Run
./main
```
