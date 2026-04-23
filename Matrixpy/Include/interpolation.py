from Matrixpy.Include.matrix import Matrix

class Interpolation(Matrix):
    def __init__(self, x=None, y=None):
        if x is not None and y is not None:
            super().__init__(len(x), 2)
            self.setData(x, y)
        else:
            super().__init__(0, 0)

    def setData(self, x, y):
        from Matrixpy.Src.Interpolation import set_data
        set_data(self, x, y)

    def pointCount(self):
        return self.rows

    def getX(self):
        return [self.mat[i][0] for i in range(self.rows)]

    def getY(self):
        return [self.mat[i][1] for i in range(self.rows)]

    def evaluate(self, x):
        raise NotImplementedError("Subclasses must implement evaluate()")

    def evaluateRange(self, xMin, xMax, samples):
        raise NotImplementedError("Subclasses must implement evaluateRange()")

class Lagrange(Interpolation):
    def __init__(self, x=None, y=None):
        super().__init__(x, y)

    def evaluate(self, x):
        from Matrixpy.Src.Interpolation import evaluate_lagrange
        return evaluate_lagrange(self, x)

    def evaluateRange(self, xMin, xMax, samples):
        from Matrixpy.Src.Interpolation import evaluate_range_lagrange
        return evaluate_range_lagrange(self, xMin, xMax, samples)
