# Technical Growth Cheat Sheet — My Interview Prep

Here is my summary of the technical growth I made during this session. I can use this as a cheat sheet for my final interview preparation, especially for C++ optimization, amortized analysis, monotonic stacks, and understanding how data structures behave at the hardware level.

## 1. C++ Memory Mechanics & Compiler Optimizations

### Variable Elimination

I learned to actively look for variables that don't actually contribute to the final result.

For example, if I have an unused:

```cpp id="h7k2mv"
int n;
```

or an unnecessary intermediate:

```cpp id="x4p9qa"
vector<int> ans;
```

I should question whether I actually need it.

If I can reuse an existing variable or tighten the scope of a variable, I should do so.

The benefit is not just saving a few bytes of memory. The bigger benefit is reducing the amount of state I have to reason about.

My mental rule is:

> **Every variable should have a purpose. If I don't need it, remove it.**

This reduces cognitive load and can also reduce unnecessary memory usage.

---

### Primitive vs. Object Overhead

I also learned to pay attention to the type of comparison I am performing.

For example, if I have:

```cpp id="j3q8nx"
string ch;
```

and I only care about its first character, repeatedly comparing the entire `string` object is unnecessary.

Instead, I can extract:

```cpp id="r6m2vz"
char op = ch[0];
```

Now I am working with a simple primitive value.

For example:

```cpp id="f9c4kw"
if(op == '+')
```

is much simpler than repeatedly performing string-based comparisons such as:

```cpp id="y7m3px"
if(ch == "+")
```

The important idea is:

> **If the problem only requires a small part of an object, extract that information and operate on the simpler representation.**

This reduces unnecessary object-level work and makes the code clearer.

---

### The `switch` Advantage

Once I have reduced the operation to a primitive:

```cpp id="q8n4mc"
char op = ch[0];
```

I can use:

```cpp id="a5x7pz"
switch(op)
{
    case '+':
        ...
        break;

    case '-':
        ...
        break;

    case '*':
        ...
        break;

    case '/':
        ...
        break;
}
```

instead of a long chain of:

```cpp id="m2v9rx"
if(op == '+')
    ...
else if(op == '-')
    ...
else if(op == '*')
    ...
else if(op == '/')
    ...
```

A compiler may be able to optimize a suitable `switch` into a jump table or another efficient branch structure.

This can make dispatch very efficient, although I should not blindly claim that every `switch` is automatically `O(1)` at the hardware level. The compiler decides the actual implementation based on the case values and optimization opportunities.

The important interview takeaway is:

> **Use the language construct that clearly expresses the finite set of operations, and let the compiler optimize the dispatch.**

And one basic C++ rule I should never forget:

```cpp id="k7p3vz"
break;
```

Without `break`, execution can fall through into the next case.

---

## 2. Algorithmic Depth & Big-O Defense

### Amortized Analysis

One of the most important things I learned is how to defend an `O(N)` complexity even when the code contains a nested `while` loop.

A common pattern is:

```cpp id="b8x4qn"
for(int i = 0; i < n; i++)
{
    while(!stk.empty() && condition)
        stk.pop();

    stk.push(i);
}
```

At first glance, this looks like:

```text id="u4m8pz"
for loop
    ↓
while loop
```

and it is tempting to call it `O(N²)`.

But that would ignore the actual behavior of the stack.

Every index can:

```text id="n3q7mv"
be pushed once
```

and:

```text id="p6x2ka"
be popped at most once
```

across the **entire execution**.

So even though one particular iteration may pop many elements, those elements can never be popped again.

The total number of operations is therefore bounded by approximately:

```text id="w8c5zr"
N pushes + N pops
= 2N operations
```

which is:

```text id="g5v9qm"
O(N)
```

This is amortized analysis.

My mental rule is:

> **Don't judge complexity by indentation. Count how many times each element can actually be processed across the entire algorithm.**

A nested loop does not automatically mean `O(N²)`.

---

### Visualizing Worst-Case Space

I also learned to determine space complexity by looking at the **shape of the input**, not just its size.

For a right-to-left monotonic stack, consider a strictly increasing array:

```text id="x9m4qa"
[1, 2, 3, 4, 5, 6]
```

Depending on the stack condition, the elements may never be popped.

Therefore, as I process the array:

```text id="j8r2wc"
push 6
push 5
push 4
push 3
push 2
push 1
```

the stack can grow to contain all `N` elements.

Therefore:

```text id="p4v7mz"
Worst-case Space = O(N)
```

