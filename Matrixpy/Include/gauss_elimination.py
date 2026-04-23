from Matrixpy.Include.matrix import Matrix

class GaussianElimination(Matrix):
    def __init__(self, r=0, c=0):
        super().__init__(r, c)

    def basicPivoting(self, currIndex):
        from Matrixpy.Src.Matrix_Algorithms import basic_pivoting
        basic_pivoting(self, currIndex)

    def upperTriangularWithoutPivot(self):
        from Matrixpy.Src.Matrix_Algorithms import upper_triangular_without_pivot
        upper_triangular_without_pivot(self)

    def upperTriangularWithPivot(self):
        from Matrixpy.Src.Matrix_Algorithms import upper_triangular_with_pivot
        upper_triangular_with_pivot(self)
