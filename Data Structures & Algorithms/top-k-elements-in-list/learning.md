# Top K Frequent Elements Optimization — My Interview Checklist

Here is the summary of the optimizations I applied to my `Top K Frequent Elements` solution. I can use this as a mental checklist in interviews when dealing with heaps, bucket sort, memory allocation, references, array bounds, and early termination.

## 1. The Algorithmic Leap — Min-Heap to Bucket Sort

**What I changed:**

I moved away from using a Min-Heap / `priority_queue` approach and switched to **Bucket Sort**.

The Min-Heap approach requires maintaining the heap property whenever elements are inserted or removed.

If there are `N` elements and I need the top `K` frequent elements, heap operations generally cost:

```text id="qj1x4n"
O(log K)
```

per relevant operation.

Therefore, the overall complexity becomes approximately:

```text id="i7j2qz"
O(N log K)
```

This is already a good solution, but I can do better because the problem gives me a very useful constraint.

The frequency of any number can never exceed the total number of elements:

```text id="e1g3d5"
Maximum frequency = N
```

That means the possible frequencies are bounded:

```text id="w6q8z1"
1, 2, 3, ..., N
```

So instead of using a heap to dynamically compare frequencies, I can create buckets where the **index represents the frequency**.

For example:

```cpp id="g4v9xm"
vector<vector<int>> freq(n + 1);
```

Here:

```text id="l7q2sa"
freq[1] → numbers appearing once
freq[2] → numbers appearing twice
freq[3] → numbers appearing three times
...
freq[n] → numbers appearing n times
```

Suppose:

```text id="x5k8rd"
nums = [1,1,1,2,2,3]
```

Then the frequency information becomes:

```text id="n5x0kw"
frequency 1 → [3]
frequency 2 → [2]
frequency 3 → [1]
```

Now I can simply iterate from the highest frequency toward the lowest:

```text id="3z0q8a"
N
↓
N-1
↓
N-2
↓
...
1
```

and collect elements until I have found `K` answers.

There is no heap.

There is no frequency comparison.

There is no `log K` factor.

The resulting complexity becomes:

```text id="b7c4yq"
O(N)
```

for the overall algorithm, assuming the usual hash-map frequency counting and bucket traversal.

This is effectively optimal because I must inspect the input at least once to determine the frequencies.

So my mental rule is:

> **When the value I am sorting or ranking is bounded by a small range, ask whether I can replace comparison-based sorting with Bucket Sort.**

This is an important pattern because comparison-based algorithms generally have a lower bound involving `log N`, while bounded integer ranges allow me to exploit the domain and achieve linear-time processing.

---

## 2. Guarding the Result Vector — Memory Allocation

**What I changed:**

```cpp id="5b0f6z"
vector<int> ans;
```

→

```cpp id="w8k2ap"
vector<int> ans;
ans.reserve(k);
```

**Why I changed it:**

I already know exactly how many elements I need in the answer:

```text id="q5p3b7"
K
```

So there is no reason to let the vector repeatedly grow while I insert elements.

A `std::vector` has two important properties:

```text id="7c4r2a"
size
capacity
```

When the vector reaches its capacity and I try to insert another element, it may need to allocate a larger block of memory and move its existing elements into the new location.

Conceptually:

```text id="w0h8ps"
Vector becomes full
        ↓
Allocate larger memory block
        ↓
Move existing elements
        ↓
Release old memory
        ↓
Continue insertion
```

This does not make normal `push_back()` operations inefficient—the amortized complexity remains `O(1)`.

However, individual reallocations can still introduce unnecessary memory-management overhead.

Since I know that the final answer contains exactly `K` elements, I can simply write:

```cpp id="f4x9dz"
ans.reserve(k);
```

Now the vector allocates enough capacity upfront.

The insertion process becomes more predictable:

```text id="k7m1wq"
Reserve K slots
      ↓
Insert answers
      ↓
No capacity growth
      ↓
No unnecessary reallocations
```

My mental rule is:

> **If I know how many elements a vector will eventually contain, reserve that capacity before repeatedly pushing elements.**

Again, I should be precise in an interview: `reserve()` does not change the asymptotic complexity of `push_back()` from something worse to `O(1)`. `push_back()` is already amortized `O(1)`. The optimization primarily eliminates reallocations and improves practical performance.

---

## 3. C++ Reference Safety — Avoiding Deep Copies

**What I changed:**

```cpp id="8c6d2v"
const vector<int>& nums
```

instead of:

```cpp id="7r1x5c"
vector<int> nums
```

**Why I changed it:**

Passing:

```cpp id="b7p3mz"
vector<int> nums
```

by value means the function receives its own copy of the vector's contents.

If the input contains `N` elements, creating that copy can cost:

```text id="s4v9hx"
Time:  O(N)
Space: O(N)
```

This is unnecessary because my algorithm only needs to read the input.

Instead, I can pass the vector by reference:

```cpp id="f2r8yc"
const vector<int>& nums
```

The reference avoids copying the entire vector.

