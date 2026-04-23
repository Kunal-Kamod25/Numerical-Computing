from Matrixpy.Include.matrix import Matrix

class LU(Matrix):
    def __init__(self, n_or_A):
        if isinstance(n_or_A, int):
            super().__init__(n_or_A, n_or_A)
            n = n_or_A
        else:
            super().__init__(n_or_A.rows, n_or_A.cols)
            # Copy data if A is Matrix
            for i in range(self.rows):
                for j in range(self.cols):
                    self.mat[i][j] = n_or_A.mat[i][j]
            n = self.rows

        self.L = Matrix(n, n)
        self.U = Matrix(n, n)
        self.P = list(range(n))

    def doolittle(self, A):
        from Matrixpy.Src.LU import doolittle
        doolittle(self, A)

    def crout(self, A):
        from Matrixpy.Src.LU import crout
        crout(self, A)

    def cholesky(self, A):
        from Matrixpy.Src.LU import cholesky
        cholesky(self, A)

    def solve(self, B):
        from Matrixpy.Src.LU import solve_system
        return solve_system(self, B)
