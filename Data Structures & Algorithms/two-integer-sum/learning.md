# Two Sum Optimization — My Interview Checklist

Here is the summary of the optimizations I applied to my `Two Sum` solution. I can use this as a mental checklist in interviews when working with hash maps, memory allocation, and integer arithmetic.

## 1. Eliminating Redundant Lookups — The Iterator Advantage

**What I changed:**

```cpp
mp.count(need)
```

followed by:

```cpp
mp[need]
```

→

```cpp
auto x = mp.find(need);
```

**Why I changed it:**

A common implementation is:

```cpp
if(mp.count(need))
{
    return {mp[need], i};
}
```

The problem is that I am effectively asking the hash map about the same key twice.

First:

```cpp
mp.count(need)
```

checks whether `need` exists.

Then:

```cpp
mp[need]
```

looks up `need` again to retrieve its corresponding value.

Even though `unordered_map` provides average `O(1)` operations, `O(1)` does not mean zero cost. Hashing the key and traversing the appropriate bucket still requires actual CPU work.

Instead, I can perform one lookup:

```cpp
auto x = mp.find(need);
```

Now `x` is an iterator pointing directly to the matching element if it exists.

I can check:

```cpp
if(x != mp.end())
```

and retrieve the stored index using:

```cpp
x->second
```

So the flow becomes:

```text
find(need)
    ↓
Check whether iterator == mp.end()
    ↓
If found → directly access x->second
```

Instead of:

```text
count(need)
    ↓
Check existence
    ↓
mp[need]
    ↓
Search for the same key again
```

The important idea I should remember is:

> **If I need to check whether a key exists and also retrieve its value, `find()` is usually the cleaner and more efficient choice.**

---

## 2. Nullifying Unnecessary Rehashing — Pre-allocation with `reserve()`

**What I changed:**

I added:

```cpp
mp.reserve(nums.size());
```

**Why I changed it:**

`unordered_map` internally uses buckets to store its elements.

As I keep inserting elements, the hash table may eventually reach its load-factor threshold. At that point, it needs to increase the number of buckets and rehash the existing elements.

Conceptually, without reserving:

```text
Insert elements
      ↓
Buckets become insufficient
      ↓
Allocate a larger bucket array
      ↓
Rehash existing elements
      ↓
Move/reorganize entries
      ↓
Continue inserting
```

That rehashing operation can be expensive because many existing elements have to be processed again.

By writing:

```cpp
mp.reserve(nums.size());
```

I tell the `unordered_map` in advance that I expect to store approximately `nums.size()` elements.

This allows it to allocate enough buckets ahead of time and significantly reduces the possibility of repeated rehashing during the main loop.

The important distinction is that this does **not** change the theoretical average complexity from:

```text
O(n)
```

to something better.

The algorithm was already expected `O(n)`.

Instead, `reserve()` improves the **practical performance** by reducing unnecessary allocations and rehashing.

So my mental rule is:

> **If I know roughly how many elements I am going to insert into an `unordered_map`, consider calling `reserve()` beforehand.**

---

## 3. Bulletproofing Against Integer Overflow

**What I changed:**

```cpp
int need = target - nums[i];
```

→

```cpp
long long need = 1LL * target - nums[i];
```

**Why I changed it:**

This is an important defensive-programming detail.

A standard `int` in C++ is typically 32 bits and can represent values approximately in the range:

```text
-2.147 billion → +2.147 billion
```

Suppose:

```text
target = 2,000,000,000
nums[i] = -2,000,000,000
```

Mathematically:

```text
target - nums[i]
= 2,000,000,000 - (-2,000,000,000)
= 4,000,000,000
```

But `4,000,000,000` cannot be represented by a signed 32-bit `int`.

So if the subtraction is performed using `int` arithmetic, the result cannot represent the mathematical answer correctly.

To force the calculation into 64-bit arithmetic, I use:

```cpp
1LL * target
```

Now the expression:

```cpp
1LL * target - nums[i]
```

is evaluated using `long long` arithmetic.

Therefore:

```cpp
long long need = 1LL * target - nums[i];
```

protects the calculation from 32-bit overflow, assuming the mathematical result fits within `long long`.

The key thing I should remember is:

> **The type of the operands matters, not just the type of the variable receiving the result.**

For example, simply writing:

```cpp
long long need = target - nums[i];
```

does not necessarily protect the subtraction.

If both `target` and `nums[i]` are `int`, the subtraction can happen as `int` arithmetic first, and only then can the result be assigned to `long long`.

By writing:

```cpp
1LL * target
```

I promote the calculation to `long long` **before the subtraction happens**.

---

## My Interview Checklist

When I see a `Two Sum`-type problem using a hash map, I should quickly ask myself:

1. **Am I performing the same hash-map lookup twice?**

Instead of:

```cpp
mp.count(need);
mp[need];
```

consider:

```cpp
auto x = mp.find(need);
```

2. **Do I know how many elements I am going to insert?**

If yes, consider:

```cpp
mp.reserve(nums.size());
```

to reduce unnecessary rehashing.

3. **Can my arithmetic overflow?**

Instead of blindly writing:

```cpp
int need = target - nums[i];
```

consider:

```cpp
long long need = 1LL * target - nums[i];
```

when the constraints make overflow possible.

4. **What is the actual complexity?**

The overall approach remains:

```text
Time:  O(n) average
Space: O(n)
```

The optimizations do not magically change the Big-O complexity. They improve the implementation's constant factors, memory behavior, and robustness.

The main lesson I should take from this problem is:

> **Don't stop once the algorithm is theoretically optimal. Look at how many times I access the data structure, how memory is allocated, and whether my arithmetic is safe.**

For `Two Sum`, the hash-map approach already gives me an expected `O(n)` solution. These optimizations make that solution cleaner, more deliberate, and more robust for real-world constraints.
