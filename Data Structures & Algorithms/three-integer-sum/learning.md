# 3Sum — My Interview Checklist

Here is the summary of the algorithmic and C++ implementation decisions I used for my `3Sum` solution. I can use this as a mental checklist whenever I encounter problems involving triplets, sorting, two pointers, duplicate handling, and nested containers.

## 1. The Algorithmic Architecture — `O(N³)` to `O(N²)`

The brute-force solution for `3Sum` is straightforward:

```cpp
for(int i = 0; i < n; i++)
    for(int j = i + 1; j < n; j++)
        for(int k = j + 1; k < n; k++)
```

This checks every possible triplet, giving:

```text
Time: O(N³)
```

That becomes expensive very quickly.

The major improvement comes from **sorting the array first**:

```cpp
sort(nums.begin(), nums.end());
```

Sorting costs:

```text
O(N log N)
```

but it gives me something much more valuable: **ordered data**.

Once the array is sorted, I can fix one number and solve the remaining problem using Two Pointers.

For every `i`:

```cpp
int j = i + 1;
int k = n - 1;
```

Now I check:

```cpp
nums[i] + nums[j] + nums[k]
```

If the sum is too small:

```cpp
j++;
```

because moving `j` to the right gives me a larger value.

If the sum is too large:

```cpp
k--;
```

because moving `k` to the left gives me a smaller value.

If:

```cpp
nums[i] + nums[j] + nums[k] == 0
```

I have found a valid triplet.

So instead of searching:

```text
i
 ↓
 j
  ↓
  k
```

with three nested loops, I now have:

```text
Fix i
  ↓
j → → → ← ← ← k
```

For every fixed `i`, the two pointers together traverse the remaining array in `O(N)` time.

Since `i` itself runs `O(N)` times:

```text
O(N) × O(N) = O(N²)
```

The initial sorting contributes:

```text
O(N log N)
```

so the total is:

```text
O(N log N + N²)
```

which simplifies to:

```text
O(N²)
```

My mental rule is:

> **When I need combinations involving two or three values and ordering can help me decide which direction to search, sorting + Two Pointers should immediately come to mind.**

---

## 2. Zero-Memory Duplicate Handling

One of the hardest parts of `3Sum` is not finding triplets—it is making sure I don't return the same triplet multiple times.

A simple solution could store every answer inside:

```cpp
set<vector<int>>
```

The set would automatically remove duplicates.

But that introduces additional memory and logarithmic insertion overhead.

Since my array is already sorted, identical values are adjacent.

That means I can eliminate duplicates directly.

For the fixed element `i`:

```cpp
if(i > 0 && nums[i] == nums[i - 1])
    continue;
```

Suppose:

```text
nums = [-4, -1, -1, 0, 1, 2]
```

After processing the first `-1`, I don't need to start another search from the second `-1`.

They would generate the same candidate space.

Similarly, after finding a valid triplet, I move both pointers:

```cpp
j++;
k--;
```

and skip repeated values.

For example:

```cpp
while(j < k && nums[j] == nums[j - 1])
    j++;

while(j < k && nums[k] == nums[k + 1])
    k--;
```

This gives me duplicate-free answers without requiring another data structure.

Conceptually:

```text
Sorted array
     ↓
Equal values become adjacent
     ↓
Skip repeated i
     ↓
Skip repeated j
     ↓
Skip repeated k
     ↓
No duplicate triplets
```

So excluding the output container, the two-pointer scanning itself requires only a few integer variables:

```text
i, j, k
```

giving:

```text
Auxiliary scanning space: O(1)
```

One nuance I should remember: `std::sort` itself may use `O(log N)` stack space depending on the implementation, so saying the entire implementation is *strictly* `O(1)` auxiliary space can be imprecise. In interviews, I can say the **two-pointer algorithm uses `O(1)` extra data-structure space**, excluding the output.

My mental rule is:

> **If sorting places duplicates next to each other, try skipping them directly instead of introducing a `set`.**

---

## 3. C++ Memory Mechanics — Adding the Triplet

Once I find:

```cpp
nums[i] + nums[j] + nums[k] == 0
```

I need to insert:

```text
[nums[i], nums[j], nums[k]]
```

into:

```cpp
vector<vector<int>> ans;
```

There are several ways I could do this.

### Level 1 — Named Vector + Copy

I could write:

```cpp
vector<int> x{nums[i], nums[j], nums[k]};
ans.push_back(x);
```

First I create:

```cpp
x
```

and then `push_back(x)` receives an lvalue, so it copies `x` into the new element of `ans`.

Conceptually:

