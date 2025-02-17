# [Sorting - 1](https://github.com/d-khan/dslabs/blob/main/intro/sorting-1.md)

## Task 1

For $4N + 16$ steps:

- This is a linear function with a constant
- We drop constants and coefficients in Big O notation
- Therefore, this is $O(N)$

## Task 2

For $2N^2$:

- This is a quadratic function with a coefficient
- We drop the coefficient in Big O notation
- Therefore, this is $O(N^2)$

## Task 3

For the `double_then_sum(array)` function:

- First loop: Iterates through array once to double numbers: $O(N)$
- Second loop: Iterates through doubled_array once to sum: $O(N)$
- When we have sequential operations, we add them: $O(N) + O(N)$
- Simplifies to: $O(N)$

## Task 4

For the multiple_cases function:

- Single loop through the array: $O(N)$
- For each iteration, performs 3 constant time operations (upcase, downcase,
  capitalize)
- Constants don't affect Big O notation
- Therefore, this is $O(N)$

## Task 5

For the every_other function:

- Outer loop iterates through entire array: $O(N)$
- For each even index (approximately $N \div 2$ times):
  - Inner loop iterates through entire array: $O(N)$
- When loops are nested, we multiply: $O(N) \times O(N/2)$
- Simplifies to: $O(N^2)$

## Summary

- We always drop constants and coefficients
- Sequential operations are added
- Nested operations are multiplied
- We use the highest order term only
