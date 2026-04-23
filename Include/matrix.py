class Matrix:
    def __init__(self, rows=0, cols=0):
        self.rows = rows
        self.cols = cols
        self.mat = [[0.0 for _ in range(cols)] for _ in range(rows)]
        self.solution_vec = []

    def get(self, i, j):
        return self.mat[i][j]

    def set(self, i, j, value):
        self.mat[i][j] = float(value)

    def is_square(self):
        return self.rows == self.cols
