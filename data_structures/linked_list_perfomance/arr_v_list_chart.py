"""Plotting performance comparison of array vs linked list operations."""  # noqa: INP001

import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns

MILLION = 1_000_000
SMALL = 100 * MILLION
MEDIUM = 200 * MILLION
LARGE = 300 * MILLION

file = pd.read_csv("performance_results.csv")


def extract_operation(name: str) -> str:
    """Get the operation type from the name."""
    if "Add to Beginning" in name:
        return "Add to Beginning"
    if "Add to End" in name:
        return "Add to End"
    if "Remove from Beginning" in name:
        return "Remove from Beginning"
    if "Remove from End" in name:
        return "Remove from End"
    return "Other"


# Create new columns
file["Operation"] = file["Name"].apply(extract_operation)
file["Data Structure"] = file["Name"].apply(lambda x: x.split(" ")[-1])

# Create a grouped bar chart
plt.figure(figsize=(14, 8))
sns.set_style("whitegrid")

# Using logarithmic scale to better visualize the different magnitudes
plt.yscale("log")

# Create the grouped bar chart
chart = sns.barplot(
    x="Operation",
    y="Duration(ms)",
    hue="Data Structure",
    palette="viridis",
    data=pd.DataFrame(file[file["Size"] == SMALL]),
)

plt.title("Performance Comparison - Size: 100,000", fontsize=16)
plt.xlabel("Operation Type", fontsize=14)
plt.ylabel("Duration (ms) - Log Scale", fontsize=14)
plt.xticks(rotation=45)
plt.legend(title="Data Structure")
plt.tight_layout()

# Save the figure
plt.savefig("performance_comparison_100k.png")
plt.show()

# Create another chart for MEDIUM size
plt.figure(figsize=(14, 8))
chart = sns.barplot(
    x="Operation",
    y="Duration(ms)",
    hue="Data Structure",
    palette="viridis",
    data=pd.DataFrame(file[file["Size"] == MEDIUM]),
)

plt.yscale("log")
plt.title("Performance Comparison - Size: 500,000", fontsize=16)
plt.xlabel("Operation Type", fontsize=14)
plt.ylabel("Duration (ms) - Log Scale", fontsize=14)
plt.xticks(rotation=45)
plt.legend(title="Data Structure")
plt.tight_layout()

# Save the figure
plt.savefig("performance_comparison_500k.png")
plt.show()

# Create a single chart for all data with facet grid
plt.figure(figsize=(16, 10))
g = sns.catplot(
    x="Operation",
    y="Duration(ms)",
    hue="Data Structure",
    col="Size",
    kind="bar",
    palette="viridis",
    height=6,
    aspect=1.2,
    data=file,
)

# Set log scale for all axes
for ax in g.axes.flat:
    ax.set_yscale("log")
    ax.set_xticklabels(ax.get_xticklabels(), rotation=45)

g.figure.suptitle("Performance Comparison by Size", fontsize=16)
g.set_axis_labels("Operation Type", "Duration (ms) - Log Scale")
g.figure.subplots_adjust(top=0.85)
plt.tight_layout()

plt.savefig("performance_comparison_all_sizes.png")
plt.show()
