# `isAnagram` Optimization — My Interview Checklist

Here is the summary of the optimizations I applied to my `isAnagram` code. I can use this as a mental checklist in interviews, especially for problems involving strings, arrays, memory, and parameter passing.

## 1. Eradicating Hidden Deep Copies — Pass by `const` Reference

**What I changed:**

```cpp
string s, string t
```

→

```cpp
const string& s, const string& t
```

**Why I changed it:**

When I pass a `string` by value, the function may have to create a copy of the entire string. For a string of length `n`, this can cost `O(n)` time and `O(n)` additional space before my actual logic even starts.

By passing the strings using `const` reference:

```cpp
const string& s
```

I can access the original strings without creating unnecessary copies.

The `const` is important because I am only reading the strings. It guarantees that I cannot accidentally modify the original input.

So my mental rule is:

> If I only need to read a large object and don't need to modify it, consider passing it using `const &`.

This gives me both better performance and better safety.

---

## 2. True `O(1)` Memory — Using `array` Instead of `vector`

**What I changed:**

```cpp
vector<int> freq(26, 0);
```

→

```cpp
array<int, 26> freq = {0};
```

**Why I changed it:**

In this problem, I already know that the input contains only lowercase English letters. Therefore, I will always need exactly **26 frequency counters**.

There is no reason to use a dynamically sized container when the size is fixed.

`vector` is designed for dynamic sizing and its underlying storage is dynamically allocated. Since I know at compile time that I only need 26 integers, `std::array<int, 26>` is a more natural choice.

```cpp
array<int, 26> freq = {0};
```

gives me fixed-size storage without the need for dynamic resizing.

The important point is that both approaches are already `O(1)` space for this particular problem because `26` is a constant.

So this optimization does **not** change:

```text
O(1) → O(1)
```

Instead, it improves the implementation by avoiding unnecessary dynamic allocation and making my intention clearer:

> I know exactly how much storage I need, so I should use a fixed-size container.

---

## 3. Domain Constraints — Knowing When the Array Approach Breaks

My original logic:

```cpp
freq[s[i] - 'a']++;
```

is very efficient, but it depends completely on the problem constraint that the strings contain only lowercase English letters.

For example:

```text
'a' - 'a' = 0
'b' - 'a' = 1
'c' - 'a' = 2
...
'z' - 'a' = 25
```

So every character safely maps to an index from `0` to `25`.

But if the input contains an uppercase letter, special character, or Unicode character, this assumption is no longer valid.

For example, something like:

```cpp
freq[s[i] - 'a']
```

could produce an index outside the valid range of my 26-element array.

That can result in an out-of-bounds access and undefined behavior.

So before blindly optimizing, I need to check the **input constraints**.

If the interviewer says:

```text
Only lowercase English letters are allowed.
```

then I should confidently use:

```cpp
array<int, 26>
```

because it is simple and extremely efficient.

If the interviewer says the strings can contain arbitrary characters, I need a more general solution.

For example:

```cpp
unordered_map<char, int> freq;
```

Then I can directly use the character as the key:

```cpp
freq[s[i]]++;
freq[t[i]]--;
```

The tradeoff is that the fixed array gives me:

```text
Time:  O(n)
Space: O(1)
```

with very small constant factors.

The `unordered_map` approach still has expected `O(n)` time, but its space depends on the number of distinct characters. In the general case, that can become `O(n)`.

So my mental rule is:

> First understand the constraints. Then choose the most specialized data structure that safely handles them.

The important lesson I take from this problem is that optimization is always dependent on the problem's domain.

If the domain is fixed, I can exploit that constraint for better performance.

If the domain expands, I should sacrifice some efficiency for correctness and flexibility.

---

## My Interview Checklist

When I see a string-frequency problem, I should quickly ask myself:

1. **What is the character domain?**
   Lowercase English, ASCII, Unicode, or arbitrary characters?

2. **Am I unnecessarily copying the input?**
   If I only need to read a large object, consider:

   ```cpp
   const string&
   ```

3. **Is my required storage size fixed?**
   If it is fixed, consider:

   ```cpp
   array<int, 26>
   ```

4. **Does my optimization depend on a constraint?**
   If yes, explicitly verify that the constraint is guaranteed.

5. **What am I trading for the optimization?**
   A fixed array gives better constants and `O(1)` space, while a hash map provides more flexibility at the cost of additional memory and hashing overhead.

The main thing I should remember is:

> **Don't optimize blindly. First understand the constraints, then choose the data structure that best fits them.**

For this particular problem, the optimized approach gives me a clean `O(n)` solution with `O(1)` auxiliary space while avoiding unnecessary string copies and dynamic allocation.
