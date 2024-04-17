import matplotlib.pyplot as plt

# Data for lazy propagation implementation (construction time, query time, update time)
lazy_propagation = {
    'Construction Time': [100, 120, 130, 140, 150],  # Example values, replace with actual data
    'Query Time': [50, 55, 60, 65, 70],  # Example values, replace with actual data
    'Update Time': [80, 85, 90, 95, 100]  # Example values, replace with actual data
}

# Data for without lazy propagation implementation (construction time, query time, update time)
no_lazy_propagation = {
    'Construction Time': [200, 220, 240, 260, 280],  # Example values, replace with actual data
    'Query Time': [70, 75, 80, 85, 90],  # Example values, replace with actual data
    'Update Time': [120, 125, 130, 135, 140]  # Example values, replace with actual data
}

# Array sizes for x-axis
array_sizes = [1000, 2000, 3000, 4000, 5000]  # Example values, replace with actual array sizes

# Plotting construction time
plt.figure(figsize=(10, 6))
plt.plot(array_sizes, lazy_propagation['Construction Time'], marker='o', label='Lazy Propagation')
plt.plot(array_sizes, no_lazy_propagation['Construction Time'], marker='o', label='Without Lazy Propagation')
plt.title('Construction Time Comparison')
plt.xlabel('Array Size')
plt.ylabel('Construction Time (nanoseconds)')
plt.legend()
plt.grid(True)

# Plotting query time
plt.figure(figsize=(10, 6))
plt.plot(array_sizes, lazy_propagation['Query Time'], marker='o', label='Lazy Propagation')
plt.plot(array_sizes, no_lazy_propagation['Query Time'], marker='o', label='Without Lazy Propagation')
plt.title('Query Time Comparison')
plt.xlabel('Array Size')
plt.ylabel('Query Time (nanoseconds)')
plt.legend()
plt.grid(True)

# Plotting update time
plt.figure(figsize=(10, 6))
plt.plot(array_sizes, lazy_propagation['Update Time'], marker='o', label='Lazy Propagation')
plt.plot(array_sizes, no_lazy_propagation['Update Time'], marker='o', label='Without Lazy Propagation')
plt.title('Update Time Comparison')
plt.xlabel('Array Size')
plt.ylabel('Update Time (nanoseconds)')
plt.legend()
plt.grid(True)

# Display all plots
plt.show()
