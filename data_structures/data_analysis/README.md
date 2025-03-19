# Task

You are a data analyst for a company that sells residential computers. The
manager shared with you a dataset of the year 2023 sales.

```txt
Month Sales in USD (Millions)
Jan 100
Feb 113
Mar 110
Apr 85
May 81
Jun 101
Jul 94
Aug 106
Sep 105
Oct 102
Nov 86
Dec 63
```

The manager plans to run an advertising campaign for the products offered by the
company. The manager wants to know which consecutive months contribute towards
the highest sales so that the advertisement can be targeted on months before and
after the successive months of the highest sales. Based on the dataset, you have
the following tasks:

a. Explain how you are going to solve the problem mentioned above. No coding or
pseudocode is needed in this step.

b. Implement the solution that you proposed in part a. Furthermore, the
implemented solution should be able to identify consecutive months when the
sales are at the highest when a different dataset is used. C++ code is needed.

c. Write the pseudocode and explain the algorithm using O(N) notation. No coding
is needed in this step.

d. What are the limitations of the solution you proposed in part a?

## Task a: Explaining the Solution Approach

1. **Data Processing**: First, I'd convert the unstructured sales data into a
   semi-structured format, such as CSV, where each month is associated with its
   sales value.

2. **Finding the Best Sales Period**: I would use a sliding window algorithm to
   find the period with highest average sales:

   - Initialize variables to track the best period and its sales metrics
   - For each possible window size (from 1 to 12 months)
   - For each possible starting point, calculate the total and average sales for
     that window
   - Keep track of the window with the highest average sales
   - Consider periods that might wrap around from December to January

3. **Identifying Target Advertising Months**: Once I find the period with
   highest average sales, I would determine:
   - The month immediately before this period (for pre-season advertising)
   - The month immediately after this period (for post-season advertising)

## Task b: Implementing the Solution in C++

See: [code](./advert_target_months.cpp)

1. Reads sales data from a file or uses default data if no file is provided
2. Uses a sliding window approach to calculate all possible consecutive month
   combinations
3. Finds the combination with the highest average monthly sales
4. Identifies the months before and after the best period for targeted
   advertising
5. Provides command-line options for sorting by different metrics (average or
   total sales)

The key algorithm uses a sliding window approach, which:

- Considers all possible window sizes (period lengths)
- For each window size, slides the window through all possible starting
  positions
- Efficiently calculates average sales for each window
- Tracks the best period found

## Task c: O(N) Notation and Pseudocode

**Time Complexity Analysis**:

- The algorithm has two nested loops:
  - The outer loop runs $n$ times (for each possible window size)
  - The inner loop runs $n$ times (for each possible starting position)
  - For each window, we do $O(1)$ work to calculate the new window
- This gives us a time complexity of $O(N^2)$

**Pseudocode**:

```text
// Find the best consecutive period using sliding window
function findBestPeriod(salesData, months):
    bestAvg = 0
    bestPeriod = null

    // For each possible window size
    for windowSize = 1 to months.length:

        // Calculate initial window sum
        windowSum = sum of first windowSize elements
        windowAvg = windowSum / windowSize

        // Track best window
        if windowAvg > bestAvg:
            bestAvg = windowAvg
            bestPeriod = {start: 0, length: windowSize}

        // Slide the window through all positions
        for startIdx = 1 to months.length - 1:
            // Remove previous element, add new element
            windowSum = windowSum - salesData[(startIdx-1) % months.length] + salesData[(startIdx+windowSize-1) % months.length]
            windowAvg = windowSum / windowSize

            if windowAvg > bestAvg:
                bestAvg = windowAvg
                bestPeriod = {start: startIdx, length: windowSize}

    return bestPeriod
```

## Task d: Limitations of the Solution

The solution has several limitations:

1. **Computational Efficiency**: While the sliding window approach is more
   efficient than calculating all combinations $O(N^3)$ -- it still has $O(N^2)$
   time complexity. This might be slow for large datasets, but since we have a
   maximum of 12 months, it should be acceptable. As it will never be more than
   144 iterations.

2. **Memory Usage**: The algorithm uses $O(N)$ space.

3. **Simplistic Model**: The solution doesn't account for:

   - External factors affecting sales (economic conditions, competitor actions,
     etc.)
   - The cost of advertising or production in different months (ROI might be
     better in lower-cost months)

4. **Equal Averages Handling**: When multiple periods have the same average
   sales, the algorithm prefers the first one found, which might not always be
   the optimal business decision.

5. **Limited Data**: Analyzing only one year of data might not capture long-term
   trends.

6. **Static Analysis**: The algorithm performs a one-time analysis rather than
   adapting to new data.

7. **Limited Error Handling**: The file parsing assumes a specific format and
   has minimal validation.