The `const` is also important.

It tells the compiler that my function is not supposed to modify the original vector.

So I get two benefits:

```text id="1z8r6n"
const → prevents accidental modification
&    → avoids copying the entire vector
```

The function can directly access the original vector without creating another copy.

My mental rule is:

> **If I only need to read a potentially large object, pass it as `const &`.**

This is especially important in C++ interviews because parameter passing can introduce hidden `O(N)` work even when the algorithm itself is theoretically optimal.

---

## 4. Preventing Segmentation Faults — Off-by-One in Bucket Allocation

**What I changed:**

```cpp id="6v8j2m"
vector<vector<int>> freq(n + 1);
```

instead of:

```cpp id="0m5w9q"
vector<vector<int>> freq(n);
```

**Why I changed it:**

This is a classic off-by-one issue.

C++ uses zero-based indexing.

If I create:

```cpp id="5c1z8p"
vector<vector<int>> freq(n);
```

the valid indices are:

```text id="n3q7ka"
0 → n-1
```

But the maximum possible frequency of an element is exactly:

```text id="h8v2cs"
n
```

This happens when every element in the array is identical.

For example:

```text id="z2d6pq"
nums = [5,5,5,5,5]
```

Here:

```text id="p3s7jx"
frequency of 5 = 5
```

So I need to access:

```cpp id="x9m4qa"
freq[5]
```

If I only allocated:

```cpp id="w5k1hz"
vector<vector<int>> freq(5);
```

the valid indices would only be:

```text id="m8c2vy"
0, 1, 2, 3, 4
```

and accessing:

```cpp id="3q6j1k"
freq[5]
```

would be out of bounds.

Therefore, I allocate:

```cpp id="7k4n9x"
vector<vector<int>> freq(n + 1);
```

Now the valid indices are:

```text id="x1b8mv"
0, 1, 2, ..., n
```

which safely includes the maximum possible frequency.

This is a simple but important constraint-based decision:

> **If my valid value range is `0...N`, my container needs at least `N+1` positions.**

---

## 5. CPU Cycle Sniping — Early Termination

**What I changed:**

I added an immediate:

```cpp id="m5v7xc"
return ans;
```

when `k` becomes zero.

The reason is that once I have collected exactly `K` elements, the problem is already solved.

Suppose I have:

```text id="a8f3wd"
k = 3
```

and while traversing the buckets I collect:

```text id="p9z4xq"
1st element → k = 2
2nd element → k = 1
3rd element → k = 0
```

At this point, there is absolutely no reason to continue traversing the remaining buckets.

A naive implementation might continue:

```text id="q3m7vx"
frequency bucket
      ↓
more elements
      ↓
more buckets
      ↓
more iterations
      ↓
eventually finish
```

Even though the answer has already been found.

Instead, I can immediately terminate:

```cpp id="f8x2mv"
if(k == 0)
    return ans;
```

This prevents unnecessary work.

The benefit becomes more noticeable when the input is large and the remaining buckets contain many elements.

My mental rule is:

> **Whenever the problem has a clear stopping condition, terminate immediately once that condition is satisfied.**

This does not change the worst-case Big-O complexity, because in the worst case I may still need to traverse almost everything.

But it improves the **best-case and practical runtime** by avoiding work that no longer contributes to the answer.

---

## My Interview Checklist

When I see a `Top K Frequent Elements` problem, I should quickly ask myself:

1. **Can I replace a heap with Bucket Sort?**

If the frequency is bounded by `N`, I can use:

```cpp id="u3j8pk"
vector<vector<int>> freq(n + 1);
```

and achieve an expected `O(N)` approach.

2. **Do I know how many results I need?**

If the answer always contains `K` elements:

```cpp id="w5r2nb"
ans.reserve(k);
```

can avoid unnecessary reallocations.

3. **Am I copying the input unnecessarily?**

Prefer:

```cpp id="v9c4sx"
const vector<int>& nums
```

when I only need to read the array.

4. **Have I handled the maximum possible frequency?**

Since an element can appear `N` times:

```cpp id="g6t2mx"
vector<vector<int>> freq(n + 1);
```

is required.

5. **Can I stop early?**

Once:

```cpp id="j3p8qw"
k == 0
```

I already have the answer, so I should return immediately.

6. **What is my final complexity?**

With frequency counting and Bucket Sort:

```text id="e5y7nc"
Time:  O(N) expected
Space: O(N)
```

The hash map used for counting contributes expected `O(N)` time, and the bucket structure requires `O(N)` space.

The main lesson I should take from this problem is:

> **When the problem gives me a bounded range, I should exploit it instead of automatically reaching for a heap or sorting algorithm.**

Then I should look beyond the Big-O notation and optimize the implementation itself: avoid unnecessary copies, reserve known capacities, allocate enough space for boundary cases, and terminate immediately when the answer is complete.

That combination gives me not just a theoretically efficient solution, but a solution that is deliberate about **algorithmic complexity, memory behavior, C++ semantics, and practical CPU work**.
