# [Sorting - 2](https://github.com/d-khan/dslabs/blob/main/intro/sorting-2.md)

## Task 1

> Proof that, under the average-case scenario, the insertion sort has a time
> complexity of $O(N^2)$. Draw a clear figure and show all the operations
> clearly.

The average case for insertion sort requires approximately $N^2 \div 4$
comparisons and $N^2 \div 4$ shifts.
Proving Insertion Sort's Average Case $O(n^2)$:


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

> At the start of the insertion sort, the index of the inspected value is set
> to 1. Change the index of the inspected value and verify that the total number
> of operations equals 20. Consider the worst-case scenario. Use N=5, where N is
> the number of elements.

When using insertion sort with N=5, the index should start at 2 (not 1) to get
exactly 20 operations in worst case. Let's count:
For N=5 with 20 operations (worst case):

- Index 2: 2 operations
- Index 3: 6 operations
- Index 4: 12 operations
- Total: 2 + 6 + 12 = 20 operations

## Task 3

> The following function returns whether or not a capital “X” is present within
> a string:
>
> ```js
> function containsX(string) {
>   foundX = false;
>   for (let i = 0; i < string.length; i++) {
>     if (string[i] === "X") {
>       foundX = true;
>     }
>   }
>   return foundX;
> }
> ```
>
> (a) What is this function’s time complexity regarding Big O Notation?
>
> (b) Then, modify the code to improve the algorithm’s efficiency for best- and
> average-case scenarios.

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
