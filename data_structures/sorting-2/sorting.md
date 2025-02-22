# [Sorting - 2](https://github.com/d-khan/dslabs/blob/main/intro/sorting-2.md)

## Task 1

> Proof that, under the average-case scenario, the insertion sort has a time
> complexity of $O(N^2)$. Draw a clear figure and show all the operations
> clearly.

Proving Insertion Sort's Average Case $O(n^2)$:

1. Basic Concept:
   - Insertion sort works by taking each element and comparing it to the value
     next to it, then swapping it with that value if it needs to. Where, when
     sorting a list into ascending order:
     - Compare the current element with the element to the left
     - If the element to the left is greater, swap the two values
     - Continue this compare and swap process until the element to the left is
       less than the current element
2. Operations:
   - Index 1: 2 operations (1 comparison + 1 swap)
     - Starting from the second element (index 1), since we assume the first
       element is already sorted
   - Index 2: 4 operations (2 comparisons + 2 swaps)
   - And so on, until the last element
   - For $n$ elements using index $i$, the total operations will be
     $\sum_{i=2}^n \frac {i(i-1)} 2$
3. Math:

   - On average, we can assume the element will be halfway to where it should be

     - Worst case: each element at position $i$ will need $i$ comparisons
       - A list that sorted in the reverse order, such as `[4,3,2,1]` to
         `[1,2,3,4]`
     - Average case: each element at position $i$ will need about $\frac i 2$
       comparisons
       - A list that is randomly ordered, such as `[3,1,4,2]` to `[1,2,3,4]`

   - Dividing the total operation summation by 2 (for average case) gives us
     $\frac{n(n-1)}{4}$
     - This simplifies to approximately $\frac{n^2}{4}$ operations

4. Big O:
   - While we calculated $\frac{n^2}{4}$ operations
   - In Big O notation, we drop constant factors
   - Therefore, the average case complexity is $O(n^2)$

**ASCII Art Figure**:

```txt
Initial Array: [5, 2, 4, 1, 3]

Pass 1: Compare element 2 with element 1
[5, 2, 4, 1, 3] -> [2, 5, 4, 1, 3]
 ^  ^
  Compare 2 with 5
  2 < 5
  Swap 5 and 2
  Leftmost element, done

Pass 2: Compare element 3 with previous elements
[2, 5, 4, 1, 3] -> [2, 4, 5, 1, 3]
    ^  ^
    Compare 4 with 5
    4 < 5
    Swap 5 and 4
    Compare 4 and 2
    4 > 2
    Do not swap, done

Pass 3: Compare element 4 with previous elements
[2, 4, 5, 1, 3] -> [2, 4, 1, 5, 3] -> [2, 1, 4, 5, 3] -> [1, 2, 4, 5, 3]
       ^  ^            ^  ^            ^  ^
    Multiple swaps to move 1 to correct position:
      Compare 1 with 5
      1 < 5
      Swap 5 and 1
      Compare 1 with 4
      1 < 4
      Swap 4 and 1
      Compare 1 with 2
      1 < 2
      Swap 2 and 1
      Leftmost element, done

Pass 4: Compare element 5 with previous elements
[1, 2, 4, 5, 3] -> [1, 2, 4, 3, 5] -> [1, 2, 3, 4, 5]
          ^  ^            ^  ^
    Compare 3 with 5
    3 < 5
    Swap 5 and 3
    Compare 3 with 4
    3 < 4
    Swap 3 and 4
    Compare 3 with 2
    3 > 2
    Do not swap, done

    Was last element (array is sorted), return

Final Sorted Array: [1, 2, 3, 4, 5]
```

## Task 2

> At the start of the insertion sort, the index of the inspected value is set
> to 1. Change the index of the inspected value and verify that the total number
> of operations equals 20. Consider the worst-case scenario. Use N=5, where N is
> the number of elements.

For N=5 with 20 operations (worst case):

- Index 0: 0 operations (0 comparison + 0 swap) - assume it is sorted
- Index 1: 2 operations (1 comparison + 1 swap)
- Index 2: 4 operations (2 comparisons + 2 swaps)
- Index 3: 6 operations (3 comparisons + 3 swaps)
- Index 4: 8 operations (4 comparisons + 4 swaps) Total: 0 + 2 + 4 + 6 + 8 = 20
  operations

We begin the insertion sort at index 1 rather than index 0 because the first
element (at index 0) is considered already sorted as it has no elements to its
left for comparison. This 'optimization' eliminates an unnecessary iteration
without affecting the algorithm's correctness.

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

For the `containsX` function:

a) Time Complexity: Current complexity is $O(n)$ where $n$ is the string length,
as it always checks every character.

b) Improved version:

```js
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
- Average case: $O(\frac n 2)$, if `X` is in the middle
- Worst case: $O(n)$, if `X` is at the end or not present

The main improvement is the early return when `X` is found, avoiding unnecessary
iterations through the rest of the string.
