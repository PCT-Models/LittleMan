# -*- coding: utf-8 -*-
"""
Created on Thu Aug  8 20:51:40 2024
Inverse Kinematics Program
@author: gtaus
"""

import numpy as np
import matplotlib.pyplot as plt

#%% Inverse Kinematics



# Arm lengths
L1 = 2.0  # Length of the first link
L2 = 1.5  # Length of the second link

# Target point in space (desired end-effector position)
target_x = 2.5
target_y = 1.5

# Inverse Kinematics calculations
def inverse_kinematics(x, y):
    # Calculate the distance from the base to the target point
    r = np.sqrt(x**2 + y**2)
    
    # Check if the target is reachable
    if r > (L1 + L2) or r < abs(L1 - L2):
        print("Target point is out of reach.")
        return None
    
    # Calculate the angle for the first joint (theta1)
    cos_theta2 = (x**2 + y**2 - L1**2 - L2**2) / (2 * L1 * L2)
    sin_theta2 = np.sqrt(1 - cos_theta2**2)
    
    theta2 = np.arctan2(sin_theta2, cos_theta2)
    
    k1 = L1 + L2 * cos_theta2
    k2 = L2 * sin_theta2
    
    theta1 = np.arctan2(y, x) - np.arctan2(k2, k1)
    
    return np.degrees(theta1), np.degrees(theta2)

# Get the joint angles
angles = inverse_kinematics(target_x, target_y)

if angles:
    theta1, theta2 = angles
    print(f"Joint angles: theta1 = {theta1:.2f} degrees, theta2 = {theta2:.2f} degrees")

    # Forward Kinematics to determine the positions of each joint
    x1 = L1 * np.cos(np.radians(theta1))
    y1 = L1 * np.sin(np.radians(theta1))
    x2 = x1 + L2 * np.cos(np.radians(theta1 + theta2))
    y2 = y1 + L2 * np.sin(np.radians(theta1 + theta2))

    # Plot the robotic arm
    plt.figure()
    plt.plot([0, x1, x2], [0, y1, y2], marker='o', color='b')
    plt.xlim(-L1 - L2 - 1, L1 + L2 + 1)
    plt.ylim(-L1 - L2 - 1, L1 + L2 + 1)
    plt.title('2-DOF Robotic Arm')
    plt.xlabel('X-axis')
    plt.ylabel('Y-axis')
    plt.grid(True)
    plt.show()

#%% More better Code

# Arm lengths
L1 = 2.0  # Length of the first link
L2 = 1.5  # Length of the second link

# Initial position of the end effector
initial_x = 1
initial_y = -1

# Define multiple target points for the end effector
targets = [(2.5, 1.5), (3.0, 0.0), (0.5, 2.0), (2.0, -2.0), (1.5, 1.5)]

# Inverse Kinematics calculations
def inverse_kinematics(x, y):
    r = np.sqrt(x**2 + y**2)
    if r > (L1 + L2) or r < abs(L1 - L2):
        print("Target point is out of reach.")
        return None
    
    cos_theta2 = (x**2 + y**2 - L1**2 - L2**2) / (2 * L1 * L2)
    sin_theta2 = np.sqrt(1 - cos_theta2**2)
    
    theta2 = np.arctan2(sin_theta2, cos_theta2)
    
    k1 = L1 + L2 * cos_theta2
    k2 = L2 * sin_theta2
    
    theta1 = np.arctan2(y, x) - np.arctan2(k2, k1)
    
    return np.degrees(theta1), np.degrees(theta2)

# Lists to store the trajectory of the end effector
trajectory_x = []#[initial_x]
trajectory_y = []#[initial_y]

plt.figure()
# Process each target point
for target in targets:
    target_x, target_y = target
    angles = inverse_kinematics(target_x, target_y)


    if angles:
        theta1, theta2 = angles
        
        # Calculate the new position of the end effector
        x1 = L1 * np.cos(np.radians(theta1))
        y1 = L1 * np.sin(np.radians(theta1))
        x2 = x1 + L2 * np.cos(np.radians(theta1 + theta2))
        y2 = y1 + L2 * np.sin(np.radians(theta1 + theta2))
        
        # Append the new position to the trajectory lists
        trajectory_x.append(x2)
        trajectory_y.append(y2)
        plt.plot([0, x1, x2], [0, y1, y2], marker='o', color='b')

# Plot the trajectory of the end effector

plt.plot(trajectory_x, trajectory_y, 'or')
plt.scatter([t[0] for t in targets], [t[1] for t in targets], color='blue', label='Targets')
plt.xlim(-L1 - L2 - 1, L1 + L2 + 1)
plt.ylim(-L1 - L2 - 1, L1 + L2 + 1)
plt.title('End Effector Trajectory')
plt.xlabel('X-axis')
plt.ylabel('Y-axis')
plt.grid(True)
# plt.legend(['End Point','Targets'])
plt.show()
