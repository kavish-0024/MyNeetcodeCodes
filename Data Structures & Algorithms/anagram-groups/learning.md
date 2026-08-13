# Group Anagrams Optimization — My Interview Checklist

Here is the summary of the optimizations I applied to my `Group Anagrams` solution. I can use this as a mental checklist in interviews when dealing with sorting, hashing, move semantics, vector allocation, and cache efficiency.

## 1. Eradicating the Sorting Bottleneck — Time Complexity

**What I changed:**

```cpp
sort(key.begin(), key.end());
```

→

```cpp
Count the frequency of each character
        ↓
Build a unique frequency-based key
        ↓
Use that key in the hash map
```

The original approach generates a key by sorting every string.

If there are `N` strings and each string has an average length of `K`, sorting one string costs:

```text
O(K log K)
```

Therefore, sorting all the strings gives:

```text
O(N · K log K)
```

This works, but the sorting step is unnecessary because I don't actually care about the characters being sorted. I only need to know whether two strings contain the **same characters with the same frequencies**.

For example:

```text
"eat"
"tea"
"ate"
```

all have the same frequency distribution:

```text
a → 1
e → 1
t → 1
```

So instead of sorting:

```text
"eat" → "aet"
"tea" → "aet"
"ate" → "aet"
```

I can directly count the characters.

For lowercase English letters, I can use:

```cpp
array<int, 26> freq = {0};

for(char c : s)
{
    freq[c - 'a']++;
}
```

Then I can construct a unique key from the frequency array, for example:

```text
1#0#0#0#1#0#...#1#...
```

The exact representation is less important than the fact that two anagrams generate the same key.

Now, instead of sorting every string, I only scan its characters and its fixed-size frequency array.

The complexity becomes:

```text
O(N · K)
```

because counting the characters takes `O(K)` for each string, and processing the fixed 26-character frequency array is effectively constant time.

So I have removed the unnecessary:

```text
log K
```

factor from the sorting approach.

My mental rule is:

> **If I only need to compare character frequencies, don't sort the string just to generate a canonical form. Count the frequencies directly.**

---

## 2. Zero-Copy Memory Transfers — Move Semantics

**What I changed:**

```cpp
ans.push_back(it.second);
```

→

```cpp
ans.push_back(move(it.second));
```

**Why I changed it:**

Suppose my hash map contains:

```cpp
unordered_map<string, vector<string>> mp;
```

At the end, I want to move all the grouped anagrams from the hash map into my answer:

```cpp
vector<vector<string>> ans;
```

If I write:

```cpp
ans.push_back(it.second);
```

I am asking C++ to **copy** the vector stored inside the hash map.

If that vector contains many strings, copying it can be expensive because the vector has to create a new storage area and copy its elements.

Since I am about to finish processing the hash map and no longer need the original vector, keeping the original data intact is unnecessary.

Instead:

```cpp
ans.push_back(move(it.second));
```

uses **move semantics**.

`std::move()` does not literally move the memory by itself. It converts the expression into an rvalue, allowing the vector's move constructor to transfer ownership of its dynamically allocated storage instead of performing a deep element-by-element copy.

Conceptually:

```text
Copy:
Hash Map Vector
      ↓
Allocate new memory
      ↓
Copy every string
      ↓
Store in answer
```

Whereas with move semantics:

```text
Hash Map Vector
      ↓
Transfer ownership of underlying storage
      ↓
Answer now owns the storage
```

For a vector, this is typically an `O(1)` operation because the underlying buffer can be transferred rather than duplicated.

This becomes especially useful when the grouped vectors are large.

My mental rule is:

> **If I am done with an object and need to transfer its contents somewhere else, consider move semantics instead of copying.**

One important point I should remember in an interview is that `std::move()` itself does not magically make every operation `O(1)`. The destination type must have an appropriate move operation. For standard containers such as `vector`, moving is typically constant time.

---

## 3. Nullifying Vector Reallocation — Heap Management

**What I changed:**

I added:

```cpp
ans.reserve(mp.size());
```

before inserting the grouped vectors.

**Why I changed it:**

