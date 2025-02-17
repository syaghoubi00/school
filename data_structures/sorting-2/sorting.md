# [Sorting - 2](https://github.com/d-khan/dslabs/blob/main/intro/sorting-2.md)

## Task 1

Proving Insertion Sort's Average Case $O(N^2)$:

The average case for insertion sort requires approximately $N^2 \div 4$
comparisons and $N^2 \div 4$ shifts.

- On average, each element needs to be compared with about half of the already
  sorted elements
- For `N` elements:
  - First element: 0 comparisons
  - Second element: ~1/2 comparisons
  - Third element: ~2/2 comparisons ...and so on
- This forms an arithmetic series: $(0 + 1 + 2 + ... + (n-1)) \div 2$
- Which simplifies to: $n(n-1) \div 4 \approx N^2 \div 4$. Therefore, the
  average case is $O(N^2)$

## Task 2

For N=5 with 20 operations (worst case):

When using insertion sort with N=5, the index should start at 2 (not 1) to get
exactly 20 operations in worst case. Let's count:

- Index 2: 2 operations
- Index 3: 6 operations
- Index 4: 12 operations
- Total: 2 + 6 + 12 = 20 operations

## Task 3

For the `containsX(string)` function:

a) Time Complexity: Current complexity is $O(n)$ where `n` is the string length,
as it always checks every character.

b) Improved version:

```cpp
function containsX(string) {
  for (let i = 0; i < string.length; i++) {
    if (string[i] === "X") {
      return true; // Early return when X is found
    }
  }
  return false;
}
```

This improved version:

- Best case: $O(1)$, if `X` is at the beginning
- Average case: $O(n \div 2)$, still $O(n)$ but practically faster
- Worst case: $O(n)$, if `X` is at the end or not present

The main improvement is the early return when `X` is found, avoiding unnecessary
iterations through the rest of the string.
