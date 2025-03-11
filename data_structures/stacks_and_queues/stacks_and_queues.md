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

```txt
Array Q[1..6]: [null, null, null, null, null, null]
                 Front = 0, Rear = 0 (empty queue)

ENQUEUE(Q,4): [4, null, null, null, null, null]
               ^
              Front = 1, Rear = 1

ENQUEUE(Q,1): [4, 1, null, null, null, null]
               ^  ^
              Front = 1, Rear = 2

ENQUEUE(Q,3): [4, 1, 3, null, null, null]
               ^     ^
              Front = 1, Rear = 3

DEQUEUE(Q): [null, 1, 3, null, null, null]
              ^    ^  ^
            Front = 2, Rear = 3

ENQUEUE(Q,8): [null, 1, 3, 8, null, null]
                     ^     ^
                    Front = 2, Rear = 4

DEQUEUE(Q): [null, null, 3, 8, null, null]
                    ^    ^  ^
                  Front = 3, Rear = 4
```

## Task 3

> Rewrite ENQUEUE and DEQUEUE to detect **_underflow_** and **_overflow_** of a
> queue. (see Listings 4 & 5 in the book). **_Code is not required._**

### Modified ENQUEUE

Modified code checks for overflow by comparing the head and tail pointers. If
adding a new element would make the tail pointer land on the head, or if
wrapping around would make the tail pointer land on the head, the queue is full
(no available indexes to insert new value) and an error occurs.

```txt
ENQUEUE(Q,x):
  if Q.head == Q.tail + 1 or              // If adding a new element would make the tail pointer land on the head
    (Q.head == 1 and Q.tail == Q.length)  // Or if wrapping around would make the tail pointer land on the head
    error "Queue overflow" // Queue is full
  else                     // If the queue is not full
    Q[Q.tail] = x          // Store the new element at the tail
    if Q.tail == Q.length    // If the tail is at the end of the array
        Q.tail = 1           // Wrap around to the beginning
    else Q.tail = Q.tail + 1 // Otherwise, advance the tail
```

### Modified DEQUEUE

Modified code checks for underflow by comparing the head and tail pointers. If
they are equal, the queue is empty, so dequeueing is not possible and an error
occurs. The error handling could be written in a way to be a soft error (eg.
returning `null`) to prevent crashing, since no data would be lost.

```txt
DEQUEUE(Q):
  if Q.head == Q.tail // Check for underflow - queue is empty when head equals tail
      error "Queue underflow"
  else
      x = Q[Q.head]         // Set x to the element at the head
      if Q.head == Q.length // If the head is at the end of the array
          Q.head = 1        // Wrap around to the beginning
      else
          Q.head = Q.head + 1 // Otherwise, advance the head
      return x // Return the element at the head
```

## Task 4

> A stack allows insertion and deletion of elements at only end, and a queue
> allows insertion at one end and deletion at the other end, a **deque**
> (double-ended queue) allows insertion and deletion at both ends. Write four
> $O(1)$-time procedures to insert elements into and delete elements from both
> ends of a deque implemented by an array. **_Code is not required._**
