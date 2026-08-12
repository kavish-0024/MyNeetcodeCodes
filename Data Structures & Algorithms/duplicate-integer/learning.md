## Modern Iteration

By using `auto it : nums`, you made the code safer by eliminating the possibility of going out of bounds and demonstrated an understanding of passing primitive types optimally by value.

## Algorithmic Efficiency

By switching to `st.insert(it).second`, you reduced the constant-time overhead of the loop. We no longer need to calculate the hash and traverse the bucket twice for each element.

## Memory Management

By adding:

```cpp
st.reserve(nums.size());
