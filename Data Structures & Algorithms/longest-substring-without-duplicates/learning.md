# Optimized Sliding Window — My Interview Checklist

Here is how I would explain my optimized Sliding Window solution to an interviewer. The main improvements are the linear-time index tracking, fixed-size frequency storage, and safe C++ string handling.

## 1. Complexity — Strict `O(N)` Time

The main improvement is using an **index map** to track the most recent position of every character.

Instead of repeatedly shrinking a window using a `while` loop, I can directly jump the left boundary to the correct position.

For every character:

```cpp
last[s[i]]
```

tells me where that character was previously seen.

If I encounter a duplicate inside the current window, I can move the left boundary directly:

```cpp
left = max(left, last[c] + 1);
```

This means I don't need to repeatedly move `left` one position at a time.

The important distinction is that a traditional Sliding Window implementation might have:

```text
right pointer → moves N times
left pointer  → can also move N times
```

So it still has `O(N)` complexity, but the total number of pointer movements can approach `2N`.

With the index-map approach, I process every character once and directly calculate where the window should begin.

The overall complexity remains:

```text
Time: O(N)
```

The important interview point is:

> **The `while`-loop Sliding Window is already O(N) because both pointers move monotonically. The index-map version doesn't improve the Big-O complexity; it reduces pointer movements and gives a cleaner direct-jump implementation.**

So I should not claim that the `while`-loop approach is worse asymptotically. Both are linear.

---

## 2. Space Efficiency — Fixed-Size Array

Instead of using:

```cpp
unordered_map<char, int>
```

I use a fixed-size array:

```cpp
int last[256] = {0};
```

or:

```cpp
array<int, 256> last{};
```

The reason is that I know the character domain I am targeting.

There are only 256 possible byte values, so I don't need a dynamically sized hash table.

With an `unordered_map`, I would introduce:

```text
Hashing
Bucket management
Dynamic allocation
Potential cache-unfriendly memory access
```

A fixed array gives me direct indexing:

```cpp
last[c]
```

which is effectively constant-time and has very small constant factors.

The storage is always exactly 256 integers, regardless of the input length.

Therefore:

```text
Space: O(1)
```

because 256 is a fixed constant.

It is also more cache-friendly because the array is contiguous in memory.

My mental rule is:

> **If the key domain is small and fixed, prefer direct indexing with an array over a hash map.**

---

## 3. Safety — `const` Reference and `unsigned char`

I pass the string as:

```cpp
const string& s
```

instead of:

```cpp
string s
```

This prevents an unnecessary copy of the entire string.

If the string contains `N` characters, passing it by value can introduce:

```text
Time:  O(N)
Space: O(N)
```

copying overhead.

Since my algorithm only reads the string, I use:

```cpp
const string&
```

which gives me:

```text
const → prevents modification
&     → avoids copying
```

I also need to be careful when using characters as array indices.

A `char` in C++ may be signed depending on the implementation.

If the string contains a byte with a value greater than `127`, a signed `char` can become negative.

For example, conceptually:

```text
byte value = 200
signed char representation → negative value
```

If I then write:

```cpp
last[s[i]]
```

I could end up indexing the array with a negative value, causing undefined behavior.

So I can safely convert the character using:

```cpp
unsigned char c = static_cast<unsigned char>(s[i]);
```

and then:

```cpp
last[c]
```

Now the index is guaranteed to be in the range:

```text
0 ... 255
```

This is especially important when I am treating the string as arbitrary byte data rather than restricting it to lowercase English characters.

My mental rule is:

> **When using `char` as an array index for arbitrary byte values, convert it to `unsigned char` first.**

---

## My Interview Checklist

When I see an optimized Sliding Window problem, I should quickly ask myself:

1. **Can I directly jump the left boundary?**

Use the last-seen index of each character instead of repeatedly moving the left pointer.

2. **Is my key domain fixed?**

If I only need byte values:

```cpp
array<int, 256>
```

is preferable to a hash map.

3. **Am I copying the input string?**

Use:

```cpp
const string& s
```

when the string is read-only.

4. **Can `char` become a negative array index?**

For arbitrary byte values, use:

```cpp
static_cast<unsigned char>(s[i])
```

before indexing the 256-element array.

5. **What is my final complexity?**

```text
Time:  O(N)
Space: O(1)
```

The main lesson I should take from this problem is:

> **The biggest optimization is not merely choosing Sliding Window. It is recognizing what information the window actually needs.**

By storing the last position of each character, I can jump the left boundary directly. By recognizing that the character domain is fixed, I can replace a hash map with a contiguous array. Finally, by using `const` references and safe character indexing, I make the implementation more efficient and robust C++.
