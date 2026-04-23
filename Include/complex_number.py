import math

class MyComplex:
    def __init__(self, x=0, y=0, z=0):
        # Mirroring C++ constructors
        if x == 0 and y == 0 and z == 0:
            print("\n i am a default constructor in MyComplex class....")
        elif z == 0:
            print("\n i am a parameterized constructor in MyComplex class....")
        else:
            print("\n i am a parameterized constructor with 3 parameters in MyComplex class....")
        
        self.a = float(x)
        self.b = float(y)
        self.c = float(z)

    def add(self, tmp):
        """Function to add two complex numbers"""
        ans = MyComplex()  # Calls default constructor
        ans.a = self.a + tmp.a
        ans.b = self.b + tmp.b
        return ans

    def subtract(self, tmp):
        ans = MyComplex()
        ans.a = self.a - tmp.a
        ans.b = self.b - tmp.b
        return ans

    def multiply(self, tmp):
        # Formula: (a+bi)(c+di) = (ac-bd) + (ad+bc)i
        ans = MyComplex()
        ans.a = (self.a * tmp.a) - (self.b * tmp.b)
        ans.b = (self.a * tmp.b) + (self.b * tmp.a)
        return ans

    def divide(self, tmp):
        denominator = (tmp.a * tmp.a) + (tmp.b * tmp.b)
        ans = MyComplex()
        if denominator == 0:
            print("Error: Division by zero!")
            return ans
        ans.a = ((self.a * tmp.a) + (self.b * tmp.b)) / denominator
        ans.b = ((self.b * tmp.a) - (self.a * tmp.b)) / denominator
        return ans

    def complexConjugate(self):
        # Conjugate of a + bi is a - bi
        return MyComplex(self.a, -self.b)

    def norm(self):
        # Norm (Magnitude) is sqrt(a^2 + b^2)
        return math.sqrt((self.a * self.a) + (self.b * self.b))