The important lesson is:

> **To determine worst-case space, construct the input that prevents the data structure from releasing anything.**

For a monotonic stack, the worst-case pattern is often a sorted or monotonic array.

---

### Temporal Distance Through Indices

Another important insight was why monotonic-stack problems usually store **indices instead of values**.

Suppose I need to know how far away a greater element is.

If I only store:

```cpp id="m7q3xz"
stk.push(nums[i]);
```

I know the value, but I lose the position where it occurred.

Instead, I store:

```cpp id="t5v8kp"
stk.push(i);
```

Now when I find the required element, I can calculate the distance directly:

```cpp id="q2n6wy"
stk.top() - i
```

For example:

```text id="v8m3qa"
current index = 2
previous index = 5
```

The distance can be calculated immediately from the indices.

This is especially useful in problems involving:

* Next Greater Element
* Daily Temperatures
* Stock Span
* Largest Rectangle in Histogram
* Distance between elements
* Sequence lengths

The mental rule is:

> **If the problem asks about distance, timing, position, or span, store indices rather than just values.**

The index contains both the value's location and allows me to retrieve the value using:

```cpp id="c4m8vz"
nums[index]
```

so I don't lose useful information by storing the index.

---

## 3. Hardware-Level Data Structures — Understanding `std::stack`

I also learned that `std::stack` is not actually a completely independent container implementation.

It is a **container adapter**.

By default, it typically uses:

```cpp id="k7v2mp"
std::deque
```

as its underlying container.

So when I write:

```cpp id="p9x4cz"
stack<int> stk;
```

I am effectively using a stack interface built on top of another container.

I can explicitly choose the underlying container:

```cpp id="w6m3qa"
stack<int, vector<int>> stk;
```

Now the stack uses `std::vector` internally.

---

### Why the Underlying Container Matters

A `std::deque` does not generally store its elements in one single contiguous memory block.

It uses multiple memory blocks.

A `std::vector`, on the other hand, stores its elements contiguously.

Conceptually:

```text id="n4q8px"
vector:

[ 1 ][ 2 ][ 3 ][ 4 ][ 5 ][ 6 ]
 ↑
contiguous memory
```

while a deque can be conceptually thought of as:

```text id="z5m7cv"
[1][2][3]     [4][5][6]     [7][8]
 block 1       block 2       block 3
```

This difference can matter for CPU cache behavior.

Modern CPUs work efficiently when data that is accessed together is located close together in memory.

This is called **spatial locality**.

With contiguous storage, when the CPU loads one cache line, it is likely to bring nearby elements into the cache as well.

Therefore, a vector-backed stack can have very good cache locality for workloads that repeatedly access nearby elements.

So:

```cpp id="f3x9kw"
stack<int, vector<int>> stk;
```

can be a useful implementation choice when I want stack semantics backed by contiguous storage.

My mental rule is:

> **The abstract data structure and the underlying storage structure are separate concepts. Always understand what container is actually storing the data.**

---

## My Interview Checklist

When writing optimized C++, I should ask myself:

1. **Do I have unnecessary variables?**

Remove variables that don't contribute to the result.

2. **Am I comparing complex objects when a primitive is enough?**

Extract the required information:

```cpp id="x4m7qp"
char op = ch[0];
```

3. **Can a `switch` express a small fixed set of operations more clearly?**

Use it when appropriate, and remember:

```cpp id="a9v2kc"
break;
```

4. **Does a nested `while` actually mean `O(N²)`?**

Count how many times each element enters and leaves the data structure.

If each element is pushed once and popped once:

```text id="r8n3mv"
O(N)
```

is often the correct amortized complexity.

5. **What input creates the maximum stack size?**

Construct the worst-case pattern instead of guessing.

6. **Do I need values or indices?**

If the problem involves distance or position:

```cpp id="h6q2wx"
stack<int> // store indices
```

is usually more useful.

7. **What is underneath my container?**

Remember:

```text id="p3x8qa"
std::stack
    ↓
container adapter
    ↓
std::deque by default
```

and I can explicitly use:

```cpp id="m7c4vz"
stack<int, vector<int>>
```

when contiguous storage is desirable.

The main lesson I should take from this session is:

> **I should not stop at knowing which algorithm works. I should understand why its complexity is what it is, what data is actually being stored, how memory is laid out, and how C++ translates my abstractions into real operations.**

That is the difference between simply solving a DSA problem and being able to **defend the solution in a technical interview**.
