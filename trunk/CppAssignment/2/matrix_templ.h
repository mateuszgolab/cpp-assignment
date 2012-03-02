#ifndef MATRIX_TEMPL_H  //include guard
#define MATRIX_TEMPL_H

#include <iostream>  //generic IO
#include <fstream>   //file IO
#include <stdexcept> //provides exceptions
#include "vector_templ.h"  //we use Vector<T> in Matrix<T> implementation
#include <sstream>

//forward declarations - needed to tell the compiler that friends are templates
template <typename T> class Matrix;
template <typename T> Matrix<T> operator*(const Matrix<T>& m1, const Matrix<T>& m2); // operator * for matrix multiplication
template <typename T> bool operator==(const Matrix<T>& m1, const Matrix<T>& m2); // operator ==  for matrix comparison
template <typename T> std::istream& operator>>(std::istream& is, Matrix<T>& m);// keyboard input
template <typename T> std::ostream& operator<<(std::ostream& os, const Matrix<T>& m);// screen output
template <typename T> std::ifstream& operator>>(std::ifstream& ifs, Matrix<T>& m);// file input
template <typename T> std::ofstream& operator<<(std::ofstream& ofs, const Matrix<T>& m);// file output


template <typename T>
class Matrix {
private:
    Vector<T> v;     // Vector used to store the matrix elements
    int nrows;    // number of rows of the matrix
    int ncols;    // number of columns of the matrix

public:
    Matrix(); // default constructor, uses default constructor for v
    Matrix(int Nrows, int Ncols);  // alternate constructor

	int getNrows() const; // get the number of rows
	int getNcols() const; // get the number of cols

    T& operator() (int i, int j); //  function call overload (-,-) for assignment
    const T& operator() (int i, int j) const; // for reading matrix values

    friend Matrix<T> operator* <> (const Matrix<T>& m1, const Matrix<T>& m2); // operator * for matrix multiplication
	friend bool operator== <> (const Matrix& m1, const Matrix& m2); // operator == for matrix comparison

    friend std::istream& operator>> <>(std::istream& is, Matrix<T>& m);// keyboard input
    friend std::ostream& operator<< <>(std::ostream& os, const Matrix<T>& m);// screen output

    //the file output operator is compatible with file input operator,
    //ie. everything written can be read later.
    friend std::ifstream& operator>> <>(std::ifstream& ifs, Matrix<T>& m);// file input
    friend std::ofstream& operator<< <>(std::ofstream& ofs, const Matrix<T>& m);// file output
};


// default constructor
template <typename T>
Matrix<T>::Matrix() : v(), nrows(0), ncols(0)
{
}

// alternate constructor 
template <typename T>
Matrix<T>::Matrix(int rows, int cols) : v(rows * cols) , nrows(0), ncols(0)
{
}

// operator * for matrix multiplication
template <typename T>
Matrix<T> operator*(const Matrix<T>& m1, const Matrix<T>& m2)
{
	if(m1.getNcols() != m2.getNrows()) 
	{
		std::ostringstream ss;
	
		std::string ex = "m1 matrix has ";
		ss << m1.getNcols() ;
		ex += ss.str();
		ex += " columns";
		ss.str("");
		ex += " and m2 matrix has ";
		ss << m2.getNrows() ;
		ex += ss.str();
		ex += " rows";

		throw std::invalid_argument(ex);
		
	}

	int n = m1.getNcols();
	
	Matrix<T> m(n, n);

	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			m(i, j) = 0;
			for(int k = 0; k < n; k++)
			{
				m(i, j) += m1(i, k) * m2(k, j);
			}
		}
	}

	return m;
}

// operator == for matrix comparison
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
			if(m1(i, j) != m2(i, j)) return false;
		}
	}

	return true;
}

// keyboard input
template <typename T>
std::istream& operator>>(std::istream& is, Matrix<T>& m)
{
	int rows, cols;

    std::cout << "input the size for the matrix (rows x cols)" << std::endl;
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

// screen output - user friendly
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

// file input - raw data, compatible with file writing operator
template <typename T>
std::ifstream& operator>>(std::ifstream& ifs, Matrix<T>& m)
{
	int rows, cols;

	// read sizes from the file
    ifs >> rows >> cols;
    //check input sanity
    if((rows < 0) || (cols < 0)) throw std::invalid_argument("read error - negative matrix size");

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

// file output - raw data, comaptible with file reading operator
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

// get the number of rows
template <typename T>
int Matrix<T>::getNrows() const
{
	return nrows;
}

// get the number of cols
template <typename T>
int Matrix<T>::getNcols() const
{
	return ncols;
}

//  function call overload (-,-) for assignment
template <typename T>
T& Matrix<T>::operator() (int i, int j)
{
	if(i < 0 || i >= nrows || j < 0 || j >= ncols) throw std::out_of_range("matrix access error");
	return v[i * ncols + j];
}

// for reading matrix values
template <typename T>
const T& Matrix<T>::operator() (int i, int j) const
{
	if(i < 0 || i >= nrows || j < 0 || j >= ncols) throw std::out_of_range("matrix access error");
	return v[i * ncols + j];
}


#endif