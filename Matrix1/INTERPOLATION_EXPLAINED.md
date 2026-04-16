# Interpolation Module Documentation

## 1. What is Interpolation?
Interpolation is a numerical method used to estimate unknown values that fall between known data points. In computational mathematics, interpolation is often used to construct new data points within the range of a discrete set of known data points.

## 2. What is a Header File (.hpp)?
A header file (with extension `.hpp` or `.h`) in C++ contains class declarations, function prototypes, and macro definitions. It is used to declare the structure and interface of classes and functions, separating them from their implementation (which is usually in `.cpp` files).

## 3. Interpolation.hpp: Structure and Inheritance
- **Purpose:** Declares the `Interpolation` base class and the `Lagrange` derived class for interpolation algorithms.
- **Inheritance:**
  - `Interpolation` inherits from `Matrix`, so it gets all matrix data storage and methods.
  - `Lagrange` inherits from `Interpolation` and implements the Lagrange interpolation algorithm.
- **Data Members:**
  - No new data members for storing x/y points; uses the `mat` member from `Matrix` (each row: `[x, y]`).
- **New Functions:**
  - `setData(x, y)`: Loads x and y data into the matrix.
  - `pointCount()`: Returns the number of interpolation points.
  - `getX()`, `getY()`: Extracts x or y values from the matrix.
  - `evaluate(x)`: (pure virtual) Evaluates the interpolation at a given x.
  - `evaluateRange(xMin, xMax, samples)`: (pure virtual) Evaluates the interpolation at multiple points.

## 4. Interpolation.cpp: Implementation
- Implements all methods declared in the header.
- Uses the inherited `mat` (from `Matrix`) to store and access x/y data.
- Validates input (checks for size match and unique x values).
- `Lagrange::evaluate(x)`: Computes the Lagrange polynomial at x using the matrix data.

## 5. How Does Inheritance Work Here?
- `Matrix` provides all matrix storage and utility functions.
- `Interpolation` extends `Matrix` to provide an interface for interpolation algorithms, but does not add new storage for points.
- `Lagrange` implements the actual interpolation logic.

## 6. Example: How It Works in Main
Suppose you want to interpolate points using Lagrange:

```cpp
#include "Lagrange.hpp"
#include <vector>
#include <iostream>

int main() {
    std::vector<long double> x = {1, 2, 3};
    std::vector<long double> y = {2, 4, 6};
    Lagrange lag(x, y);
    long double value = lag.evaluate(2.5); // Interpolated value at x=2.5
    std::cout << "Interpolated value: " << value << std::endl;
    return 0;
}
```
- The `Lagrange` object stores points in the inherited matrix.
- You can add more interpolation types by inheriting from `Interpolation` and implementing the required methods.

## 7. Summary Table
| Class         | Inherits From | Data Storage | Key Methods                |
|---------------|---------------|--------------|----------------------------|
| Matrix        | BaseMatrix    | mat          | Matrix operations          |
| Interpolation | Matrix        | mat          | setData, getX, getY, ...   |
| Lagrange      | Interpolation | mat          | evaluate, evaluateRange    |

---
This structure ensures code reuse, clarity, and extensibility for future interpolation algorithms.
