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

2. **Finding the Best Sales Period**: I would examine all possible consecutive
   month combinations to find the period with highest average sales. This
   includes:

   - Considering every possible starting month
   - For each starting month, analyzing all possible period lengths (from 1 to
     12 months)
   - Since months form an annual cycle, I need to account for periods that wrap
     around from December to January.
   - For each combination, calculating the average monthly sales
   - Tracking which combination yields the highest average

3. **Identifying Target Advertising Months**: Once I find the period with
   highest average sales, I would determine:
   - The month immediately before this period (for pre-season advertising)
   - The month immediately after this period (for post-season advertising)

## Task b: Implementing the Solution in C++

See: [code](./advert_target_months.cpp)

1. Reads sales data from a file or uses default data if no file is provided
2. Calculates all possible consecutive month combinations
3. Finds the combination with the highest average monthly sales
4. Identifies the months before and after the best period for targeted
   advertising
5. Provides command-line options for sorting by different metrics (average or
   total sales)

The key algorithm is in the `monthCombos` function, which:

- Considers all possible starting months
- For each start, considers all possible period lengths
- Calculates average sales for each period
- Tracks the best period found

## Task c: O(N) Notation and Pseudocode

**Time Complexity Analysis**:

- The main algorithm has three nested loops:
  - The outer loop runs n times (for each starting month)
  - The middle loop runs n times (for each possible length)
  - The inner loop runs up to n times (for each month in the period)
- This gives us a time complexity of $O(N^3)$

**Pseudocode**:

```text
// O(n) over all months
// Set the starting month for the loop
// Loop 1: Jan, Loop 2: Feb, ...
for (startMonth = 0; startMonth < endMonth; startMonth++)
  // O(n) over all possible period lengths
  // For each possible period length
  // eg. 1 month, 2 months, ...
  for (curStartMonth = 0; curStartMonth < endMonth; curStartMonth++)
    // O(n) over all months in the period
    // Calculate total sales for this period
    for (startMonth = 0; startMonth < curStartMonth; startMonth++)
      // Calculate total sales for this period
      totalSales += salesData[startMonth].sales

    avgSales = totalSales / periodLength
```

## Task d: Limitations of the Solution

The solution has several limitations:

1. **Computational Efficiency**: The current solution has exponential time
   complexity, which is inefficient for large datasets. For 12 months it's fine,
   but for larger datasets it would be problematic.

2. **Memory Usage**: The algorithm stores all possible combinations, which uses
   $O(N^2)$ space.

3. **Simplistic Model**: The solution doesn't account for:

   - External factors affecting sales (economic conditions, competitor actions,
     etc.)
   - The cost of advertising or production in different months (ROI might be
     better in lower-cost months)

4. **Equal Averages Handling**: When multiple periods have the same average
   sales, the algorithm prefers longer periods, which might not always be the
   optimal business decision.

5. **Limited Data**: Analyzing only one year of data might not capture long-term
   trends.

6. **Static Analysis**: The algorithm performs a one-time analysis rather than
   adapting to new data.

7. **Limited Error Handling**: The file parsing assumes a specific format and
   has minimal validation.
