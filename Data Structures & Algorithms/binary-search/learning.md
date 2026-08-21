# 2-Branch Binary Search — My Interview Checklist

Here is my summary of the **2-Branch Binary Search (Deferred Equality Check)** optimization. The main idea is to remove the equality check from the main loop and let the search converge to the final candidate.

## 1. The Code Changes — How the Mechanics Work

There are three important changes.

### Change 1 — `while(l <= r)` → `while(l < r)`

Instead of:

```cpp
while(l <= r)
```

I use:

```cpp
while(l < r)
```

The difference is that the loop continues only while there are at least two possible candidates.

Eventually:

```text
l == r
```

and the search stops.

The pointers never need to cross.

At this point, `l` and `r` represent the same final candidate.

---

### Change 2 — `r = m - 1` → `r = m`

In normal binary search, I might write:

```cpp
if(nums[m] > target)
    r = m - 1;
```

But in the 2-branch version, I am deliberately **not checking equality** inside the loop.

Therefore, when I decide that the answer lies on the left side, I cannot immediately discard `m`.

`nums[m]` might actually be the target.

So I use:

```cpp
r = m;
```

This keeps `m` as a valid candidate.

The general structure becomes:

```cpp
if(nums[m] < target)
    l = m + 1;
else
    r = m;
```

This is exactly the structure used for finding a lower bound.

---

### Change 3 — Move the Equality Check Outside

I don't check:

```cpp
nums[m] == target
```

during every iteration.

Instead, after the loop finishes:

```cpp
if(nums[l] == target)
    return l;

return -1;
```

At this point:

```text
l == r
```

so there is only one candidate left to verify.

The complete idea becomes:

```text
while(l < r)
        ↓
eliminate half the candidates
        ↓
l == r
        ↓
check the final candidate
```

My mental rule is:

> **Instead of repeatedly asking "Did I find it?", keep shrinking the search space until only one candidate remains, then verify that candidate.**

---

## 2. The Hardware Advantage — Fewer Branches

A traditional binary search might contain three logical outcomes:

```text
nums[m] < target
nums[m] == target
nums[m] > target
```

which can lead to multiple conditional branches inside the loop.

The 2-branch version reduces this to essentially:

```text
nums[m] < target
        ↓
     yes → l = m + 1
     no  → r = m
```

Equality is handled later.

This means the tight binary-search loop has fewer explicit decision points.

At the CPU level, conditional branches involve branch prediction, where the processor attempts to predict which path will execute next.

Reducing unnecessary branching can improve the efficiency of a very tight loop, although I should be careful not to oversell this: modern compilers and CPUs are sophisticated, and the real performance difference between binary-search variants is usually small.

The more important advantage is actually the **simpler invariant and control flow**.

My mental rule is:

> **If I can remove a branch without changing the algorithm's correctness, especially inside a hot loop, it can improve both code simplicity and potentially practical performance.**

---

## 3. The Algorithmic Advantage — Finding the First Occurrence

There is another major advantage of this structure.

The algorithm naturally finds the **first occurrence** of the target.

Consider:

```text
[2, 2, 2, 2, 2]
```

and:

```text
target = 2
```

A normal binary search might immediately find the middle `2` and return its index.

But this version does not stop when it finds equality.

Instead:

```cpp
if(nums[m] < target)
    l = m + 1;
else
    r = m;
```

Since:

```text
nums[m] == target
```

the condition:

```cpp
nums[m] < target
```

is false.

Therefore:

```cpp
r = m;
```

The algorithm continues searching toward the left.

Eventually:

```text
l == r == 0
```

so the first occurrence is found.

This is exactly the fundamental idea behind:

```cpp
lower_bound(begin, end, target)
```

which finds the first position where the value is greater than or equal to the target.

The important invariant is:

> **If `nums[m] >= target`, `m` can still be the first valid position, so I keep it by setting `r = m`.**

At the end, I simply verify whether the candidate actually equals the target.

---

## My Interview Checklist

When I want to use this binary-search pattern, I should remember:

1. Use:

```cpp
while(l < r)
```

instead of:

```cpp
while(l <= r)
```

2. Keep `m` as a candidate:

```cpp
r = m;
```

rather than:

```cpp
r = m - 1;
```

3. Use only two decisions inside the loop:

```cpp
if(nums[m] < target)
    l = m + 1;
else
    r = m;
```

4. Perform the equality check after convergence:

```cpp
if(nums[l] == target)
    return l;
return -1;
```

5. Remember the major benefit:

```text
Standard Binary Search
→ Find any occurrence

2-Branch / Lower-Bound Style
→ Find the first occurrence
```

The main lesson I should take from this pattern is:

> **Binary search becomes much cleaner when I define exactly what the final `l` represents and maintain that invariant throughout the loop.**

Instead of repeatedly checking whether I have already found the target, I continuously eliminate impossible candidates until only the correct boundary remains. This gives me a clean two-branch loop and naturally handles duplicates by converging to the first occurrence.
