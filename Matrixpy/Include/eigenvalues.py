from Matrixpy.Include.matrix import Matrix

class Eigenvalues(Matrix):
    def __init__(self, r_or_A=0, c=0):
        if isinstance(r_or_A, Matrix):
            super().__init__(r_or_A.rows, r_or_A.cols)
            for i in range(self.rows):
                for j in range(self.cols):
                    self.mat[i][j] = r_or_A.mat[i][j]
        else:
            super().__init__(r_or_A, c)

    def getDisks(self):
        from Matrixpy.Src.Eigenvalues import get_disks
        return get_disks(self)

    def getRealBounds(self):
        from Matrixpy.Src.Eigenvalues import get_real_bounds
        return get_real_bounds(self)
