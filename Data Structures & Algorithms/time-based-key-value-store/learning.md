# Binary Search Patterns — My Interview Cheat Sheet

Here is my summary of the main Binary Search templates and the situations where I should use each one. The important thing is not memorizing one template, but recognizing **what the search is actually trying to find**.

## 1. Classic 3-Branch — Exact Match

The standard template is:

```cpp
while(l <= r)
{
    int m = l + (r - l) / 2;

    if(nums[m] == target)
        return m;

    if(nums[m] < target)
        l = m + 1;
    else
        r = m - 1;
}
```

I should use this when I simply need to determine whether an exact target exists in a sorted array.

The three possibilities are:

```text
nums[m] == target → found → return
nums[m] < target  → search right
nums[m] > target  → search left
```

The important rule is that once I know `m` is not the answer, I can safely discard it:

```cpp
l = m + 1;
r = m - 1;
```

Because of this, the `l <= r` template is very straightforward and is unlikely to get stuck.

My mental rule:

> **If I only need any exact occurrence, use the classic 3-branch binary search.**

---

## 2. Record and Move — Finding the Best Valid Answer

Sometimes I don't want to stop when I find a valid answer.

I want to find the **best** answer among all valid possibilities.

In that case, I can maintain:

```cpp
int ans = ...;
```

and continue searching after finding a valid midpoint.

For example, suppose I need the largest value satisfying:

```text
value <= target
```

When the midpoint is valid:

```cpp
if(nums[m] <= target)
{
    ans = nums[m];
    l = m + 1;
}
```

I record it and continue searching to the right for a potentially better answer.

If the midpoint is too large:

```cpp
else
{
    r = m - 1;
}
```

This pattern is useful for problems such as:

* Finding a floor value
* Finding the largest timestamp `<= target` in TimeMap
* Binary Search on Answer problems such as Koko Eating Bananas

The key idea is:

```text
Valid answer
    ↓
Save it
    ↓
Continue searching for a better answer
```

Unlike exact-match binary search, I don't immediately return.

My mental rule:

> **If I need the best valid answer rather than just any valid answer, record the current candidate and keep searching.**

This is also a very safe template because I explicitly remove `m` after recording it:

```cpp
l = m + 1;
```

or:

```cpp
r = m - 1;
```

so I avoid many boundary-related infinite-loop issues.

---

## 3. 2-Branch Squeeze — Advanced Boundary Search

The more advanced template is:

```cpp
while(l < r)
{
    int m = l + (r - l) / 2;

    if(condition)
        l = m + 1;
    else
        r = m;
}
```

The key difference is that I don't ask:

```cpp
nums[m] == target?
```

inside the loop.

Instead, I ask:

> **Which side can still contain the answer?**

I keep shrinking the search space until:

```text
l == r
```

At that point, the remaining position is my answer candidate.

This is especially useful for:

* First occurrence
* Last occurrence
* Lower bound
* Upper bound
* Minimum in a rotated sorted array
* Other boundary-finding problems

For example, to find the first occurrence of a target:

```cpp
while(l < r)
{
    int m = l + (r - l) / 2;

    if(nums[m] < target)
        l = m + 1;
    else
        r = m;
}
```

If `nums[m] == target`, I don't return.

I keep:

```cpp
r = m;
```

because `m` could be the **first occurrence**.

The search continues toward the left until the boundary is found.

### The Midpoint Trap

There is one important case where the normal midpoint is dangerous.

If my update can be:

```cpp
l = m;
```

then:

```cpp
m = l + (r - l) / 2;
```

can cause an infinite loop.

For example:

```text
l = 2
r = 3

m = 2
```

If I then do:

```cpp
l = m;
```

I get:

```text
l = 2
r = 3
```

Nothing changes.

The loop repeats forever.

So whenever I need:

```cpp
l = m;
```

I should use a **right-biased midpoint**:

```cpp
int m = l + (r - l + 1) / 2;
```

Now:

```text
l = 2
r = 3

m = 3
```

and:

```cpp
l = m;
```

actually makes progress.

My mental rule:

> **If I update `l = m`, use a right-biased midpoint. If I update `r = m`, the normal left-biased midpoint is usually appropriate.**

---

## 4. Rotated Sorted Array Navigation

Rotated-array problems require a different way of thinking because the entire array is no longer globally sorted.