A `std::vector` manages a dynamically allocated array internally.

When I repeatedly perform:

```cpp
ans.push_back(...);
```

the vector may eventually run out of capacity.

When that happens, it needs to allocate a larger block of memory and move or copy its existing elements into the new storage.

Conceptually:

```text
Vector capacity = full
        ↓
Need another element
        ↓
Allocate larger memory block
        ↓
Move existing elements
        ↓
Release old storage
        ↓
Continue insertion
```

This does not make `push_back()` inefficient overall—the amortized complexity is still `O(1)`.

However, individual reallocations can be expensive and introduce unnecessary memory-management overhead.

In this problem, I already know the maximum number of groups:

```cpp
mp.size()
```

because each unique hash-map key corresponds to one anagram group.

Therefore, I can tell the vector how much space it needs:

```cpp
ans.reserve(mp.size());
```

Now the vector can allocate enough storage upfront.

The insertion process becomes more predictable:

```text
Reserve required capacity
        ↓
Insert groups
        ↓
No unnecessary capacity growth
        ↓
No repeated reallocation
```

The important distinction is:

> `reserve()` does not change the asymptotic complexity of vector insertion. `push_back()` is already amortized `O(1)`. It primarily reduces reallocations and improves practical performance.

So my mental rule is:

> **If I know approximately how many elements a vector will contain, reserve that capacity before repeatedly pushing elements.**

---

## 4. Maximizing Cache Efficiency — Fixed-Size Frequency Array

**What I changed:**

Instead of using a dynamically allocated structure for character frequencies, I use:

```cpp
array<int, 26> freq = {0};
```

**Why I changed it:**

The problem guarantees lowercase English letters.

That means I only need 26 counters:

```text
a → 0
b → 1
c → 2
...
z → 25
```

There is no need for a dynamically sized frequency structure.

Using:

```cpp
array<int, 26>
```

gives me a fixed-size contiguous block of memory.

This is useful because the array is small and contiguous, which makes it very cache-friendly. The CPU can access these frequency counters efficiently because they occupy a small, predictable region of memory.

It also avoids the need for a separate dynamic allocation for the frequency array.

The important point is not simply:

```text
Stack = fast
Heap = slow
```

because that is an oversimplification.

Modern memory performance depends heavily on allocation patterns, locality, cache behavior, and the allocator. The real advantage here is that `std::array<int, 26>` is a small fixed-size object with contiguous storage and no separate dynamic allocation for its elements.

So my mental rule is:

> **When the problem gives me a small fixed domain, use a fixed-size contiguous structure instead of a dynamically allocated data structure.**

---

## My Interview Checklist

When I see a `Group Anagrams` problem, I should quickly ask myself:

1. **Do I actually need sorting?**

If I only need to determine whether two strings have identical character frequencies, I can replace:

```cpp
sort(s.begin(), s.end());
```

with a frequency-based key.

2. **Can I use the input constraints?**

If the characters are guaranteed to be lowercase English letters:

```cpp
array<int, 26>
```

is a very efficient choice.

3. **Am I copying large containers unnecessarily?**

If I am transferring ownership and no longer need the source object:

```cpp
move(it.second)
```

can avoid an expensive deep copy.

4. **Do I know the size of my result?**

If I know the number of groups beforehand:

```cpp
ans.reserve(mp.size());
```

can eliminate unnecessary vector reallocations.

5. **What is the actual complexity?**

With sorting:

```text
O(N · K log K)
```

With frequency counting:

```text
O(N · K)
```

where:

* `N` = number of strings
* `K` = average length of a string

The space complexity depends on the number and total size of the groups, but the fixed frequency array itself uses:

```text
O(1)
```

additional space for the 26-character alphabet.

The main lesson I should take from this problem is:

> **Don't automatically use sorting just because I need a canonical representation. First ask whether the problem's constraints allow me to build that representation directly.**

Then, once the main algorithm is optimal, I should look at the implementation details: unnecessary copies, move semantics, memory allocation, vector capacity, and cache-friendly data structures.

That is how I turn a standard `Group Anagrams` solution into a more deliberate and efficient C++ implementation.
