# [Binary Search Trees](https://github.com/d-khan/dslabs/blob/main/intro/binary-search-trees-activity.md)

## Task 1

> Imagine you were to take an empty binary search tree and insert the following
> sequence of numbers in this order: `[1, 5, 9, 2, 4, 10, 6, 3, 8]`. Draw a
> diagram showing what the binary search tree would look like. Remember, the
> numbers are being inserted in the order presented here.

```txt
Step 1: Insert 1
    1

Step 2: Insert 5 (greater than 1, goes to the right)
    1
     \
      5

Step 3: Insert 9 (greater than 1 and 5, goes to the right of 5)
    1
     \
      5
       \
        9

Step 4: Insert 2 (greater than 1 but less than 5, goes to the right of 1 and left of 5)
    1
     \
      5
     / \
    2   9

Step 5: Insert 4 (greater than 1 and 2 but less than 5, goes to the right of 2)
    1
     \
      5
     / \
    2   9
     \
      4

Step 6: Insert 10 (greater than 1, 5, and 9, goes to the right of 9)
    1
     \
      5
     / \
    2   9
     \   \
      4   10

Step 7: Insert 6 (greater than 1 and 5 but less than 9, goes to the left of 9)
        1
         \
          5
        /   \
       2     9
        \   / \
         4 6   10

Step 8: Insert 3 (greater than 1 and 2 but less than 4 and 5, goes to the left of 4)
        1
         \
          5
        /   \
       2     9
        \   / \
         4 6   10
        /
       3

Step 9: Insert 8 (greater than 1, 5, and 6 but less than 9, goes to the right of 6)
    1
     \
      5
     /  \
    2    9
     \  /  \
     4  6  10
     /  \
    3    8
```

Final tree:

```txt
       1
        \
         5
       /   \
      2     9
       \   / \
        4 6  10
       /   \
      3     8
```

## Task 2

> If a well-balanced binary search tree contains 1,000 values, what is the
> maximum number of steps it would take to search for a value within it?

The search efficiency of a well balanced binary search tree is $O(log N)$.

The maximum steps would be $log_2(1000) = 9.97 \approx 10$.

The $O(log N)$ only holds true for a well balanced binary search tree. As
imbalance increases, the complexity moves closer to $O(N)$.

## Task 3

> Write an algorithm that finds the greatest value within a binary search tree.

## Task 4

> Write a code in C++ using the same array mentioned in [Task 1](#task-1) and
> implement a binary search tree. Only insertion operation is required.
