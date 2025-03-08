# [Hashing](https://github.com/d-khan/dslabs/blob/8214da88d1009266cf3a6d4fc51cf19eac19160a/intro/hashing.md)

## Task 1

> Assume you have a simple single-dimensional array:
>
> `array = [200, 400, 100, 50, 350]`
>
> Linear search will take $O(n)$. Write a code in C++/Python to improve the
> search operation efficiency from O(n) to O(1)

see:

- [Task-1 (python)](task-1.py)
- [Task-1 (c++)](task-1.cpp)

## Task 2

> Use C++, generate hash value of your name

see: [Task-2](task-2.cpp)

## Task 3

> With the help of a figure, explain the problem that occurred due to
> introducing a tombstone to mark the deleted cell

Hash tables provide O(1) average lookup time, but deletion operations can
complicate this efficiency. When an element is deleted, leaving an empty `null`
cell can break search operations, so `tombstones` are used to mark deleted
cells. A tombstone is special marker that indicates "an element was here but was
deleted".

### Initial Hash Table State

A hash table with some elements:

```txt
 Index | Value   | Status
-------|---------|--------
   0   | "apple" | OCCUPIED
   1   | null    | EMPTY
   2   | "banana"| OCCUPIED
   3   | "cherry"| OCCUPIED
   4   | null    | EMPTY
   5   | "date"  | OCCUPIED
   6   | null    | EMPTY
   7   | "fig"   | OCCUPIED
```

### Deletion Approaches

#### Approach 1: Simple Nullification (Problematic)

```txt
// If we delete "banana" at index 2 and just set to null:
 Index | Value   | Status
-------|---------|--------
   0   | "apple" | OCCUPIED
   1   | null    | EMPTY
-> 2   | null    | EMPTY (was "banana")
-> 3   | "cherry"| OCCUPIED
   ...
```

**The Problem**: If `cherry` was placed at `index 3` due to collision at
`index 2`, searching for `cherry` will now stop at `index 2` (`null`) and fail
to find it even though it is in `index 3`, because there is no prior knowledge
of the collision, so the assumption is that there should be a value in
`index 2`, if it exists.

#### Approach 2: Tombstone Insertion

```txt
// Instead, we place a tombstone where "banana" was deleted:
 Index | Value   | Status
-------|---------|--------
   0   | "apple" | OCCUPIED
   1   | null    | EMPTY
-> 2   | T       | DELETED (tombstone)
   3   | "cherry"| OCCUPIED
   ...
```

When searching for an element, the search must continue past tombstones:

```txt
 Hash("cherry") -> 2
 Index | Value   | Status
-------|---------|--------
   0   | "apple" | OCCUPIED
   1   | null    | EMPTY
-> 2   | T       | DELETED <- Start searching here
-> 3   | "cherry"| OCCUPIED
   4   | null    | EMPTY
   ...

Search path: 2 -> 3
             T    x
           Skip  Found
```

`cherry` was able to be found because the search continued past the tombstone,
instead of stopping at the `null` value.

### The Problem With Tombstones

Now let's insert a new item `grape` that hashes to `index 2`:

```txt
 Hash("grape") -> 2
 Index | Value   | Status
-------|---------|--------
   0   | "apple" | OCCUPIED
   1   | null    | EMPTY
   2   | T       | DELETED  <- Must check and continue
   3   | "cherry"| OCCUPIED <- Must check and continue
   4   | T       | DELETED  <- Must check and continue
   5   | "date"  | OCCUPIED <- Must check and continue
   6   | null    | EMPTY    <- Can insert here
   7   | "fig"   | OCCUPIED
```

The search path becomes: 2 -> -> 3 -> 4 -> 5 -> 6

#### Why Can't We Put `grape` at `index 2`?

1. `grape` is hashed to `index 2`
2. But what if something else like `date` was also hashed to `index 2` earlier?
3. If `date` arrived, didn't find an empty spot, and moved the available
   `index 5`
4. Someone looking for `date` would still need to follow the same path

If we put `grape` at position `index 2`:

- Anyone searching for `date` would stop at `index 2` and not find it
- They'd find `grape` and say "This isn't my `date`!" and conclude that `date`
  doesn't exist
- But `date` might still be at `index 5`

So, by skipping tombstones, we ensure that the search path is preserved and
insert `grape` at `index 6` instead. That way any previous collisions (such as
`date`) are still found.

**The search path must be preserved even after deletions.**

This means:

- When inserting, we must follow the same probing sequence we would follow
  during searching
- We can only insert at an `EMPTY` slot, not at a `DELETED` slot
- `DELETED` slots (tombstones) are skipped during insertion, just as they are
  during search

##### Grapes Journey

1. h(`grape`) -> 2: "I should go to `index 2`!"
2. Checks `index 2`: "Oh, there's a `tombstone` here. Can't stop!"
3. Probe to `index 3`: "`cherry` is here, not my spot!"
4. Probe to `index 4`: "Another `tombstone`, keep moving!"
5. Probe to `index 5`: "`date` is here, not my spot!"
6. Probe to `index 6`: "Finally! An empty `null` spot where I can settle down!"

#### Tombstone Performance Degradation

```txt
Before tombstones: [A][E][B][C][E][D][E][F]
                             ^
                    Direct access O(1)

After tombstones:  [A][T][T][C][T][D][T][F]
                       ^  ^  ^
                   Now requires O(n) traversal, where n = number of tombstones
```

#### Tombstone Space Inefficiency

```txt
[A][T][T][C][T][D][T][F]
    ^  ^     ^     ^
Tombstones occupy space but store no useful data
```

### Conclusion

The tombstone approach causes:

- **Performance decay** - Search operations degrade toward O(n) over time due to
  longer search paths
- **Memory waste** - Tombstones consume space without storing data
- **Increased complexity** - Search algorithms must process tombstones
  differently
- **Rehashing necessity** - Eventually requires complete rebuilding to restore
  efficiency
- **Load factor monitoring** - Tracking of (items + tombstones)/capacity ratio

## Task 3 - Supplemental

### Rehashing

Rehashing is the process of creating a new hash table and transferring only
non-deleted elements:

```txt
Original table (with tombstones):
[A][T][T][C][T][D][T][F]

After rehashing (new table):
[A][C][D][F][null][null][null][null]

Result: Clean table with O(1) operations restored
```

The rehashing process:

1. Create new table of appropriate size
2. For each element in old table:
   1. If element is actual data (not T or null)
   2. Compute new hash in new table
   3. Insert at new position
3. Replace old table with new table

### Alternative Approaches

#### Separate Chaining vs. Open Addressing with Tombstones

- Benefits:
  - No tombstones needed
  - Deletions are clean
- Drawbacks:
  - Requires pointers/extra memory for chains

```txt
// Separate Chaining
Index 0: -> apple ->
Index 1: ->
Index 2: -> banana -> grape ->
Index 3: -> cherry ->
...
```
