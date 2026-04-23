from Matrixpy.Include.matrix import Matrix

class CurveFitting(Matrix):
    def __init__(self, x=None, y=None):
        if x is not None and y is not None:
            super().__init__(len(x), 2)
            self.setData(x, y)
        else:
            super().__init__(0, 0)

    def setData(self, x, y):
        from Matrixpy.Src.CurveFitting import set_data
        set_data(self, x, y)

    def getXi(self):
        return [self.mat[i][0] for i in range(self.rows)]

    def getFi(self):
        return [self.mat[i][1] for i in range(self.rows)]

    def pointCount(self):
        return self.rows

    def fit(self):
        raise NotImplementedError("Subclasses must implement fit()")

    def evaluate(self, x):
        raise NotImplementedError("Subclasses must implement evaluate()")

    def rms(self):
        raise NotImplementedError("Subclasses must implement rms()")

    def evaluateRange(self, xMin, xMax, samples):
        from Matrixpy.Src.CurveFitting import evaluate_range_curve
        return evaluate_range_curve(self, xMin, xMax, samples)

class LeastSquares(CurveFitting):
    def __init__(self, x=None, y=None):
        super().__init__(x, y)
        self.a = 0.0 # slope
        self.b = 0.0 # intercept

    def fit(self):
        from Matrixpy.Src.CurveFitting import fit_least_squares
        fit_least_squares(self)

    def evaluate(self, x):
        from Matrixpy.Src.CurveFitting import evaluate_least_squares
        return evaluate_least_squares(self, x)

    def rms(self):
        from Matrixpy.Src.CurveFitting import rms_least_squares
        return rms_least_squares(self)

    def getSlope(self):
        return self.a

    def getIntercept(self):
        return self.b

    def printReport(self):
        from Matrixpy.Src.CurveFitting import print_report_least_squares
        print_report_least_squares(self)