```text
Create x
   ↓
Allocate x's internal storage
   ↓
push_back(x)
   ↓
Copy x into ans
   ↓
Destroy x
```

This works correctly, but the named temporary vector is unnecessary.

My mental rule is:

> **Don't create a separate container merely to immediately copy it into another container.**

---

### Level 2 — Named Vector + `std::move`

I can improve the previous version using:

```cpp
vector<int> x{nums[i], nums[j], nums[k]};
ans.push_back(std::move(x));
```

Now `push_back` can invoke the vector's move constructor instead of its copy constructor.

The destination vector can typically take ownership of `x`'s dynamically allocated storage instead of copying the elements individually.

Conceptually:

```text
Create x
   ↓
Allocate x's storage
   ↓
std::move(x)
   ↓
Transfer ownership into ans
   ↓
x becomes valid but unspecified
   ↓
Destroy x
```

This removes the expensive copy, but I am still creating a named `x` that serves no purpose after insertion.

So it is better than Level 1, but unnecessary for this particular situation.

My mental rule is:

> **Use `std::move` when I already have an object whose resources I no longer need. Don't create an unnecessary named object just so I can move it.**

---

### Level 3 — Direct Construction

For this problem, the cleanest version is simply:

```cpp
ans.push_back({nums[i], nums[j], nums[k]});
```

I directly provide the initializer list needed to construct the `vector<int>` that will be inserted into `ans`.

There is no need for:

```cpp
vector<int> x;
```

in my source code.

This is concise, readable, and avoids the explicit copy from a named lvalue.

So instead of:

```cpp
vector<int> x{nums[i], nums[j], nums[k]};
ans.push_back(x);
```

I prefer:

```cpp
ans.push_back({nums[i], nums[j], nums[k]});
```

For `vector<vector<int>>`, this is the natural syntax for inserting a small triplet.

---

## `push_back` vs `emplace_back` — Important Interview Detail

I should not blindly assume that:

```cpp
emplace_back(...)
```

is always faster than:

```cpp
push_back(...)
```

For custom objects, `emplace_back` is particularly useful because it forwards constructor arguments directly to the object's constructor.

For example:

```cpp
struct Person
{
    string name;
    int age;

    Person(string n, int a)
        : name(std::move(n)), age(a) {}
};
```

Then:

```cpp
people.emplace_back("Kavish", 20);
```

constructs the `Person` directly as an element of the vector.

But my `3Sum` answer is:

```cpp
vector<vector<int>>
```

and I want to insert a `vector<int>` initialized from three integers.

The clearest solution is:

```cpp
ans.push_back({nums[i], nums[j], nums[k]});
```

rather than trying to force:

```cpp
ans.emplace_back(nums[i], nums[j], nums[k]);
```

because `vector<int>` does not have a constructor meaning "create a vector containing these three integer values."

So my actual mental rule should be:

> **Prefer direct construction, but understand the constructor of the object being inserted. `emplace_back` is not automatically superior to `push_back`.**

---

## My Interview Checklist

When I see `3Sum`, I should quickly ask myself:

1. **Can sorting unlock Two Pointers?**

```cpp
sort(nums.begin(), nums.end());
```

allows me to intelligently move `j` and `k`.

2. **Can I eliminate one nested loop?**

Fix:

```cpp
i
```

and solve the remaining `2Sum` problem using:

```cpp
j = i + 1;
k = n - 1;
```

This takes me from:

```text
O(N³)
```

to:

```text
O(N²)
```

3. **Am I using a `set` just to remove duplicate answers?**

Because the array is sorted, I can directly skip duplicate values for:

```text
i, j and k
```

instead.

4. **Am I creating an unnecessary temporary vector?**

Instead of:

```cpp
vector<int> x{nums[i], nums[j], nums[k]};
ans.push_back(x);
```

prefer:

```cpp
ans.push_back({nums[i], nums[j], nums[k]});
```

5. **Should I automatically replace `push_back` with `emplace_back`?**

No.

I should understand what object I am constructing and what constructors are available.

6. **What is my final complexity?**

```text
Sorting:             O(N log N)
Two-Pointer Search:  O(N²)

Overall Time:        O(N²)
```

The two-pointer logic uses:

```text
O(1)
```

additional data-structure space, excluding the returned triplets, with the caveat that the sorting implementation may use additional call-stack space.

The main lesson I should take from this problem is:

> **Sorting isn't always an expensive step that I should avoid. Sometimes paying `O(N log N)` upfront creates structure that allows me to eliminate an entire nested loop.**

For `3Sum`, sorting gives me both major benefits at once: **Two Pointers for `O(N²)` searching and adjacent duplicates for zero-extra-container deduplication.**
