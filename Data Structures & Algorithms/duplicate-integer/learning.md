# C++ Code Optimization — Detailed Review

Let's quickly review the massive leap you just made from your original code to this **production-grade version**.

## 1. Modern Iteration

By using:

```cpp
for (auto it : nums)
```

you made the code significantly safer and cleaner.

Unlike a traditional index-based loop such as:

```cpp
for (int i = 0; i < nums.size(); i++)
```

the range-based loop directly iterates over the elements of `nums`. This eliminates the possibility of accidentally accessing an invalid index or making an off-by-one error.

It also demonstrates a proper understanding of modern C++ syntax and the use of `auto` for type deduction.

Since `nums` contains primitive values such as integers, using:

```cpp
auto it
```

means that each value is passed by value, which is appropriate and efficient for small primitive data types. There is no unnecessary reference or object copying overhead involved.

Overall, this makes the iteration:

* Safer
* Cleaner
* Easier to read
* Less error-prone
* More aligned with modern C++ practices

---

## 2. Algorithmic Efficiency

By switching to:

```cpp
st.insert(it).second
```

you improved the efficiency of the operation.

The important part here is the use of `.second`.

For an `unordered_set`, `insert()` returns a pair containing information about the insertion:

```cpp
pair<iterator, bool>
```

The `bool` value tells us whether the element was actually inserted.

Therefore:

```cpp
st.insert(it).second
```

directly tells us whether `it` was newly added to the set.

This is more efficient than first checking:

```cpp
if (st.find(it) == st.end()) {
    st.insert(it);
}
```

because the latter can potentially perform two hash-table operations:

1. `find()` calculates the hash and searches for the element.
2. `insert()` then calculates the hash and searches again before inserting.

With:

```cpp
st.insert(it).second
```

we combine the check and insertion into a single operation.

So instead of:

```text
find → hash → traverse bucket
insert → hash → traverse bucket → insert
```

we effectively perform:

```text
insert → hash → traverse bucket → insert if necessary
```

This reduces the constant-time overhead of the loop while maintaining the same expected overall complexity.

The average complexity of insertion into an `unordered_set` remains:

```text
O(1)
```

per element.

Therefore, processing all `n` elements remains:

```text
O(n)
```

on average.

---

## 3. Memory Management

The most important optimization here is:

```cpp
st.reserve(nums.size());
```

This demonstrates a deeper understanding of how `unordered_set` manages its internal memory.

An `unordered_set` internally maintains buckets for storing elements based on their hash values.

As more elements are inserted, the container may eventually need to increase its bucket count. When this happens, the existing elements need to be rehashed and redistributed into the new bucket structure.

Without reserving capacity beforehand, the set may repeatedly grow as elements are inserted:

```text
Insert elements
      ↓
Capacity becomes insufficient
      ↓
Allocate more buckets
      ↓
Rehash existing elements
      ↓
Continue insertion
      ↓
Repeat when necessary
```

These reallocations and rehashing operations introduce additional overhead.

By calling:

```cpp
st.reserve(nums.size());
```

before performing the insertions, we tell the container that we expect approximately `nums.size()` elements.

This allows the `unordered_set` to allocate an appropriate number of buckets in advance.

The process becomes closer to:

```text
Reserve required capacity
        ↓
Allocate buckets
        ↓
Insert elements
        ↓
Avoid unnecessary rehashing
```

This can significantly improve practical performance, especially when `nums` contains a large number of elements.

It also helps avoid sudden latency spikes caused by expensive rehashing operations during the main loop.

---

## 4. Overall Complexity

The optimized implementation still has an expected time complexity of:

```text
O(n)
```

because each element is inserted into the `unordered_set` with an average-case `O(1)` insertion cost.

The space complexity is:

```text
O(n)
```

because the `unordered_set` may store up to `n` unique elements.

The important improvement is not changing the theoretical Big-O complexity, but improving the **constant factors and practical runtime behavior**.

### Before

```text
Manual iteration
        ↓
Potential index-related errors
        ↓
find()
        ↓
insert()
        ↓
Possible repeated hashing/searching
        ↓
Possible rehashing
```

### After

```text
Range-based iteration
        ↓
auto it : nums
        ↓
st.insert(it).second
        ↓
Single insertion/search operation
        ↓
reserve(nums.size())
        ↓
Reduced rehashing overhead
```

So the final implementation remains **O(n) expected time and O(n) space**, but it is safer, cleaner, and more efficient in practical terms.

This is the kind of optimization that moves the code from simply being **correct** to being **well-engineered C++**.
