from Matrixpy.Include.gauss_elimination import GaussianElimination

class SLE(GaussianElimination):
    GAUSSIAN = 0
    LU_METHOD = 1

    DOOLITTLE = 0
    CROUT = 1
    CHOLESKY = 2

    def __init__(self, r=0, c=0):
        super().__init__(r, c)

    def backSubstitutionToVec(self):
        from Matrixpy.Src.Matrix_Algorithms import back_substitution_to_vec
        return back_substitution_to_vec(self)

    def solve(self, method=GAUSSIAN, lu_m=DOOLITTLE):
        from Matrixpy.Src.Matrix_Algorithms import solve_sle
        return solve_sle(self, method, lu_m)

    def solveWithPivot(self):
        from Matrixpy.Src.Matrix_Algorithms import solve_with_pivot
        return solve_with_pivot(self)

    def solveWithoutPivot(self):
        from Matrixpy.Src.Matrix_Algorithms import solve_without_pivot
        return solve_without_pivot(self)
