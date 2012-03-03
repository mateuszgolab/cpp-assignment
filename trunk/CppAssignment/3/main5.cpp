//#include <fstream>
//#include <iostream>
//
//#include "complex.h"
//#include "matrix_templ.h"
//
//int main()
//{
//    try
//    {
//
//    	Matrix<Complex> m1, m2;
//
//	    std::cin >> m1;  // input matrix m1 from keyboard (as user wants)
//
//	    std::ifstream ifs("complex_matrix.dat");
//	    std::ofstream ofs("result.dat");
// 
//		
//	    ifs >> m2;   // read matrix m2 from the file matrix.dat
//	  
//	    Matrix<Complex> m3;
//
//	    m3 = m1*m2;    // multiply them together, store in m3
//
//	    std::cout << m3;   // output m3 to the screen
//
//	    ofs << m3;   // output m3 to file result.dat	   
//    }
//    catch (std::exception& e)
//    {
//        std::cerr << "std::exception caught" << std::endl;
//        std::cerr << "Type: " << typeid(e).name() << std::endl;
//        std::cerr << "What: " << e.what() << std::endl;
//    }
//
//    std::getc(stdin); //just that the console doesn't dissapear if program run by doubleclick
//    return 0;
//}
