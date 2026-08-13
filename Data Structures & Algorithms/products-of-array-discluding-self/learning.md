# Product of Array Except Self — My Interview Checklist

Here is the summary of the optimizations I applied to my `Product of Array Except Self` solution. I can use this as a mental checklist in interviews when dealing with prefix/suffix techniques, space optimization, C++ references, and indexing safety.

## 1. The Algorithm — Prefix & Suffix Products

The main idea was to solve the problem without using division by calculating the product of all elements **to the left** of each index and multiplying it by the product of all elements **to the right**.

For every index `i`:

```text
answer[i] = product of elements before i
            ×
            product of elements after i
```

For example:

```text
nums = [1, 2, 3, 4]
```

For index `2`:

```text
elements on the left  → 1 × 2 = 2
elements on the right → 4

answer[2] = 2 × 4 = 8
```

The important part is that I don't calculate these products repeatedly using nested loops.

Instead, I sweep through the array and maintain the running product.

The prefix pass allows me to build:

```text
product of everything to the left
```

and the suffix pass allows me to multiply by:

```text
product of everything to the right
```

This avoids the `O(N²)` brute-force approach.

The final time complexity becomes:

```text
Time: O(N)
```

because I only make a constant number of sequential passes through the array.

My mental rule is:

> **When every answer depends on everything before and after the current index, think about prefix/suffix techniques before considering nested loops.**

---

## 2. State Reduction — Bringing Auxiliary Space from `O(N)` to `O(1)`

Initially, I used an additional array to store the suffix products.

That approach works, but I realized that I don't actually need to remember the suffix product for every index.

While traversing the array from right to left, I only need the **current running suffix product**.

So instead of:

```cpp
vector<int> suffix(n);
```

I can maintain a single variable:

```cpp
int x = 1;
```

As I move from right to left, `x` represents the product of all elements currently to the right.

For example:

```text
nums = [1, 2, 3, 4]

Start:
x = 1

At 4:
x represents product to the right → 1
Update x → 4

At 3:
x represents product to the right → 4
Update x → 12

At 2:
x represents product to the right → 12
Update x → 24
```

The key observation is:

> **I only need the most recent suffix state, not the entire suffix array.**

So I collapsed:

```text
O(N) suffix storage
```

into:

```text
one integer
```

and reduced the auxiliary space to:

```text
O(1)
```

The output array `ans` itself does not count as auxiliary space because it is the required result of the problem.

This is an important distinction in interviews:

```text
Output space      → usually not counted
Auxiliary space   → extra memory used by the algorithm
```

So my final auxiliary-space complexity becomes:

```text
Space: O(1)
```

which is the optimal additional-space solution.

My mental rule is:

> **If I am storing a whole DP/prefix/suffix array, ask whether I actually need every previous state or only the most recent state.**

If only the previous state is required, I can often reduce `O(N)` space to `O(1)`.

---

## 3. C++ Memory & Safety — `const` Reference

I used:

```cpp
const vector<int>& nums
```

instead of:

```cpp
vector<int> nums
```

The reason is that I only need to read the input array.

Passing:

```cpp
vector<int> nums
```

by value can create a complete copy of the vector's elements.

For an array containing `N` elements, that unnecessary copy can introduce:

```text
Time:  O(N)
Space: O(N)
```

before my actual algorithm even starts.

By using:

```cpp
const vector<int>& nums
```

I access the original vector without copying its contents.

The `const` is also important because my algorithm should not modify the input.

So:

```text
const → I cannot accidentally modify nums
&     → I avoid copying the entire vector
```

This gives me a clean and efficient function interface.

My mental rule is:

> **If I only need to read a large container, pass it as `const &`.**

---

## 4. Dodging the `size_t` Trap

One subtle C++ issue I handled was the type returned by:

```cpp
nums.size()
```

`vector::size()` returns an unsigned type, typically `size_t`.

This can become dangerous when iterating backwards.

For example, consider:

```cpp
for(auto i = nums.size() - 1; i >= 0; i--)
```

This looks reasonable at first glance, but `i` becomes an unsigned integer because `nums.size()` is unsigned.

The problem appears when `i` reaches `0`.

The expression:

```text
0 - 1
```

does not become `-1` for an unsigned integer.

Instead, it wraps around to the maximum representable value for that unsigned type.

On a typical 64-bit system, that value is:

```text
18,446,744,073,709,551,615
```

So the condition:

```cpp
i >= 0
```

is effectively always true for an unsigned variable.

That can result in an incorrect/infinite loop and eventually an out-of-bounds access.

Instead, I explicitly store the size in a signed integer:

```cpp
int n = nums.size();
```

Now I can safely write a reverse loop such as:

```cpp
for(int i = n - 1; i >= 0; i--)
```

When `i` reaches:

```text
0
```

the next decrement gives:

```text
-1
```

and:

```cpp
i >= 0
```

becomes false.

So the loop terminates correctly.

The mental rule I should remember is:

> **Be careful when mixing unsigned values such as `size_t` with reverse loops.**

This is a classic C++ interview trap because the code can look perfectly correct while behaving incorrectly at the boundary.

---

## My Interview Checklist

When I see `Product of Array Except Self`, I should quickly ask myself:

1. **Can I avoid division?**
   Use prefix and suffix products.

2. **Am I using nested loops unnecessarily?**
   If every index can be processed using running products, I should target:

   ```text
   O(N)
   ```

3. **Do I really need a complete suffix/prefix array?**
   If I only need the previous state, replace the array with a single running variable.

4. **Am I accidentally copying the input?**
   Prefer:

   ```cpp
   const vector<int>& nums
   ```

   when the input is read-only.

5. **Am I iterating backwards using `nums.size()` directly?**
   Be careful with unsigned `size_t` and underflow.

6. **What is my final complexity?**

   ```text
   Time: O(N)
   Auxiliary Space: O(1)
   ```

The main lesson I should take from this problem is:

> **First find the right mathematical decomposition, then look for opportunities to compress the state.**

The prefix/suffix idea gives me the linear-time algorithm, while recognizing that I only need the current suffix product reduces the auxiliary space from `O(N)` to `O(1)`.

On top of that, being careful with `const` references and unsigned-index behavior makes the implementation safer and more efficient C++ rather than just a theoretically optimal algorithm.
