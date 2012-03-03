#ifndef MATRIX_TEMPL_INHERIT_H  //include guard
#define MATRIX_TEMPL_INHERIT_H

#include <iostream>  //generic IO
#include <fstream>   //file IO
#include <stdexcept> //provides exceptions
#include "vector_templ.h"  //we use Vector<T> in Matrix<T> implementation
#include <string>	// provides string 
#include <sstream>  // provides ostringstream

//forward declarations - needed to tell the compiler that friends are templates
template <typename T> class Matrix;
template <typename T> Matrix<T> operator*(const Matrix<T>& m1, const Matrix<T>& m2); // operator * for matrix multiplication
template <typename T> bool operator==(const Matrix<T>& m1, const Matrix<T>& m2); // operator ==  for matrix comparison
template <typename T> std::istream& operator>>(std::istream& is, Matrix<T>& m);// keyboard input
template <typename T> std::ostream& operator<<(std::ostream& os, const Matrix<T>& m);// screen output
template <typename T> std::ifstream& operator>>(std::ifstream& ifs, Matrix<T>& m);// file input
template <typename T> std::ofstream& operator<<(std::ofstream& ofs, const Matrix<T>& m);// file output


template <typename T>
class Matrix : public Vector<T> {
private:
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

    T& operator() (int i, int j); //  function call overload (-,-) for assignment
    const T& operator() (int i, int j) const; // for reading matrix values

    friend Matrix<T> operator* <> (const Matrix<T>& m1, const Matrix<T>& m2); // operator * for matrix multiplication
	friend bool operator==(const Matrix<T>& m1, const Matrix<T>& m2); // operator ==  for matrix comparison

    friend std::istream& operator>> <>(std::istream& is, Matrix<T>& m);// keyboard input
    friend std::ostream& operator<< <>(std::ostream& os, const Matrix<T>& m);// screen output

    //the file output operator is compatible with file input operator,
    //ie. everything written can be read later.
    friend std::ifstream& operator>> <>(std::ifstream& ifs, Matrix<T>& m);// file input
    friend std::ofstream& operator<< <>(std::ofstream& ofs, const Matrix<T>& m);// file output
};

// ====== Implementation ============================================================================

// default constructor (empty matrix)
// uses default constructor of Vector<T>() implicitly
template <typename T>
Matrix<T>::Matrix() : nrows(0), ncols(0)
{
}

// alternate constructor , creates NRows x Ncols matrix 
// uses inherited constructor of Vector<T>(int) explicitly
// param Nrows - number of rows
// param Ncols - number of columns
// throwing exceptions from constructor is a bad practice, so no exception is thrown here, however negative values will be corrected 
template <typename T>
Matrix<T>::Matrix(int rows, int cols) : Vector<T>((rows < 0 ?0:rows) * (cols < 0 ?0:cols)), nrows(rows < 0 ?0:rows), ncols(cols < 0 ?0:cols)
{
}

// get the number of rows
// returns number of rows
template <typename T>
int Matrix<T>::getNrows() const
{
	return nrows;
}

// get the number of columns
// returns number of columns
template <typename T>
int Matrix<T>::getNcols() const
{
	return ncols;
}

// operator overloaded for accessing modifable elements
// uses inherited operator [] from Vector<T>
// param i - row
// param j - columns
// throws std::out_of_range in case of accessing out of range element
// returns matrix element from i-th row and j-th column
template <typename T>
T& Matrix<T>::operator()(int i, int j)
{
	if(i < 0 || i >= nrows || j < 0 || j >= ncols) throw std::out_of_range("matrix access error");
	return operator[](i * ncols + j);
}

// operator overloaded for accessing readable elements
// uses inherited operator [] from Vector<T>
// param i - row
// param j - columns
// throws std::out_of_range in case of accessing out of range element
// returns matrix element from i-th row and j-th column
template <typename T>
const T& Matrix<T>::operator()(int i, int j) const
{
	if(i < 0 || i >= nrows || j < 0 || j >= ncols) throw std::out_of_range("matrix access error");
	return operator[](i * ncols + j);
}

