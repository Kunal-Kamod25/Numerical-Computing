"""
MyComplex Class Demo
--------------------
Demonstrates basic complex number arithmetic using the MyComplex class.
Includes addition, subtraction, multiplication, division, conjugation, and norm.
"""

from Include.complex_number import MyComplex

def main():
    print("\n--- MyComplex Class Demo ---")

    # --- Step 1: Initialization ---
    # c1 = 1 + 2i, c2 = 1 + 3i
    c1 = MyComplex(1, 2)
    c2 = MyComplex(1, 3)
    c3 = MyComplex()

    print(f"Number 1: {c1.a} + {c1.b}i")
    print(f"Number 2: {c2.a} + {c2.b}i")

    # --- Step 2: Arithmetic Operations ---
    
    # 1) Addition: (a+bi) + (c+di) = (a+c) + (b+d)i
    c3 = c1.add(c2)
    print(f"\nAddition:       {c3.a} + {c3.b}i")

    # 2) Subtraction: (a+bi) - (c+di) = (a-c) + (b-d)i
    sub = c1.subtract(c2)
    print(f"Subtraction:    {sub.a} + ({sub.b}i)")

    # 3) Multiplication: (a+bi)(c+di) = (ac-bd) + (ad+bc)i
    mult = c1.multiply(c2)
    print(f"Multiplication: {mult.a} + {mult.b}i")

    # 4) Division: Uses the conjugate of the denominator
    div = c1.divide(c2)
    print(f"Division:       {div.a:.4f} + {div.b:.4f}i")

    # --- Step 3: Utility Methods ---

    # 5) Complex Conjugate: a + bi -> a - bi
    conj = c1.complexConjugate()
    print(f"\nConjugate of c1: {conj.a} + ({conj.b}i)")

    # 6) Norm (Magnitude): sqrt(a^2 + b^2)
    print(f"Norm of c1:      {c1.norm():.4f}")

if __name__ == "__main__":
    main()
