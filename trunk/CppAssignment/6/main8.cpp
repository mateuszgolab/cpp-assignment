#include "IterativeSolver.h"
#include <iomanip>

using namespace std;

int main()
{
	try
	{
		Matrix a;						// coefficient matrix
		Vector b;						// data vector
		int n = 0;						// problem size
		int maxIter = 0;				// iteration number

		ifstream ifs("input_data.dat"); //file stream with input data

		ifs>>a>>b>>n>>maxIter;

		if(n < 0)
			throw invalid_argument("input data error - negative problem size");
		if(a.getNcols() != a.getNrows() || a.getNcols() != b.size() || b.size() != n) 
			throw invalid_argument("input data error - wrong data sizes");
		if(maxIter < 0) 
			throw invalid_argument("input data error - negative iteration number");

		Vector x = IterativeSolver::jacobi(a, b, n, maxIter);
		cout<<"Jacobi method's result after "<<maxIter<<" iterations"<<endl;
		cout<<fixed<<setprecision(6)<<x<<endl;

		x = IterativeSolver::gaussSiedel(a, b, n, maxIter);
		cout<<"Gauss-Siedel method's result after "<<maxIter<<" iterations"<<endl;
		cout<<fixed<<setprecision(6)<<x;


	}
	catch (exception& e)
	{
		cerr << "exception caught" << endl;
		cerr << "Type: " << typeid(e).name() << endl;
		cerr << "What: " << e.what() << endl;
	}

	getc(stdin); //just that the console doesn't dissapear if program run by doubleclick
	return 0;
}