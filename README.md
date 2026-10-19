# 📘 Design and Analysis of Algorithms (DAA) Lab

This repository contains my laboratory assignments for the **Design and Analysis of Algorithms (DAA)** course. It serves as a comprehensive collection of algorithm implementations, complexity analysis, theoretical proofs, empirical observations, and supporting documentation completed throughout the entire semester.

---

## 👨‍🎓 Student Information

| Field | Details |
|-------|---------|
| **Name** | Aman Deep Pandit |
| **Student ID** | B525006 |
| **Branch** | Computer Engineering |
| **College** | IIIT Bhubaneswar |

---

## 📖 About Design and Analysis of Algorithms

Design and Analysis of Algorithms (DAA) focuses on designing efficient algorithms and evaluating their performance using rigorous asymptotic time and space complexity analysis. It provides systematic techniques to compare diverse computational paradigms—such as Divide and Conquer, Greedy Approaches, Dynamic Programming, and Graph / Disjoint Set Union (DSU) structures—enabling developers and researchers to devise optimal solutions for complex, real-world computational challenges.

---

## 📊 Semester Laboratory Overview

| Lab # | Laboratory Topic / Domain | Number of Problems | Primary Algorithmic Techniques & Themes |
|:---:|:---|:---:|:---|
| **LAB 01** | Asymptotic Analysis & Basic Recursion | 6 | Bubble Sort Empirical Analysis, Tower of Hanoi, Partition Points, Coin Tossing |
| **LAB 02** | Data Structure Performance & Priority Queues | 3 | Singly/Doubly Linked Lists vs Arrays, Benchmark Analysis, K-Way Merging |
| **LAB 03** | Divide and Conquer Foundations | 6 | Binary vs Ternary Search, Strassen's Matrix Multiplication, Defective Coin, Loop Invariants |
| **LAB 04** | Applications of Sorting & Order Statistics | 6 | Inversion Counting, Interval Scheduling, Two-Pointer Partitioning, Quickselect |
| **LAB 05** | Linear-Time Selection, Quicksort & Heapsort | 4 | Median-of-Medians Selection, In-Place Heap Sort, Dual-Pivot Quick Sort |
| **LAB 06** | Advanced Matrix Operations & Divide-and-Conquer | 4 | Vector Convolution (FFT/Karatsuba), Matrix Transformations, Sorting by Prefix Reversals |
| **LAB 07** | Advanced Dynamic Programming & Mathematical Puzzles | 7 | Matrix Chain Multiplication, Super Egg Drop, Reve's 4-Peg Puzzle, Interval Lifespans |
| **LAB 08** | Dynamic Programming Design Paradigm | 9 | LCS, LIS, MSIS, Edit Distance Traceback, Rod Cutting, Optimal BST, Collatz Conjecture |
| **LAB 09** | Greedy Algorithms & Optimization Paradigms | 10 | Fractional Knapsack Deterioration, Canonical Huffman, Min Refuel, Hu-Tucker Tree, Shortest Superstring |
| **LAB 10** | Graphs, Disjoint Set Union (DSU) & Connected Components | 5 | Online Bipartiteness, Dynamic 2D Islands, Max Weight with Size Limit, Reverse Time-Step DSU, Orbit Permutations |

---

## 📂 Repository Structure

```
DAA_LAB/
│
├── LAB 1/
│   ├── 1_Put them in order
│   ├── 2_Fair vs Biased Coin
│   ├── 3_Performance analysis of bubble sort
│   ├── 4_Tower of Hanoi(ToH)
│   ├── 5_Find the partition point
│   └── 6_Element-Uniqueness
│
├── LAB 2/
│   ├── 1_Array & Linked List Operations Benchmark
│   ├── 2_Complexity Verification
│   └── 3_Merge K Sorted Arrays
│
├── LAB 3/
│   ├── 1_Binary_vs_Ternary_Search
│   ├── 2_Search_Defective_Coin
│   ├── 3_Max_Min_DC
│   ├── 4_Strassen_Matrix_Multiplication
│   ├── 5_Special_Pattern_Matrix_Multiplication
│   └── 6_Selection_Sort_Loop_Invariant
│
├── LAB 4/
│   ├── 1_Application_of_Sorting_I
│   ├── 2_Application_of_Sorting_II
│   ├── 3_Application_of_Sorting_III
│   ├── 4_Application_of_Sorting_IV
│   ├── 5_Application_of_Sorting_V
│   └── 6_Application_of_Sorting_VI
│
├── LAB 5/
│   ├── 1_Median_Without_Sorting
│   ├── 2_Kth_Smallest_Element
│   ├── 3_Quick_Sort_File_Input
│   └── 4_Heap_Sort_File_Input
│
├── LAB 6/
│   ├── 1_1D_Array_Operations
│   ├── 2_2D_Matrix_Operations
│   ├── 3_Vector_Convolution_Divide_Conquer
│   └── 4_Sorting_Via_Reversal
│
├── LAB 7/
│   ├── 1_Invert_Coin_Triangle
│   ├── 2_Super_Egg_Testing
│   ├── 3_Reves_Puzzle
│   ├── 4_Security_Switches
│   ├── 5_Hitting_Moving_Target
│   ├── 6_Best_Time_To_Be_Alive
│   └── 7_Matrix_Chain_Multiplication
│
├── LAB 8/
│   ├── 1_Minimum_Coin_Change
│   ├── 2_Coin_Change_Total_Ways
│   ├── 3_Longest_Common_Subsequence
│   ├── 4_Longest_Increasing_Subsequence
│   ├── 5_Max_Sum_Increasing_Subsequence
│   ├── 6_Edit_Distance_Traceback
│   ├── 7_Rod_Cutting_Reconstruction
│   ├── 8_Optimal_Binary_Search_Tree
│   └── 9_Collatz_Conjecture_Analysis
│
├── LAB 9/
│   ├── 1_Fractional_Knapsack_Deterioration
│   ├── 2_Canonical_Huffman_Coding
│   ├── 3_Min_Refuel_Stops_Greedy
│   ├── 4_Min_Cost_Connect_Sticks
│   ├── 5_Candy_Distribution_Greedy
│   ├── 6_Reorganise_String_K_Distance
│   ├── 7_Minimise_Deviation_Array
│   ├── 8_Min_Meeting_Rooms
│   ├── 9_Hu_Tucker_Alphabetic_Tree
│   └── 10_Greedy_Superstring_Conjecture
│
├── LAB 10/
│   ├── 1_Online_Bipartiteness_Testing
│   ├── 2_Dynamic_Connected_Components_Grid
│   ├── 3_Max_Weight_Component_Size_Constraint
│   ├── 4_Reverse_Time_Step_DSU
│   └── 5_Lexicographically_Smallest_Permutation
│   
│
└── README.md
```

Each question directory typically contains:

- C source files (`solution.c` / `main.c`)
- Theoretical analysis and algorithmic proofs (`algorithm.md` / `DOCUMENTATION.md`)
- Summary & complexity justification (`SUMMARY.md`)
- GNUPlot scripts (`.gnu`) *(where empirical benchmarking is required)*

---

## ⚙️ Build

Compile the required source file(s) using GCC.

Single source file:

```bash
gcc solution.c -o solution.exe -lm
```

Multiple source files:

```bash
gcc main.c utils.c -o program.exe -lm
```

Using Makefile (where provided):

```bash
make all
```

---

## ▶️ Run

### Windows (PowerShell / Command Prompt)

```bash
.\solution.exe
```

### Linux / macOS

```bash
./solution
```

---
<br>

> Thank You

---
