# Sliding Window Maximum — My Interview Checklist

## The Challenge

I have an array and a window of size `k` that moves from left to right.

At every position of the window, I need to find the **maximum element** inside that window.

For example:

```text id="z4p7km"
nums = [1, 3, -1, -3, 5, 3, 6, 7]
k = 3
```

The windows are:

```text id="y1c6qp"
[1, 3, -1] → 3
[3, -1, -3] → 3
[-1, -3, 5] → 5
[-3, 5, 3] → 5
[5, 3, 6] → 6
[3, 6, 7] → 7
```

So the answer is:

```text id="m8v3xa"
[3, 3, 5, 5, 6, 7]
```

The obvious approaches work, but they are not optimal. The key is to avoid recalculating the maximum from scratch every time the window moves.

---

## 1. The `O(N log N)` Solution — Priority Queue

My first approach can use a Max-Heap:

```cpp id="n6c4xz"
priority_queue<pair<int, int>> pq;
```

I store both:

```text id="e7r2kp"
value
index
```

The value allows me to identify the maximum, while the index allows me to determine whether that element is still inside the current window.

The heap gives me the maximum element at the top.

However, every insertion into the heap costs:

```text id="w3k8qn"
O(log N)
```

and removing elements also costs:

```text id="f2m6vp"
O(log N)
```

So processing the entire array gives approximately:

```text id="q7z1yc"
O(N log N)
```

This is a valid and reasonably efficient solution, but I can do better.

The problem has an important property:

> **The window only moves in one direction.**

That means I can exploit the order in which elements enter and leave the window instead of using a general-purpose heap.

---

## 2. The `O(N)` Optimal Solution — Monotonic Deque

The optimal approach uses:

```cpp id="a8r5dy"
deque<int> dq;
```

The deque stores **indices**, not values.

The important invariant is that the values corresponding to those indices are maintained in **decreasing order**:

```text id="x5c9nv"
nums[dq[0]] >= nums[dq[1]] >= nums[dq[2]] >= ...
```

So the largest candidate is always at the front.

For example, suppose the current candidates are:

```text id="z8m2fq"
[5, 3, 1]
```

The deque stores their indices in such a way that:

```text id="s3k7pw"
front → 5 → 3 → 1
```

Therefore:

```cpp id="b5q1nz"
nums[dq.front()]
```

is immediately the maximum.

The entire algorithm is based on maintaining this invariant.

There are three important rules.

---

## 3. Rule 1 — Remove Stale Data from the Front

When the window moves forward, some old elements eventually fall outside the window.

Suppose:

```text id="d7k2mc"
k = 3
```

and I am currently processing index `i`.

The current window contains indices:

```text id="a4v8pz"
[i - k + 1, i]
```

Therefore, any index smaller than:

```text id="w6n3rx"
i - k + 1
```

is no longer valid.

So before using the deque, I remove stale indices:

```cpp id="p9c4mz"
if(!dq.empty() && dq.front() <= i - k)
    dq.pop_front();
```

The exact boundary can also be expressed using:

```cpp id="z3q7hx"
dq.front() < i - k + 1
```

The important idea is simply:

> **If the index at the front has fallen outside the current window, remove it.**

This prevents an old maximum from incorrectly remaining the answer.

---

## 4. Rule 2 — Destroy Useless Candidates from the Back

This is the most important insight behind the Monotonic Deque.

Before inserting the current element `nums[i]`, I look at the back of the deque.

Suppose:

```text id="p2j8km"
deque values = [8, 5, 3]
```

and the new element is:

```text id="n6v4qa"
10
```

The `3` can never become the maximum again.

Why?

The new `10` is:

```text id="j7m3wc"
larger than 3
```

and:

```text id="q5x8rz"
newer than 3
```

The newer element will remain inside the sliding window for at least as long as the older element.

Therefore, there is absolutely no future window in which `3` can beat `10`.

So I remove it:

```cpp id="s4y9pk"
while(!dq.empty() && nums[dq.back()] <= nums[i])
    dq.pop_back();
```

I keep doing this until either:

```text id="n8c2mv"
deque is empty
```

or:

```text id="f7q5xa"
nums[dq.back()] > nums[i]
```

Then I insert the new index:

```cpp id="m3k8zr"
dq.push_back(i);
```

This is the key logic:

> **If a new element is both larger and newer than an existing candidate, that old candidate is permanently useless.**

That is why I can safely delete it.

---

## 5. Rule 3 — The Front Is the Champion

After applying the first two rules, the deque maintains two properties:

```text id="c5m8vx"
1. Every index is inside the current window.
2. Values are in decreasing order.
```

Therefore, the front of the deque must contain the maximum value.

So once the first complete window has been formed:

```cpp id="g8r2mq"
ans.push_back(nums[dq.front()]);
```

I don't need to search the window again.

The maximum is already known.

Conceptually:

```text id="y6p4kn"
Window
[1, 3, -1]

Deque:
3 → -1
↑
front = maximum
```

When the window moves, I simply update the deque according to the three rules.

---

## 6. Why the Complexity Becomes `O(N)`

At first glance, this code contains a `while` loop:

```cpp id="r4x8qn"
while(!dq.empty() && nums[dq.back()] <= nums[i])
    dq.pop_back();
```

It might look like this could make the algorithm `O(N²)`.

But it doesn't.

The important observation is that **every index enters the deque at most once and leaves the deque at most once**.

An element can be removed either:

```text id="p6w2cn"
from the front → stale
```

or:

```text id="q8m4vr"
from the back → dominated by a newer larger element
```

but once an index is removed, it never comes back.

Therefore, across the entire algorithm:

```text id="j3x7mz"
N insertions
+
at most N removals
```

So the total amount of deque work is linear:

```text id="f5k9qp"
O(N)
```

The final complexity is therefore:

```text id="v8r2cx"
Time:  O(N)
Space: O(K)
```

The deque can contain at most `K` indices at any point.

This is the important amortized-analysis insight:

> **A nested `while` loop does not automatically mean `O(N²)`. If every element can be inserted and removed only a constant number of times, the total work can still be `O(N)`.**

---

## My Interview Checklist

When I see `Sliding Window Maximum`, I should quickly ask myself:

1. **Am I using a heap?**

A priority queue gives approximately:

```text id="f3v8km"
O(N log N)
```

but I should ask whether the one-directional movement of the window allows something better.

2. **Can I use a Monotonic Deque?**

Store **indices**, not just values.

Maintain:

```text id="r8m2qw"
nums[dq[0]] >= nums[dq[1]] >= ...
```

3. **Is the front stale?**

Remove it if it has fallen outside the current window.

4. **Is the back useless?**

If:

```cpp id="k4q9xm"
nums[dq.back()] <= nums[i]
```

remove it because the new element is both newer and at least as large.

5. **Where is the maximum?**

Always:

```cpp id="x7p3zn"
nums[dq.front()]
```

because the deque is maintained in decreasing order.

6. **Why is it `O(N)` despite the `while` loop?**

Every index enters once and can leave once.

Therefore:

```text id="n5v8qc"
Time:  O(N)
Space: O(K)
```

The main lesson I should take from this problem is:

> **The Monotonic Deque works because I don't need to remember every element in the window—only the elements that still have a possibility of becoming the maximum.**

The smaller elements behind a newer, larger element are permanently useless, so I can safely delete them. Once I maintain that invariant, the front of the deque becomes the maximum automatically.

This is the general pattern I should remember for future problems:

> **When a sliding window asks for a maximum or minimum, think Monotonic Deque before reaching for a heap.**