For example:

```text
[4,5,6,7,0,1,2]
```

There are still two sorted portions, but the rotation breaks global ordering.

### Searching for a Target

At every step, I first determine:

> **Which half is sorted?**

I can check:

```cpp
if(nums[l] <= nums[m])
```

If true, the left half is sorted.

Then I ask:

> **Does my target lie inside the boundaries of this sorted half?**

For example:

```cpp
if(nums[l] <= target && target < nums[m])
```

If yes:

```cpp
r = m - 1;
```

Otherwise:

```cpp
l = m + 1;
```

If the left half is not sorted, then the right half must be sorted, and I perform the same reasoning on the right side.

The mental process is:

```text
1. Which half is sorted?
2. Is target inside that sorted half?
3. If yes → search there.
4. If no → search the other half.
```

My mental rule:

> **In a rotated sorted array, don't ask whether the whole array is sorted. Identify the sorted half first.**

---

### Finding the Minimum

For finding the minimum in a rotated sorted array, I can compare:

```cpp
nums[m]
```

against:

```cpp
nums[r]
```

If:

```cpp
nums[m] > nums[r]
```

then the minimum must be somewhere to the **right of `m`**:

```cpp
l = m + 1;
```

If:

```cpp
nums[m] <= nums[r]
```

then the right side is sorted, meaning the minimum could be at `m` itself or somewhere to the left:

```cpp
r = m;
```

Notice the important difference:

```cpp
r = m;
```

not:

```cpp
r = m - 1;
```

because `m` itself might be the minimum.

This naturally fits the 2-branch squeeze template.

---

## 5. Mathematical Micro-Optimizations

There are a few small mathematical patterns I should keep ready because they repeatedly appear in Binary Search problems.

### Flattening a 2D Matrix

If a matrix is sorted in a way that allows it to be treated as one continuous sorted array, I don't need separate row and column searches.

I can pretend the matrix is:

```text
1D array
```

and perform normal binary search.

If there are `cols` columns and my flattened index is:

```cpp
int mid;
```

I can convert it back to matrix coordinates using:

```cpp
int row = mid / cols;
int col = mid % cols;
```

For example:

```text
mid = 7
cols = 4

row = 7 / 4 = 1
col = 7 % 4 = 3
```

So:

```text
1D index 7
→ matrix[1][3]
```

My mental rule:

> **When a 2D structure has a sorted linear ordering, flatten it conceptually and map the 1D index back using division and modulo.**

---

### Ceiling Division

I should avoid unnecessary floating-point operations when I only need integer mathematics.

Instead of:

```cpp
ceil((double)a / b)
```

I can use:

```cpp
(a + b - 1) / b
```

for positive integers.

For example:

```text
a = 10
b = 3

(10 + 3 - 1) / 3
= 12 / 3
= 4
```

while:

```text
10 / 3 = 3
```

using integer division.

So:

```text
ceil(10 / 3) = 4
```

My mental rule:

> **For positive integers, remember `(a + b - 1) / b` for ceiling division.**

I should still check for potential integer overflow in `a + b - 1` if the values can approach the type's maximum.

---

### Zero-Division Safety

In Binary Search on Answer problems, my search range must contain only physically valid answers.

For example, in Koko Eating Bananas, the eating speed cannot be:

```text
0
```

because division by zero would occur when calculating the required hours.

Therefore, I should start with:

```cpp
int l = 1;
```

rather than:

```cpp
int l = 0;
```

The general rule is:

> **The binary-search range should contain only feasible answers. Don't include mathematically invalid values just because they simplify the bounds.**

---

## My Binary Search Decision Tree

When I encounter a Binary Search problem, I should first ask:

```text
Do I need an exact value?
        ↓
Classic 3-branch
while(l <= r)

Do I need the best valid answer?
        ↓
Record + Move
while(l <= r) + ans

Do I need a boundary?
        ↓
2-Branch Squeeze
while(l < r)

Is the array rotated?
        ↓
Identify the sorted half

Is the answer a numerical value?
        ↓
Binary Search on Answer
```

The main lesson I should take from Binary Search is:

> **The template should come from what I am searching for, not from memorizing one piece of code.**

Exact match, best valid answer, and boundary search are different problems even though all of them use the same fundamental divide-and-conquer idea.
