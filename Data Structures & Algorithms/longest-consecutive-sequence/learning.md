# Longest Consecutive Sequence — My Interview Checklist

Here is the summary of the key ideas I used to solve `Longest Consecutive Sequence`. I can use this as a mental checklist in interviews when dealing with sorting, hash tables, and avoiding redundant work.

## 1. The Trap — `std::set` and Sorting

My first instinct might be to sort the array or use:

```cpp
set<int>
```

But both approaches introduce an `O(log N)` operation for maintaining or accessing ordered elements.

Sorting the array costs:

```text
O(N log N)
```

and `std::set` also gives `O(log N)` insertion and lookup because it is typically implemented as a **Red-Black Tree**.

This is important to remember:

```text
set          → balanced tree → O(log N)
unordered_set → hash table   → O(1) average
```

So if the problem explicitly requires:

```text
O(N) time
```

then blindly reaching for `set` or sorting will not satisfy the intended complexity.

My mental rule is:

> **If I need fast existence checks and I don't care about maintaining sorted order, think `unordered_set` instead of `set`.**

---

## 2. The Weapon — `unordered_set`

The key optimization is:

```cpp
unordered_set<int> st;
```

I insert all the numbers into the hash set first.

This gives me expected `O(1)` average-time lookup:

```cpp
st.find(x)
```

or:

```cpp
st.count(x)
```

Now I can quickly determine whether a number exists without sorting the entire array.

The overall approach becomes:

```text
Insert all numbers
        ↓
Check each number
        ↓
Determine whether it starts a sequence
        ↓
Count the sequence
        ↓
Track the maximum
```

The expected complexity becomes:

```text
Time:  O(N)
Space: O(N)
```

There is an important interview nuance here: `unordered_set` provides **average-case** `O(1)` lookup, not a strict worst-case guarantee. In normal competitive-programming analysis, this is treated as `O(1)` expected time.

My mental rule is:

> **When I need repeated membership checks and ordering is irrelevant, a hash set is often the right tool.**

---

## 3. The Clever Check — Only Start at the Beginning of a Sequence

Using a hash set alone is not enough.

If I simply tried to build a sequence starting from every number, I could end up repeatedly traversing the same sequence.

For example:

```text
nums = [1, 2, 3, 4, 5]
```

If I start counting from every element:

```text
1 → 2 → 3 → 4 → 5
2 → 3 → 4 → 5
3 → 4 → 5
4 → 5
5
```

I am doing a huge amount of redundant work.

In the worst case, this can approach:

```text
O(N²)
```

The key observation is that I only need to start counting when the current number is the **beginning of a consecutive sequence**.

I can identify that using:

```cpp
if(st.find(x - 1) == st.end())
```

This means:

> "`x` is the first element of a sequence only if `x - 1` does not exist."

For example:

```text
1 → 2 → 3 → 4 → 5
```

For `1`:

```text
0 does not exist
```

So `1` is the beginning.

For `2`:

```text
1 exists
```

So I don't start another sequence from `2`.

For `3`:

```text
2 exists
```

Again, I skip it.

The process becomes:

```text
1 → start counting
2 → skip
3 → skip
4 → skip
5 → skip
```

Now I only traverse each consecutive sequence from its smallest element.

This is the critical optimization that keeps the algorithm linear on average.

My mental rule is:

> **Before expanding a sequence, ask whether the current element is actually the beginning of that sequence.**

---

## My Interview Checklist

When I see `Longest Consecutive Sequence`, I should quickly ask myself:

1. **Do I need the elements sorted?**

If not, avoid unnecessary sorting.

2. **Do I need fast membership checks?**

Use:

```cpp
unordered_set<int>
```

instead of:

```cpp
set<int>
```

when ordering is irrelevant.

3. **Am I repeatedly traversing the same sequence?**

Before starting a `while` loop, check:

```cpp
if(st.find(x - 1) == st.end())
```

4. **What is the complexity?**

With the hash-set approach:

```text
Expected Time: O(N)
Space: O(N)
```

The important lesson I should take from this problem is:

> **The real trick is not just using a hash set. The real trick is using the hash set to identify sequence boundaries.**

`unordered_set` gives me fast existence checks, but the `x - 1` check is what prevents redundant traversal. Together, they transform an apparently sorting-based problem into an expected `O(N)` solution.
