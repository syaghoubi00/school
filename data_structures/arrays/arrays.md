# [Arrays - Theory](https://github.com/d-khan/dslabs/blob/b2dfff5067fa12ccfacce48f49850b893103ac07/intro/arrays.md)

## Task 3

> For an array containing 100 elements, provide the number of steps the
> following operations would take

- Reading
- Searching for a value not contained within the array
- Insertion at the beginning of the array
- Insertion at the end of the array
- Deletion at the beginning of the array
- Deletion at the end of the array

### Overview Table

| Operation                     | Number of Steps | Time Complexity |
| ----------------------------- | --------------- | --------------- |
| Reading                       | 1 step          | O(1)            |
| Searching (value not present) | 100 steps       | O(n)            |
| Insertion (beginning)         | 101 steps       | O(n)            |
| Insertion (end)               | 1 step          | O(1)            |
| Deletion (beginning)          | 99 steps        | O(n)            |
| Deletion (end)                | 1 step          | O(1)            |

### Explanation

#### Reading Operation

- **Steps:** 1
- **Explanation:** Reading from an array takes exactly one step because:
  - Arrays use index-based addressing
  - Memory location can be directly calculated using the base address
  - No matter the array size, reading takes constant time

#### Searching (Value Not Present)

- **Steps:** 100
- **Explanation:** For a value not in the array:
  - Must check every element
  - Will traverse all 100 elements
  - Can only determine that the value is absent after checking every element

#### Insertion at Beginning

- **Steps:** 101
- **Breakdown:**
  - 100 steps to shift existing elements right
  - 1 step to insert the new element
  - Total: 100 + 1 = 101 steps

#### Insertion at End

- **Steps:** 1
- **Explanation:**
  - No shifting required
  - Direct placement at the last position
  - Single operation regardless of array size

#### Deletion at Beginning

- **Steps:** 99
- **Breakdown:**
  - 99 steps to shift N-1 elements left
  - Shifting required for all elements except the deleted one
  - There is no need to delete the first element as it will be overwritten
    during the shift
    <!-- - **Steps:** 100
    - **Breakdown:**
      - 1 step to remove the first element
      - 99 steps to shift remaining elements left
      - Shifting required for all elements except the deleted one -->

#### Deletion at End

- **Steps:** 1
- **Explanation:**
  - No shifting required
  - Only a single operation to remove the last element

### Formulas

**Reading Time:** O(1)

- Direct access: T(n) = c (constant)

**Searching Time:** O(n)

- Worst case: T(n) = n
- Average case: T(n) = n/2

**Insertion Time:**

- Beginning: T(n) = n + 1
- End: T(n) = 1

**Deletion Time:**

- Beginning: T(n) = n - 1
- End: T(n) = 1

## Task 4

> Normally the search operation in an array looks for the first instance of a
> given value. But sometimes we may want to look for every instance of a given
> value. For example, say we want to count how many times the value “apple” is
> found inside an array. How many steps would it take to find all the “apples”?
> Give your answer in terms of N.

### Answer

**To find all instances of "apple" in an array of size N, it would take N
steps.**

#### Why?

1. **Why N steps?**

   - Even if we find an "apple", we can't stop searching
   - We must check EVERY element to ensure we don't miss any occurrences
   - There's no way to know if there are more "apples" without checking all
     elements

2. **Visualization:**

   ```txt
   Array: ["apple", "banana", "apple", "orange", "apple"]
   Size N = 5

   Steps:
   1. Check index 0: "apple"   (count = 1)
   2. Check index 1: "banana"
   3. Check index 2: "apple"   (count = 2)
   4. Check index 3: "orange"
   5. Check index 4: "apple"   (count = 3)
   ```

3. **Key Points:**
   - Best case: N steps (must check everything)
   - Worst case: N steps
   - Average case: N steps

### Time Complexity

- O(N) - Linear time complexity
- No way to optimize this specific operation as we need to check every element
