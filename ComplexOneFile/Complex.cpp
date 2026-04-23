#include <iostream>

using namespace std;
class myComplex
{
public:
        //data members
        float a,b,c;

        //Constructors

        //(1)Default Constructor
        myComplex()
        {
            cout<<"\n i am a default constructor in myComplex class....\n";
        };

        //(2)Parameterized Constructor
        myComplex(float x , float y)
        {
            cout<<"\n i am a parameterized constructor in myComplex class....\n";
            a = x;
            b = y;
        }

        myComplex(float x , float y, float z)
        {
            cout<<"\n i am a parameterized constructor with 3 parameters in myComplex class....\n";
            a = x;
            b = y;
            c = z;
        }
            myComplex add(myComplex tmp)
            {
                //"Function to add two complex numbers"
                cout << "1) Addition a:: " << a << " \t b :: " << b << endl;

                myComplex ans;
                ans.a = a + tmp.a;
                ans.b = b + tmp.b;
                return ans;
            }
};

int main()
{
    cout << "\n This is MyComplex class demo!" << endl;
    myComplex c1(1 , 2) , c2(1 , 3) , c3(0 , 0); // Object
    c3 = c1.add(c2);
    cout << "\n c3.a :: " << c3.a << "\t c3.b :: " << c3.b << endl;
    return 0;
}