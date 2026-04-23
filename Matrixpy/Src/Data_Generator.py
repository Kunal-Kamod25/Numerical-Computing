import os
import random
import math

class DataGenerator:
    """
    Utility class to generate various types of mathematical test data for the Matrixpy library.
    """

    @staticmethod
    def save_matrix(matrix, filename, folder):
        """Saves a 2D matrix to a text file in the specified folder."""
        os.makedirs(folder, exist_ok=True)
        filepath = os.path.join(folder, filename)
        with open(filepath, 'w') as f:
            for row in matrix:
                f.write('    '.join(f"{val:.4f}" for val in row) + '\n')
        print(f"Saved: {filepath}")

    @staticmethod
    def generate_random_matrix(rows, cols, val_range=(-10, 10)):
        """Generates a random matrix of given dimensions."""
        return [[random.uniform(*val_range) for _ in range(cols)] for _ in range(rows)]

    @staticmethod
    def generate_symmetric_matrix(n, val_range=(-10, 10)):
        """Generates a random symmetric matrix."""
        matrix = [[0.0] * n for _ in range(n)]
        for i in range(n):
            for j in range(i, n):
                val = random.uniform(*val_range)
                matrix[i][j] = val
                matrix[j][i] = val
        return matrix

    @staticmethod
    def generate_identity_matrix(n):
        """Generates an n x n Identity matrix."""
        return [[1.0 if i == j else 0.0 for j in range(n)] for i in range(n)]

    @staticmethod
    def generate_singular_matrix(n):
        """Generates an n x n singular matrix (one row is a multiple of another)."""
        matrix = DataGenerator.generate_random_matrix(n, n)
        if n > 1:
            # Make the second row a multiple of the first
            factor = random.uniform(0.5, 2.0)
            for j in range(n):
                matrix[1][j] = matrix[0][j] * factor
        return matrix

    @staticmethod
    def generate_diag_dominant_system(n, val_range=(-5, 5)):
        """
        Generates an n x (n+1) augmented matrix that is strictly diagonally dominant.
        Ensures |A[i][i]| > Sum(|A[i][j]| for j != i).
        """
        matrix = []
        for i in range(n):
            row = [random.uniform(*val_range) for _ in range(n)]
            # Calculate sum of absolute values of non-diagonal elements
            off_diag_sum = sum(abs(row[j]) for j in range(n) if j != i)
            # Set diagonal to be greater than this sum
            row[i] = (off_diag_sum + random.uniform(1, 5)) * (1 if random.random() > 0.5 else -1)
            # Add a random RHS value
            row.append(random.uniform(*val_range))
            matrix.append(row)
        return matrix

    @staticmethod
    def generate_hilbert_system(n):
        """
        Generates an n x (n+1) augmented matrix based on the Hilbert Matrix (H_ij = 1/(i+j-1)).
        This is notoriously ill-conditioned.
        """
        matrix = []
        for i in range(1, n + 1):
            row = [1.0 / (i + j - 1) for j in range(1, n + 1)]
            # Add a dummy RHS (Sum of row elements for a solution of all 1s)
            row.append(sum(row))
            matrix.append(row)
        return matrix

    @staticmethod
    def generate_polynomial_data(n, coeffs):
        """
        Generates n points (x, y) based on a polynomial: y = c0 + c1*x + c2*x^2 ...
        Used for Interpolation testing.
        """
        data = []
        for i in range(n):
            x = float(i)
            y = sum(c * (x**j) for j, c in enumerate(coeffs))
            data.append([x, y])
        return data

    @staticmethod
    def generate_noisy_linear_data(n, slope, intercept, noise_std=0.5):
        """
        Generates n points (x, y) for linear regression with Gaussian noise.
        Used for Curve Fitting testing.
        """
        data = []
        for i in range(n):
            x = float(i)
            # y = ax + b + noise
            y = (slope * x) + intercept + random.gauss(0, noise_std)
            data.append([x, y])
        return data

if __name__ == "__main__":
    # Self-test
    gen = DataGenerator()
    mat = gen.generate_diag_dominant_system(3)
    gen.save_matrix(mat, "gen_test_3x3.txt", "Matrixpy/Inputs/SLE")
