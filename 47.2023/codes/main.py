import numpy as np
import matplotlib.pyplot as plt

# Read the data from the simulated_data.dat file
data = np.genfromtxt('simulated_data.dat', delimiter=' ')

# Extract X and Y values from the data
x_values = data[:, 0]
y_values = data[:, 1]

# Calculate the CDF for X and Y
cdf_x = np.cumsum(np.ones_like(x_values)) / len(x_values)
cdf_y = np.cumsum(np.ones_like(y_values)) / len(y_values)

# Create a 2D grid for joint CDF
x_unique = np.unique(x_values)
y_unique = np.unique(y_values)
joint_cdf = np.zeros((len(x_unique), len(y_unique)))

for i, x in enumerate(x_unique):
    for j, y in enumerate(y_unique):
        joint_cdf[i, j] = np.mean((x_values <= x) & (y_values <= y))

# Plot the CDF of X
plt.figure()
plt.plot(sorted(x_values), cdf_x, marker='o', linestyle='-', label='CDF of X')
plt.xlabel('X values')
plt.ylabel('CDF')
plt.title('CDF of X values')
plt.grid()
plt.legend()

# Plot the CDF of Y
plt.figure()
plt.plot(sorted(y_values), cdf_y, marker='o', linestyle='-', color='green', label='CDF of Y')
plt.xlabel('Y values')
plt.ylabel('CDF')
plt.title('CDF of Y values')
plt.grid()
plt.legend()

# Plot the joint CDF using a line chart
plt.figure()
for i in range(len(x_unique)):
    plt.plot(y_unique, joint_cdf[i, :], label=f'X={x_unique[i]}')
plt.xlabel('Y values')
plt.ylabel('Joint CDF')
plt.title('Joint CDF of (X, Y)')
plt.grid()
plt.legend()

plt.show()

