# Linear Cycle Class

The `linear_cycle` class is designed to handle the results of a servo motion cycle in the XYZ dimensions. It is typically used with a cycle time of 0.001 seconds. The primary purpose of this class is to check if the XYZ motion exceeds the maximum acceleration for each axis. If it does, the class sets a new target position for XYZ, ensuring that the maximum acceleration for each axis is satisfied.

## Table of Contents
- [Introduction](#introduction)
- [Usage](#usage)
- [Class Methods](#class-methods)
- [Example](#example)
- [License](#license)

## Introduction

This class provides a solution for handling servo motion cycles in the XYZ dimensions. It checks for excessive motion and adjusts the target position to meet maximum acceleration criteria for each axis.

## Usage

To use the `linear_cycle` class, include the "linear_cycle.h" header in your C++ project. The class provides methods to set cycle values, calculate results, and retrieve the outcome of the motion cycle.

## Class Methods

### `linear_cycle::linear_cycle()`

Constructor for the `linear_cycle` class.

### `linear_cycle::set_debug(bool state)`

Enable or disable debug mode for additional information during calculations.

### `linear_cycle::set_cycle_values(...)`

Set the initial values for velocity, displacement, acceleration, and cycle time.

### `linear_cycle::calculate()`

Perform calculations based on the provided cycle values.

### `linear_cycle::get_cycle_results(...)`

Retrieve the calculated displacement, velocity, and acceleration for each dimension.

### Other Private Methods

The class includes several private methods used for specific calculations and internal operations.

## Example

```cpp
#include "linear_cycle.h"

int main() {
    linear_cycle cycle;

    // Set cycle values
    cycle.set_cycle_values(/* provide initial values for velocity, displacement, acceleration, and cycle time */);

    // Perform calculations
    cycle.calculate();

    // Retrieve and print results
    double displacement_x, velocity_end_x, acceleration_x;
    cycle.get_cycle_results(displacement_x, velocity_end_x, acceleration_x, /* ... other parameters for y and z dimensions */);

    return 0;
}
