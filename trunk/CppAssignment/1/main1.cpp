#include <fstream>  //file io
#include <iostream> //std io 
#include "matrix.h"

using namespace std;

int main()
{ 
    try
    {
        //make two 3x3 matrices
    	Matrix m1(3,3), m2(3,3);
        
        //make m1 an identity matrix
        for(int i=0;i<3;i++) 
			for(int j=0;j<3;j++) m1(i,j) = i==j?1:0;

        //put some values into m2
        for(int i=0;i<3;i++) 
			for(int j=0;j<3;j++) m2(i,j) = i*5+j*7;

        //multiply
        Matrix m3 = m1 * m2;

        //check if m3 is the same as m2
		if (m3 == m2) std::cout << "correct matrix multiplication\n";
		else std::cout << "error in multplication\n";

        //try to do something stupid:
        Matrix m4(2,2);
        try
        {
            m4 * m1; //multiplying incompatible size matrices
        }
        catch (std::invalid_argument &e)
        {
            std::cout << "You have done something stupid ;-)" << std::endl;
            std::cerr << "Type: " << typeid(e).name() << std::endl;
            std::cerr << "What: " << e.what() << std::endl;
        }

        //output the m3 matrix
        std::cout << m3;

    }
    catch (std::exception& e)
    {
        cerr << "std::exception caught" << endl;
        cerr << "Type: " << typeid(e).name() << endl;
        cerr << "What: " << e.what() << endl;
    }

    getc(stdin); //just that the console doesn't dissapear if program run by doubleclick
    return 0;
}
