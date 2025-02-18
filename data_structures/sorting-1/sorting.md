# [Sorting - 1](https://github.com/d-khan/dslabs/blob/main/intro/sorting-1.md)

## Task 1

> Use Big O Notation to describe the time complexity of an algorithm that takes
> $4N + 16$

For $4N + 16$ steps:

- This is a linear function with a constant
- We drop constants and coefficients in Big O notation
- Drop the constant term (16)
- Drop the coefficient (4)
- Therefore, this is $O(N)$

## Task 2

> Use Big O Notation to describe the time complexity of an algorithm that takes
> $2N^2$

For $2N^2$:

- This is a quadratic function with a coefficient
- We drop the coefficient in Big O notation
- Therefore, this is $O(N^2)$

## Task 3

> Use Big O Notation to describe the time complexity of the following function,
> which returns the sum of all numbers of an array after the numbers have been
> doubled:
>
> ```ruby
> def double_then_sum(array)
>   doubled_array = []
>
>   array.each do |number|
>     doubled_array << number *= 2
>   end
>
>   sum = 0
>
>   doubled_array.each do |number|
>     sum += number
>   end
>   return sum
> end
> ```

For the `double_then_sum` function:

- First loop: Iterates through array once to double numbers: $O(N)$
- Second loop: Iterates through `doubled_array` once to sum: $O(N)$
- When we have sequential operations, we add them:
  $O(N) + O(N) = O(N+N) = O(2N)$
- Simplifies to: $O(N)$

## Task 4

> Use Big O Notation to describe the time complexity of the following function,
> which accepts an array of strings and prints each string in multiple cases:
>
> ```ruby
> def multiple_cases(array)
>  array.each do |string|
>   puts string.upcase
>   puts string.downcase
>   puts string.capitalize
>  end
> end
> ```

For the `multiple_cases` function:

- Single loop through the array: $O(N)$
- For each iteration, performs 3 constant time operations (`upcase`, `downcase`,
  `capitalize`)
- $O(N \times (1+1+1)) = O(3N)$
- Constants don't affect Big O notation
- Therefore, this is $O(N)$

## Task 5

> The next function iterates over an array of numbers, and for each number whose
> index is even, it prints the sum of that number plus every number in the
> array. What is this function’s efficiency in terms of Big O Notation?
>
> ```ruby
> def every_other(array)
>  array.each_with_index do |number, index|
>   if index.even?
>    array.each do |other_number|
>     puts number + other_number
>    end
>   end
>  end
> end
> ```

For the `every_other` function:

- Outer loop iterates through entire array: $O(N)$
- For each even index (approximately half, assuming an equal `odd:even`
  distribution of numbers): $\frac N 2$
  - Inner loop iterates through entire array: $O(N)$
- When loops are nested, we multiply:
  $O(N) \times O(\frac N 2) = O(N \times \frac N 2) = O(\frac {N^2} 2)$
- Simplifies to: $O(N^2)$

## Summary

- We always drop constants and coefficients in Big O notation
- Sequential operations are added
- Nested operations are multiplied
- We use the highest order term only
