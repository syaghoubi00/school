# [Search](https://github.com/d-khan/dslabs/blob/main/intro/search.md)

## Task 1

> How many steps would it take to perform a linear search for the number 8 in
> the ordered array, `[2, 4, 6, 8, 10, 12, 13]`?

**Answer**: 4 steps.

**Explanation**:

In a linear search, we check each element sequentially from the beginning until
we find our target value (8).

The steps would be:

1. Check 2 (not 8)
2. Check 4 (not 8)
3. Check 6 (not 8)
4. Check 8 (found!)

Therefore, it takes 4 steps to find 8 in the ordered array.

The worst-case scenario for linear search is when the target value is at the
end, or isn't present, which requires checking all the elements of the dataset.
This means linear search has a time complexity of O(n) where n is the number of
elements. Linear search does not require the data to be sorted, as it
sequentially checks the data until the target is found.

## Task 2

> How many steps would binary search take for the previous example?

**Answer**: 1 step.

**Explanation:**

In binary search, we:

1. Start by checking the middle element of the sorted array
   `[2, 4, 6, 8, 10, 12, 13]`
   - Middle position = 7/2 = 3 (rounded down)
   - Middle element is 8

Since 8 is exactly what we're looking for and it happens to be at the middle
position, we find it in 1 step. This is the best-case scenario for binary
search.

## Task 3

> What is the maximum number of steps it would take to perform a binary search
> on an array of size 100,000?

**Answer**: 17 steps.

**Explanation:**

For a sorted array of size 100,000, we can calculate the maximum number of steps
in binary search using the formula: log<sub>2</sub>(n) where n = 100,000

- Binary search divides the search space in half at each step
- We need to find how many times we need to divide 100,000 by 2 to get to 1
- Mathematically, this is expressed as log<sub>2</sub>(100,000)
- log<sub>2</sub>(100,000) = 16.61
- Since we need a whole number of steps, we round up to 17

This means in the worst case, it would take at most 17 steps to find (or
determine the absence of) any element in a sorted array of 100,000 items.
