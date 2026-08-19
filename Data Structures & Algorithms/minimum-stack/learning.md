# Min Stack — One Stack and `O(1)` Extra Space

## The Challenge

I need to design a stack that supports:

```text
push
pop
top
getMin
```

with **`O(1)` time** for every operation.

The additional constraint makes the problem more interesting: I am only allowed to use **one stack and one extra variable**.

Normally, I could maintain another stack containing the minimum value at every level, but that would require `O(N)` additional space.

The goal here is therefore:

```text
Time:  O(1) per operation
Space: O(1) extra space
```

The key idea is to use **mathematics to encode the previous minimum inside the existing stack**.

## The Core Idea

Whenever I push a value that is **not smaller** than the current minimum, I can simply push it normally.

But when I encounter a new minimum, I don't push the actual value.

Instead, I encode information about the **previous minimum** into a special "fake" value:

```cpp
2 * new_value - current_min
```

At the same time, I update:

```cpp
min_val = new_value;
```

So the stack itself secretly stores the history that I need to restore previous minimums later.

The important observation is that this encoded value will always be **smaller than the new minimum**.

That gives me a way to distinguish a normal stack value from an encoded value.

---

## 1. Encoding During `push`

Suppose:

```text
current minimum = 5
new value       = 3
```

Since `3 < 5`, this is a new minimum.

Instead of pushing `3`, I calculate:

```text
2 × 3 - 5
= 6 - 5
= 1
```

So I push:

```text
1
```

and update:

```text
min_val = 3
```

The stack now contains:

```text
[1]
```

while:

```text
min_val = 3
```

The important part is that:

```text
1 < 3
```

The value `1` is therefore a signal that the top element is not a real stack value. It is an encoded value containing information about the previous minimum.

My mental rule is:

> **When a new minimum appears, store a value that is guaranteed to be smaller than the new minimum. That gives me a built-in flag for detecting encoded values.**

---

## 2. Why the Encoding Works

The encoding formula is:

```text
encoded = 2 × new_min - old_min
```

Because:

```text
new_min < old_min
```

we have:

```text
new_min - old_min < 0
```

Therefore:

```text
2 × new_min - old_min < new_min
```

So the encoded value is guaranteed to be smaller than the current minimum.

That is exactly what allows me to detect it later.

For example:

```text
old_min = 10
new_min = 7

encoded = 2 × 7 - 10
        = 4
```

Now:

```text
encoded < new_min
4 < 7
```

So the value `4` cannot be an ordinary value at the top of the stack under the current minimum state.

It tells me:

> **The top element is an encoded value, so the previous minimum is hidden inside it.**

---

## 3. Detection During `top` and `pop`

Whenever I look at the top of the stack, I compare it with the current minimum.

The important condition is:

```cpp
stack.top() < min_val
```

If this is false, then the top is an ordinary value.

I can simply return:

```cpp
stack.top()
```

But if:

```cpp
stack.top() < min_val
```

then I know that the top is an encoded value.

The actual logical top value is not the encoded number.

It is the current:

```cpp
min_val
```

For example:

```text
stack.top() = 1
min_val     = 3
```

Since:

```text
1 < 3
```

I know that `1` is encoded.

The actual top element is:

```text
3
```

So `top()` returns `min_val`.

My mental rule is:

> **If the stack top is smaller than the current minimum, it is not a real value—it is an encoded marker.**

---

## 4. Decoding During `pop`

The most interesting part is restoring the previous minimum.

Suppose:

```text
old_min = 5
new_min = 3
```

During `push`, I stored:

```text
encoded = 2 × 3 - 5
        = 1
```

Now suppose I pop this encoded value.

At this point I know:

```text
encoded = 1
current minimum = 3
```

I need to recover:

```text
old_min = 5
```

Starting from:

```text
encoded = 2 × new_min - old_min
```

I rearrange the equation:

```text
old_min = 2 × new_min - encoded
```

Therefore:

```cpp
min_val = 2 * min_val - stack.top();
```

Using our example:

```text
old_min = 2 × 3 - 1
        = 5
```

So I can restore the previous minimum without storing it anywhere else.

This is the key trick that allows the entire minimum history to be encoded into the stack itself.

---

## 5. The Complete Mental Model

The entire mechanism can be remembered as:

```text
Normal value:
    push normally

New minimum:
    encoded = 2 * new_min - old_min
    push encoded
    min_val = new_min

During top():
    if stack.top() < min_val
        actual top = min_val
    else
        actual top = stack.top()

During pop():
    if stack.top() < min_val
        old_min = 2 * min_val - stack.top()
        min_val = old_min

    pop the stack
```

So I never need a second stack.

The stack contains both:

```text
normal values
+
encoded minimum-history markers
```

while the single variable:

```text
min_val
```

stores the current minimum.

---

## My Interview Checklist

When I see a `Min Stack` problem with the strict requirement of one stack and `O(1)` extra space, I should think:

1. **Can I maintain another minimum stack?**

Normally yes, but that costs `O(N)` extra space, so it doesn't satisfy the constraint.

2. **Can I encode the previous minimum?**

When:

```text
new_min < old_min
```

store:

```text
2 * new_min - old_min
```

instead of the actual value.

3. **How do I detect encoded values?**

If:

```text
stack.top() < min_val
```

then the top is encoded.

4. **How do I recover the actual top?**

If the top is encoded:

```text
top() = min_val
```

5. **How do I restore the previous minimum?**

Use:

```text
old_min = 2 * min_val - encoded
```

6. **What is the final complexity?**

```text
push:   O(1)
pop:    O(1)
top:    O(1)
getMin: O(1)

Extra Space: O(1)
```

The main lesson I should take from this problem is:

> **When an additional data structure is forbidden, look for information that can be encoded into the state I already have.**

Here, the stack itself becomes both the storage for the actual values and the storage for the minimum history. The algebraic encoding creates a detectable "flag" that tells me when a stack value is actually carrying hidden state.

One important C++ consideration is that the expression:

```cpp
2 * new_value - current_min
```

can overflow if the values are near the limits of the integer type. In a robust implementation, I should use a sufficiently wide integer type such as `long long` when the constraints require it.
