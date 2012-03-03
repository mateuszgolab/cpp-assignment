#ifndef MATRIX_H  //include guard
#define MATRIX_H

#include <iostream>  //generic IO
#include <fstream>   //file IO
#include <stdexcept> //provides exceptions
#include "vector.h"  //we use Vector in Matrix implementation
#include <string>	// provides string 
#include <sstream>  // provides ostringstream


class Matrix {
private:
    Vector v;     // Vector used to store the matrix elements
    int nrows;    // number of rows of the matrix
    int ncols;    // number of columns of the matrix

	//=========== added methods  ========================================
	static std::string getString(int i); // converts int to string object
	//====================================================================

public:
    Matrix(); // default constructor, uses default constructor for v
    Matrix(int Nrows, int Ncols);  // alternate constructor

	int getNrows() const; // get the number of rows
	int getNcols() const; // get the number of cols

    double& operator() (int i, int j); //  function call overload (-,-) for assignment
    double operator() (int i, int j) const; // for reading matrix values


    friend Matrix operator*(const Matrix& m1, const Matrix& m2); // operator * for matrix multiplication
	friend bool operator==(const Matrix& m1, const Matrix& m2); // operator == for matrix comparison
    friend std::istream& operator>>(std::istream& is, Matrix& m);// keyboard input
    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);// screen output

    //the file output operator is compatible with file input operator,
    //ie. everything written can be read later.
    friend std::ifstream& operator>>(std::ifstream& ifs, Matrix& m);// file input
    friend std::ofstream& operator<<(std::ofstream& ofs, const Matrix& m);// file output
};

// Note: There is no need for a copy constructor or 
// assignment operator in the Matrix class since the 
// compiler version will work OK. It will copy/assign 
// the values of nrows and ncols and call the Vector copy 
// constructor/assignment operator automatically for the 
// Vector part v inside the Matrix.

#endif