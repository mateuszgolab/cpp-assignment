#ifndef ITER_SLV  //include guard
#define ITER_SLV

#include "matrix.h"
#include "vector.h"

class IterativeSolver
{

public:

	// Solves set of equations using Jacobi iterative method
	// param a - coefficients matrix
	// param b - data vector
	// param n - problem size
	// param maxIterations - number of iterations
	// returns solution vector
	static Vector jacobi(const Matrix a, const Vector b, int n, int maxIterations);

	// Solves set of equations using Gauss-Siedel iterative method
	// The rate of convergence is faster than that of the Jacobi method
	// param a - coefficients matrix
	// param b - data vector
	// param n - problem size
	// param maxIterations - number of iterations
	// returns solution vector
	static Vector gaussSiedel(const Matrix a, const Vector b, int n, int maxIterations);
};

#endif

