"""Hashing.

Task 1:
Python code to improve the search operation efficiency from O(n) to O(1).

To improve search operation efficiency from O(n) to O(1), we need to use a hash table
(dictionary in Python). This allows us to look up elements by their values in constant
time.

This solution works by:
1. Creating a dictionary that maps each value to its index in the original array
2. Using the dictionary for lookups, which gives us O(1) time complexity

The tradeoff is:
- We need additional O(n) space to store the lookup table alongside the original array
- The initial creation of the lookup table is an O(n) operation
- But after creation, all searches are O(1) instead of O(n)

This demonstrates a common space-time tradeoff: we use additional memory to achieve
faster search performance.
"""


def create_lookup_table(array: list[int]) -> dict[int, int]:
    """Create a dictionary that maps values to their indices.

    Uses the index from the array as the value in the dictionary, and the value from
    the array as the key. That way, we can look up the index of a value in the array.

    Args:
        array: A list of integers to be indexed.

    Returns:
        A dictionary mapping each value to its index in the array.

    """
    return {value: index for index, value in enumerate(array)}


def find_element(dictionary: dict, value: int) -> int:
    """Find the index of a value in the array using the lookup table.

    Args:
        dictionary: The lookup table mapping values to indices.
        value: The value to search for.

    Returns:
        The index of the value if found, or -1 if not found.

    """
    if value in dictionary:  # O(1) operation (checking if the key exists)
        return dictionary[value]  # O(1) operation (retrieving the value of the key)
    return -1  # Element not found


if __name__ == "__main__":
    """Simple Dictionary Creation and Lookup"""
    d = {"k1": "v1", "k2": "v2", "k3": "v3"}
    d["k4"] = "v4"  # Add a new key-value pair
    d.update({"k5": "v5", "k6": "v6", "k7": "v7"})  # Add multiple key-value pairs
    print(d)  # Print the dictionary
    k = "k1"
    nk = "k9"
    print(f"Value of {k}: {d.get(k, -1)}")  # Print the value of the key k ("k1": "v1")
    print(f"Value of {nk}: {d.get(nk, -1)}")  # Print -1 if not found

    """Converting the original array to a dictionary"""
    array = [200, 400, 100, 50, 350]
    # Create the lookup table (O(n) operation, done once)
    dictionary = create_lookup_table(array)
    # Simplified (no conversion function)
    lookup_table = {value: index for index, value in enumerate(array)}

    print("dictionary (value:index):", dictionary)  # Print the dictionary
    print(
        f"Index of 100: {find_element(dictionary, 100)}",
    )  # Print the index of value 100
    print(
        f"Index of 999: {find_element(dictionary, 999)}",
    )  # Print -1 (not found)
