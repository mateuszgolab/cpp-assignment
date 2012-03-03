#include "IterativeSolver.h"

// Solves set of equations using Jacobi iterative method
// param a - coefficients matrix
// param b - data vector
// param n - problem size
// param maxIterations - number of iterations
// returns solution vector
Vector IterativeSolver::jacobi(const Matrix a,const Vector b, int n, int maxIterations)
{
	Vector x[2];
	x[0] = Vector(n);
	x[1] = Vector(n);

	for(int i = 0; i < n; i++)
		x[0][i] = 0.0;

	double sum;
	int k;

	for(k = 0; k < maxIterations; k++)
	{
		for(int i = 0; i < n; i++)
		{
			sum = 0.0;
			for(int j = 0; j < n; j++)
			{
				if(j == i) continue;
				sum += a(i,j) * x[k % 2][j];
			}

			x[(k+1) % 2][i] = (b[i] - sum) / a(i, i);
		}
	}

	return x[k % 2]; 
}

// Solves set of equations using Gauss-Siedel iterative method
// The rate of convergence is faster than that of the Jacobi method
// param a - coefficients matrix
// param b - data vector
// param n - problem size
// param maxIterations - number of iterations
// returns solution vector
Vector IterativeSolver::gaussSiedel(const Matrix a,const Vector b, int n, int maxIterations)
{
	Vector x(n);

	for(int i = 0; i < n; i++)
		x[i] = 0.0;

	double sum;
	int k;

	for(k = 0; k < maxIterations; k++)
	{
		for(int i = 0; i < n; i++)
		{
			sum = 0.0;
			for(int j = 0; j < n; j++)
			{
				if(j == i) continue;
				sum += a(i,j) * x[j];
			}

			x[i] = (b[i] - sum) / a(i, i);
		}
	}

	return x; 
}