# [Recursion](https://github.com/d-khan/dslabs/blob/8214da88d1009266cf3a6d4fc51cf19eac19160a/Recursions/Activity.md)

## Task 1

> The following function prints every other number from a low number to a high
> number. For example, if low is 0 and high is 10, it would print:
>
> ```txt
> 0
> 2
> 4
> 6
> 8
> 10
> ```
>
> Identify the base case in the function:
>
> ```python
> def print_every_other(low, high)
>     return if low > high
>     puts low
>     print_every_other(low + 2, high)
> end
> ```

The base case is what stops the recursion from continuing indefinitely. In this
case, the base case is: `return if low > high`. This means that when the `low`
number exceeds the `high` number, the function will stop calling itself and
return, effectively ending the recursion.

## Task 2

> My kid was playing with my computer and changed my factorial function so that
> it computes factorial based on (n - 2) instead of (n - 1). Predict what will
> happen when we run factorial(10) using this function:
>
> ```python
> def factorial(n)
>     return 1 if n == 1
>     return n * factorial(n - 2)
> end
> ```

Python code:

```python
def factorial(n):
    if n == 0:
        return 1
    else:
        return n * factorial(n - 2)
```

The recursive factorial function will not compute the factorial of 10 correctly.
It will only compute the product of every second number down to 1. This will
result in `3840` instead of the correct factorial value of `3628800`.

## Task 3

> Following is a function in which we pass in two numbers called low and high.
> The function returns the sum of all the numbers from low to high. For example,
> if low is 1, and high is 10, the function will return the sum of all numbers
> from 1 to 10, which is 55. However, our code is missing the base case, and
> will run indefinitely! Fix the code by adding the correct base case:
>
> ```python
> def sum(low, high)
>     return high + sum(low, high - 1)
> end
> ```

We can add the following base case to the function:

```python
def sum(low: int, high: int) -> int:
    if high == 0:
        return 0
    else:
        return high + sum(low, high - 1)
```

This base case checks if `high` is equal to `0`. If it is, the function returns
`0`, effectively stopping the recursion. Otherwise, it continues to sum the
numbers from `low` to `high` by recursively calling itself with `high - 1`.

## Task 4

> Here is an array containing both numbers as well as other arrays, which in
> turn contain numbers and arrays:
>
> ```python
> array=[ 1,
>         2,
>         3,
>         [4, 5, 6],
>         7,
>         [8,
>           [9, 10, 11,
>             [12, 13, 14]
>           ]
>         ],
>         [15, 16, 17, 18, 19,
>           [20, 21, 22,
>             [23, 24, 25,
>               [26, 27, 29]
>             ], 30, 31
>           ], 32
>         ], 33
>       ]
> ```
>
> Write a recursive function that prints all the numbers (and just numbers).

Python code:

```python
def traverse_array(arr):
    for element in arr:
        if isinstance(element, list):
            traverse_array(element)
        else:
            print(element)
```

C++ code:

```cpp
void traverseArray(const std::vector<std::any> &arr) {
  for (const auto &element : arr) {
    if (element.type() == typeid(std::vector<std::any>)) {
      traverseArray(std::any_cast<const std::vector<std::any> &>(element));
    } else {
      std::cout << std::any_cast<int>(element) << std::endl;
    }
  }
}
```

The base case is a for loop which iterates through the array. If the element is
itself an array, the function calls itself recursively. If the element is a
number, it prints the number.
