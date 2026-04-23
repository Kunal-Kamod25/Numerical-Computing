from Matrixpy.Include.eigenvalues import Eigenvalues

class Gershgorin(Eigenvalues):
    def __init__(self, r_or_A=0, c=0):
        super().__init__(r_or_A, c)

    def disks(self):
        from Matrixpy.Src.Eigenvalues import disks
        return disks(self)

    def realBounds(self):
        from Matrixpy.Src.Eigenvalues import real_bounds
        return real_bounds(self)
