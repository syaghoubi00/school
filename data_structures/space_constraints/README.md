# [Space Constraints](https://github.com/d-khan/dslabs/blob/8214da88d1009266cf3a6d4fc51cf19eac19160a/space-constraints/Activity.md)

## Task 1

> Following is the 'Word Builder' algorithm. Describe its space complexity in
> terms of Big O.
>
> ```
> function wordBuilder(array) {
>     let collection = [];
>     for(let i = 0; i < array.length; i++) {
>         for(let j = 0; j < array.length; j++) {
>             if (i !== j) {
>                 collection.push(array[i] + array[j]);
>             }
>         }
>     }
>     return collection;
> }
> ```

The space complexity of the `wordBuilder` function is $O(n^2)$, where $n$ is the
length of the input array. This is because the function creates a new array
called `collection` that stores all possible combinations of two different
elements from the input array. The number of combinations is proportional to the
square of the size of the input array, leading to a space complexity of
$O(n^2)$.

## Task 2

> Following is a function that reverses an array. Describe its _space_
> complexity in terms of Big O:
>
> ```
> function reverse(array) {
>     let newArray = [];
>     for (let i = array.length - 1; i >= 0; i--) {
>         newArray.push(array[i]);
>     }
>     return newArray;
> }
> ```

The space complexity of the `reverse` function is $O(n)$, where $n$ is the size
of the input array. This is because the function creates a new array called
`newArray` to store the reversed elements of the input array. The size of
`newArray` is directly proportional to the size of the input array, leading to a
space complexity of $O(n)$.

## Task 3

> Create a new function to reverse an array that takes up just $O(1)$ extra
> space.

```cpp
#include <vector>
void reverseInPlace(std::vector<int> &array) {
  int left = 0, right = array.size() - 1;
  while (left < right) {
    std::swap(array[left], array[right]);
    left++;
    right--;
  }
}
```

The `reverseInPlace` function reverses the input array in place, using only
$O(1)$ extra space. It accomplishes this by swapping elements from the left side
of the array with the elements on the right, moving towards the center of the
array. The time complexity is $O(n)$, because it traverses the input array once,
but the space complexity is $O(1)$ because it doesn't create any additional
units of memory that grow with the size of the input.

## Task 4

> Following are three different implementations of a function that accepts an
> array of numbers and returns an array containing those numbers multiplied
> by 2. For example, if the input is `[5, 4, 3, 2, 1]`, the output will be
> `[10, 8, 6, 4, 2]`.
>
> ```
> function doubleArray1(array) {
>   let newArray = [];
>
>   for(let i = 0; i < array.length; i++) {
>     newArray.push(array[i] * 2);
>   }
>   return newArray;
> }
>
>
> function doubleArray2(array) {
>   for(let i = 0; i < array.length; i++) {
>     array[i] *= 2;
>   }
>   return array;
> }
>
>
> function doubleArray3(array, index=0) {
>   if (index >= array.length) { return; }
>   array[index] *= 2;
>   doubleArray3(array, index + 1);
>   return array;
> }
> ```
>
> Fill in the table that follows to describe the efficiency of these three
> versions in terms of both time and space:
>
> | Version    | Time complexity | Space complexity |
> | ---------- | --------------- | ---------------- |
> | Version #1 | ?               | ?                |
> | Version #2 | ?               | ?                |
> | Version #3 | ?               | ?                |

| Version    | Time complexity | Space complexity |
| ---------- | --------------- | ---------------- |
| Version #1 | O(n)            | O(n)             |
| Version #2 | O(n)            | O(1)             |
| Version #3 | O(n)            | O(n)             |

Version #1 has a space complexity of $O(n)$ because it creates a new array to
store the doubled values of the input array. The time complexity is $O(n)$
because it iterates through the input array once.

Version #2 has a space complexity of $O(1)$ because it modifies the input array
in place without creating a new array. The time complexity is still $O(n)$
because it iterates through the input array once.

Version #3 has a space complexity of $O(n)$ because it uses recursion, which
adds to the call stack. The time complexity is $O(n)$ because it iterates
through the input array once, but the recursion adds additional space usage for
each recursive call.
