# Question 5: Multiply Special-Pattern Square Matrices using D&C Approach

## Problem Statement
Two $n \times n$ matrices are provided, where $n = 2^k$. Each matrix has the recursive structure:
$$M = \begin{pmatrix} M_1 & M_2 \\ M_2 & M_1 \end{pmatrix}$$
where each block recursively possesses the same structure down to $1 \times 1$ scalar elements.

Give a Divide-and-Conquer approach-based $O(n^2)$ algorithm for multiplying two such matrices and validate the complexity.

---

## Formal Algorithm (Pseudocode)

```text
Algorithm: SPECIAL-MATRIX-MULTIPLY(A, B, n)
Input: Symmetric block matrices A and B of size n x n (n = 2^k)
Output: Product matrix C = A * B

1. if n == 1 then
2.     C[0][0] = A[0][0] * B[0][0]
3.     return C
4. end if

5. // Extract blocks A1, A2 from A and B1, B2 from B (each of size n/2 x n/2):
6. A1 = A[0 ... n/2 - 1][0 ... n/2 - 1]
7. A2 = A[0 ... n/2 - 1][n/2 ... n - 1]
8. B1 = B[0 ... n/2 - 1][0 ... n/2 - 1]
9. B2 = B[0 ... n/2 - 1][n/2 ... n - 1]

10. // Form sum and difference matrices (O(n^2) operations):
11. SA = A1 + A2
12. DA = A1 - A2
13. SB = B1 + B2
14. DB = B1 - B2

15. // Compute only TWO recursive multiplications of size (n/2) x (n/2):
16. P = SPECIAL-MATRIX-MULTIPLY(SA, SB, n/2)     // P = C1 + C2
17. Q = SPECIAL-MATRIX-MULTIPLY(DA, DB, n/2)     // Q = C1 - C2

18. // Reconstruct C1 and C2:
19. C1 = (P + Q) / 2
20. C2 = (P - Q) / 2

21. // Assemble symmetric product matrix C = [C1 C2; C2 C1]:
22. C = ASSEMBLE(C1, C2)
23. return C
```

---

## Mathematical Derivation

Let $A = \begin{pmatrix} A_1 & A_2 \\ A_2 & A_1 \end{pmatrix}$ and $B = \begin{pmatrix} B_1 & B_2 \\ B_2 & B_1 \end{pmatrix}$.

The product matrix $C = A \cdot B$ is:
$$C = \begin{pmatrix} A_1 B_1 + A_2 B_2 & A_1 B_2 + A_2 B_1 \\ A_2 B_1 + A_1 B_2 & A_2 B_2 + A_1 B_1 \end{pmatrix} = \begin{pmatrix} C_1 & C_2 \\ C_2 & C_1 \end{pmatrix}$$
where:
$$C_1 = A_1 B_1 + A_2 B_2$$
$$C_2 = A_1 B_2 + A_2 B_1$$

### Reducing Multiplications to 2
Notice that:
$$P = (A_1 + A_2)(B_1 + B_2) = A_1 B_1 + A_1 B_2 + A_2 B_1 + A_2 B_2 = C_1 + C_2$$
$$Q = (A_1 - A_2)(B_1 - B_2) = A_1 B_1 - A_1 B_2 - A_2 B_1 + A_2 B_2 = C_1 - C_2$$

Therefore:
$$C_1 = \frac{P + Q}{2}, \quad C_2 = \frac{P - Q}{2}$$

---

## Complexity Analysis (Master Theorem)

- **Recurrence Relation**:
  $$T(n) = 2 T\left(\frac{n}{2}\right) + c \cdot n^2$$
  where $c \cdot n^2$ is the time needed for matrix additions and subtractions.

- **Applying Master Theorem**:
  - $a = 2, b = 2, f(n) = \Theta(n^2)$
  - $n^{\log_b a} = n^{\log_2 2} = n^1 = n$
  - Since $f(n) = \Theta(n^2) = \Omega(n^{1 + \epsilon})$ for $\epsilon = 1$, and the regularity condition holds:
    $$2 f(n/2) = 2 c \left(\frac{n}{2}\right)^2 = \frac{c n^2}{2} \le \frac{1}{2} f(n)$$
  - By **Case 3 of the Master Theorem**:
    $$T(n) = \Theta(n^2)$$

---

## Sample Output

```text
Product C (O(n^2) D&C Algorithm) (4x4):
  [   36   24   24   36 ]
  [   24   36   36   24 ]
  [   24   36   36   24 ]
  [   36   24   24   36 ]

Product C (Standard Verification) (4x4):
  [   36   24   24   36 ]
  [   24   36   36   24 ]
  [   24   36   36   24 ]
  [   36   24   24   36 ]

Validation: PASSED (Results match identically!)
```

---

## How to Compile and Run

```bash
# Navigate to this folder
cd Question_5_Special_Pattern_Matrix_Multiplication

# Compile
gcc main.c -o main

# Run
./main
```
