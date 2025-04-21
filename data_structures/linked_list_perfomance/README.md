# Tasks

a) Use 100, 200, and 300 million elements of the same data type to compare
arrays' and linked-lists' performances using C++. You might have to use
profiling. Please research how to profile a code in C++. Evaluate the
performance in terms of time and space.

For example, add elements at the beginning of the array and linked lists and
compare. Similarly, add elements at the end of the array, such as linked lists,
and compare. The same applies to removing elements from arrays and linked lists
and comparing them.

b) Compare loop iterators; for example, compare for and while loops. See the
code below.

```cpp
 for (int i = 0; i < authorsList.size(); i++) {
             authorName = authorsList.get(i);
             System.out.println(authorName);
         }

 while (listIterator.hasNext()) {
             authorName = listIterator.next();
             System.out.println(authorName);
         }

```

Compare both the iterators and observe the performance. The performance is in
terms of time. The profiling code/engine itself has an overhead on the code you
are evaluating. Make sure you include this when evaluating the performance. The
documentation of parts a and b together should not exceed two pages. Use graphs
where applicable and explain the findings clearly.

## Task a

The first step I took was to create the necessary functions to add and remove
from the beginning and end of the array and linked list. Note, I used vectors
instead of arrays, because they are preferred in C++.

Vector functions:

- `vec.insert(vec.begin(), value)` - insert at the beginning
- `vec.push_back(value)` - insert at the end
- `vec.erase(vec.begin())` - remove from the beginning
- `vec.pop_back()` - remove from the end

Linked list functions:

- `list.push_front(value)` - insert at the beginning
- `list.push_back(value)` - insert at the end
- `list.pop_front()` - remove from the beginning
- `list.pop_back()` - remove from the end

Once I had the functions, I created a test function to test the performance of
each operation. I did this by creating a `time` function that uses `std::chrono`
to measure the time it takes to perform each operation. The results are stored
in a vector containing:

- The name of the operation
- The number of elements
- The memory in GiB consumed by the item
- The time it took to perform the operation

To ensure some consistency, I filled the `items` (vector or list) with
0...`size` values for each element. This way, the performance would be evaluated
for the full `item`, not just initialized. I then passed the full `item` to the
`time` function to measure the time it took to perform the operation. The time
taken to create the `items` was not included in the results, as it would skew
the results. The results were then printed to the console and saved to a CSV
file for further analysis.

Observations:

- Memory consumption was equal between the two data structures.
- Linked Lists were significantly faster than vectors for all operations.
- Profiling tools such as `gprof` did not provide useful information, so a
  manual approach was used to measure time.

## Task b

The first step was to convert the provided Java code to C++ code. Once I had the
translated code, I had to create the `authorsList` with fake author names, as it
wasn't provided. To do this, I used an old script I wrote which puts together
random first and last names together. The file with the `authorsList` is parsed
and pushed to a vector, which is used for the performance tests. I then used
`std::chrono` for timing the loops again. Since the tests were relatively fast,
I decided to run each test `10000` times to get a more accurate result. The
results include the mean and deviation of the `10000` runs.

Observations:

- Both loops and iterators had similar performance in terms of mean time,
  `+/- 5 microseconds`.
- Iterators had a lower deviation by about a factor of 3 (`10 microseconds` vs
  `30 microseconds`) than loops, which could indicate more consistent
  performance.
