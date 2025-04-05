# [Binary Heaps](https://github.com/d-khan/dslabs/blob/8214da88d1009266cf3a6d4fc51cf19eac19160a/binaryheaps/Activity.md)

## Task 1

> Draw what the following heap would look like after we insert the value 11 into
> it:
> <img width="377" alt="image" src="https://user-images.githubusercontent.com/11669149/229943640-2f9f7951-a9c6-4e4a-86f2-ea5dcd4bc64a.png">

Step 1: Insert the value of 11 into the leftmost open position in the heap.

```txt
       10
      /  \
     /    \
    9      8
   / \    / \
  6   5  7   4
 / \ / \
2  1 3 11
```

Step 2: Compare the value of 11 with its parent (5). Since 11 is greater than 5,
swap them.

```txt
       10
      /   \
     /     \
    9       8
   / \     / \
  6   11  7   4
 / \  / \
2  1  3  5
```

Step 3: Compare the value of 11 with its parent (9). Since 11 is greater than 9,
swap them.

```txt
       10
      /  \
     /    \
    11     8
   /  \   /  \
  6    9 7    4
 / \  / \
2  1  3  5
```

Step 4: Compare the value of 11 with its parent (10). Since 11 is greater than
10, swap them.

```txt
       11
      /  \
     /    \
    10     8
   /  \   / \
  6    9 7   4
 / \  / \
2  1 3   5
```

## Task 2

> Draw what the previous heap would look like after we delete the root node.

To delete the root node, we need to replace it with the last element in the heap
(5) and then bubble down the new root node (5) to restore the heap property.

Step 1: Replace the root node (11) with the last element (5).

```txt
        5
       /  \
      /    \
     10     8
   /   \   / \
  6     9 7   4
 / \   /
2   1 3
```

Step 2: Compare the value of 5 with its children (10 and 8). Since 10 is the
largest, swap 5 and 10.

```txt
        10
       /  \
      /    \
     5      8
   /   \   / \
  6     9 7   4
 / \   /
2   1 3
```

Step 3: Compare the value of 5 with its children (6 and 9). Since 9 is the
largest, swap 5 and 9.

```txt
        10
       /  \
      /    \
     9      8
   /   \   / \
  6     5 7   4
 / \   /
2   1 3
```

## Task 3

> Imagine you’ve built a brand-new heap by inserting the following numbers into
> the heap in this particular order: 55, 22, 34, 10, 2, 99, 68. If you then pop
> them from the heap one at a time and insert the numbers into a new array, in
> what order would the numbers now appear?

Step 1: Insert the numbers into the heap in the given order.

1. Insert 55 (root)
2. Insert 22 (left child of 55)
3. Compare 22 with 55. No swap needed.
4. Insert 34 (right child of 55)
5. Compare 34 with 55. No swap needed.
6. Insert 10 (left child of 22)
7. Compare 10 with 22. No swap needed.
8. Insert 2 (right child of 22)
9. Compare 2 with 22. No swap needed.
10. Insert 99 (left child of 34)
11. Compare 99 with 34. Swap them.
12. Compare 99 with 55. Swap them. (99 new root)
13. Insert 68 (right child of 55)
14. Compare 68 with 55. Swap them.
15. Compare 68 with 99. No swap needed.

```txt
      99
     /  \
    /    \
   /      \
  22      68
 /  \    /  \
10   2  34   55
```

Step 2: Pop the numbers from the heap one at a time and insert them into an
array. Starting at the top of the heap (root node), then moving down, left to
right.

1. Pop 99 = `[99]`
2. Pop 22 = `[99, 22]`
3. Pop 68 = `[99, 22, 68]`
4. Pop 10 = `[99, 22, 68, 10]`
5. Pop 2 = `[99, 22, 68, 10, 2]`
6. Pop 34 = `[99, 22, 68, 10, 2, 34]`
7. Pop 55 = `[99, 22, 68, 10, 2, 34, 55]`

`[99,22,68,10,2,34,55]`
