# [Stacks and Queues](https://github.com/d-khan/dslabs/blob/main/intro/stacks-queues.md)

## Task 1

> Using Figure 17 as a model, in the book
> [Data Structures in C++](https://d-khan.github.io/ds), illustrate the result
> of each operation in the sequence PUSH(S,4), PUSH(S,1), PUSH(S,3), POP(S),
> PUSH(S,8), and POP(S) on an initially empty stack $S$ stored in array
> $S[1..6]$. **_Code is not required._**

```txt
Array S[1..6]: [null, null, null, null, null, null]
                    Top = 0 (empty stack)

PUSH(S,4): [4, null, null, null, null, null]
            ^
          Top = 1

PUSH(S,1): [4, 1, null, null, null, null]
               ^
            Top = 2

PUSH(S,3): [4, 1, 3, null, null, null]
                  ^
               Top = 3

POP(S): [4, 1, null, null, null, null]
            ^
         Top = 2

PUSH(S,8): [4, 1, 8, null, null, null]
                  ^
               Top = 3

Pop(S): [4, 1, null, null, null, null]
            ^
         Top = 2
```

## Task 2

> Using Figure 18 as a model, in the book
> [Data Structures in C++](https://d-khan.github.io/ds), illustrate the result
> of each operation in the sequence ENQUEUE(Q,4), ENQUEUE(Q,1), ENQUEUE(Q,3),
> DEQUEUE(Q), ENQUEUE(Q,8), and DEQUEUE(Q) on an initially empty queue $Q$
> stored in array $Q[1..6]$. **_Code is not required._**

## Task 3

> Rewrite ENQUEUE and DEQUEUE to detect **_underflow_** and **_overflow_** of a
> queue. (see Listings 4 & 5 in the book). **_Code is not required._**

## Task 4

> A stack allows insertion and deletion of elements at only end, and a queue
> allows insertion at one end and deletion at the other end, a **deque**
> (double-ended queue) allows insertion and deletion at both ends. Write four
> $O(1)$-time procedures to insert elements into and delete elements from both
> ends of a deque implemented by an array. **_Code is not required._**