// friend operator * for matrix multiplication
// param m1 - first matrix to multiply
// param m2 - second matrix to multiply
// throws exception if matrices cannot be multiplied together
// returns m1 * m2 product
template <typename T>
Matrix<T> operator*(const Matrix<T>& m1, const Matrix<T>& m2)
{
	if(m1.getNcols() != m2.getNrows()) 
	{
		std::string ex = "matrices cannot be multiplied together because m1 matrix has ";
		ex += Matrix<T>::getString(m1.getNcols());
		ex += " columns and m2 matrix has ";
		ex += Matrix<T>::getString(m2.getNrows());
		ex += " rows";

		throw std::invalid_argument(ex);
	}

	Matrix<T> m(m1.getNrows(), m2.getNcols());

	for(int i = 0; i < m1.getNrows(); i++)
	{
		for(int j = 0; j < m2.getNcols(); j++)
		{
			m(i, j) = T(0.0);
			for(int k = 0; k < m1.getNcols(); k++)
			{
				m(i, j) += m1(i, k) * m2(k, j);
			}
		}
	}

	return m;
}

// friend operator == for matrix comparison
// param m1 - first matrix to compare
// param m2 - second matrix to compare
// returns true if matrices are equal and false if not
template <typename T>
bool operator==(const Matrix<T>& m1, const Matrix<T>& m2)
{
	if((m1.getNcols() != m2.getNcols()) || (m1.getNrows() != m2.getNrows())) return false;

	int rows = m1.getNrows();
	int cols = m1.getNcols();

	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			// comlex class has only == operator
			if(!(m1(i, j) == m2(i, j))) return false;
		}
	}

	return true;
}

// friend operator for keyboard input
// param is - input stream object
// param m - matrix
// throws std::invalid_argument when improper input values
// returns stream object
template <typename T>
std::istream& operator>>(std::istream& is, Matrix<T>& m)
{
	int rows, cols;

    std::cout << "input the size for the matrix (rows columns) : ";
    is >> rows >> cols;
    //check input sanity
    if((rows < 0) || (cols < 0)) throw std::invalid_argument("read error - negative matrix size");

    // prepare the matrix to hold rows x cols elements
	m = Matrix<T>(rows, cols);

    // input the elements
    std::cout << "input "<<rows * cols<<" matrix  elements"<< std::endl;
    for (int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			is >> m(i, j);
		}
	}

    // return the stream object
    return is;
}

// friend operator for screen output - user friendly
// param os - output stream object
// param m - matrix
// returns stream object
template <typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& m)
{
	if (m.getNcols() > 0 && m.getNrows() > 0)
	{
        os << "The matrix elements are" << std::endl;
		for (int i = 0; i < m.getNrows(); i++) 
		{
			for(int j = 0; j < m.getNcols(); j++)
			{
				os << m(i, j)  << " ";
			}
		
			os << std::endl;
		}
    }
    else
    {
        os << "Matrix is empty." << std::endl;
    }
    return os;
}

// overloaded friend operator for file input 
// param ifs - input file stream object
// throws std::invalid_argument exception when improper input values
// returns stream object
template <typename T>
std::ifstream& operator>>(std::ifstream& ifs, Matrix<T>& m)
{
	int rows, cols;

	// read sizes from the file
    ifs >> rows >> cols;
    //check input sanity
    if((rows < 0) || (cols < 0)) throw std::invalid_argument("read error - negative or  matrix size");

    // prepare the matrix to hold rows x cols elements
	m = Matrix<T>(rows, cols);

    // input the elements
    for (int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			ifs >> m(i, j);
		}
	}

    // return the stream object
    return ifs;
}

// overloaded friend operator for file output 
// param ofs - output file stream object
// param m - matrix
// returns stream object
template <typename T>
std::ofstream& operator<<(std::ofstream& ofs, const Matrix<T>& m)
{
	//put matrix size in first line (even if it is empty)
	ofs << m.getNrows() <<" "<< m.getNcols() << std::endl;
    //put data in second line (if empty matrix nothing will be put)
	for (int i = 0; i < m.getNrows(); i++) 
	{
		for(int j = 0; j < m.getNcols(); j++)
		{
			ofs << m(i, j)  <<  " ";
		}
		ofs << std::endl;
	}
    return ofs;
}


// Converts integer to string
// param i - integert to convert
// returns string object
template <typename T>
std::string Matrix<T>::getString(int i)
{
	// object to manipulate on strings
	std::ostringstream ss;		
	ss << i;

	return ss.str();
}


#endif