# Valid Sudoku — My Interview Checklist

Here is why I consider this `Valid Sudoku` solution highly optimized. The key improvements come from understanding the fixed constraints of the Sudoku board and choosing the simplest data structures that fit those constraints.

## 1. Memory Architecture — Fixed-Size Arrays

Instead of using dynamically allocated structures such as:

```cpp
vector<vector<bool>> row;
```

I use:

```cpp
bool row[9][9] = {false};
```

The important advantage is that I already know the Sudoku board has a fixed size of `9 × 9`.

That means I don't need a dynamically sized container at all.

The array contains only:

```text
9 × 9 = 81
```

boolean values, so the amount of memory required is fixed.

A fixed-size C-style array is stored as part of the local stack frame when declared locally, avoiding a separate dynamic allocation for the array itself.

It also provides contiguous, predictable storage, which is friendly to CPU cache behavior.

My mental rule is:

> **When the problem gives me a genuinely fixed and very small data size, don't introduce dynamic allocation unless I actually need it.**

---

## 2. Zero-Copy Safety — `const` Reference

I use:

```cpp
const vector<vector<char>>& board
```

instead of:

```cpp
vector<vector<char>> board
```

Passing the board by value can require copying the entire nested vector structure and its character data.

That introduces unnecessary work before the actual Sudoku validation begins.

By using:

```cpp
const vector<vector<char>>& board
```

I access the original board directly without creating a complete copy.

The `const` is also important because my validation algorithm only needs to **read** the board.

So:

```text
&     → avoids unnecessary copying
const → prevents accidental modification
```

This gives me a cleaner and safer function interface.

My mental rule is:

> **If I only need to inspect a large container and don't need to modify it, pass it as `const &`.**

---

## 3. Fixed Constraints — Why the Complexity Becomes `O(1)`

The most important observation is that the Sudoku board is **always `9 × 9`**.

Therefore, the number of cells is fixed:

```text
9 × 9 = 81
```

Even if I iterate through all 81 cells:

```cpp
for(int i = 0; i < 9; i++)
{
    for(int j = 0; j < 9; j++)
    {
        // validation
    }
}
```

the number of iterations never grows with the input.

Therefore, under the standard complexity definition for this problem:

```text
Time:  O(1)
Space: O(1)
```

The reason is that the input size itself is fixed.

This is different from saying that the algorithm is `O(N)` for a general `N × N` board.

If the board were generalized to an `N × N` Sudoku board, then scanning the board would become:

```text
O(N²)
```

But for the actual LeetCode constraint of a fixed `9 × 9` board:

```text
81 operations
```

is a constant.

My mental rule is:

> **Always look at the actual constraints before assigning complexity. If the input size is strictly bounded by a constant, the algorithm can technically be `O(1)`.**

---

## My Interview Checklist

When I see a fixed-size problem like `Valid Sudoku`, I should quickly ask myself:

1. **Is the input size genuinely fixed?**

For Sudoku:

```text
9 × 9 = 81
```

so I don't need to design for arbitrary input sizes.

2. **Can I use fixed-size arrays?**

If the dimensions are known at compile time:

```cpp
bool row[9][9] = {false};
```

can be simpler and avoids dynamic allocation for that structure.

3. **Am I copying the input unnecessarily?**

Use:

```cpp
const vector<vector<char>>& board
```

when the board is read-only.

4. **What is the actual complexity?**

For the fixed `9 × 9` board:

```text
Time:  O(1)
Space: O(1)
```

For a generalized `N × N` version, the analysis would instead depend on `N`.

The main lesson I should take from this problem is:

> **Constraints are part of the algorithm.**

I shouldn't automatically reach for dynamic containers or assume every matrix problem has variable-sized input. When the problem guarantees a tiny, fixed structure like a `9 × 9` Sudoku board, I can exploit that constraint to keep the implementation simple, predictable, and constant in both time and auxiliary space.
