#include"matrix.h"

using namespace std;

// default constructor (empty matrix), uses default constructor for v
Matrix::Matrix() : v(), nrows(0), ncols(0) 
{
}

// alternate constructor , creates NRows x Ncols matrix 
// param Nrows - number of rows
// param Ncols - number of columns
// throwing exceptions from constructor is a bad practice, so no exception is thrown here, however negative values will be corrected
Matrix::Matrix(int rows, int cols) : v((rows<0?0:rows) * (cols<0?0:cols)), nrows(rows<0?0:rows), ncols(cols<0?0:cols)
{
}

// get the number of rows
// returns number of rows
int Matrix::getNrows() const
{
	return nrows;
}

// get the number of columns
// returns number of columns
int Matrix::getNcols() const
{
	return ncols;
}

// operator overloaded for accessing modifable elements
// param i - row
// param j - columns
// throws std::out_of_range in case of accessing out of range element
// returns matrix element from i-th row and j-th column
double& Matrix::operator() (int i, int j)
{
	int index = i * ncols + j;

	if(index < 0 || index >= v.size())
		throw std::out_of_range("matrix access error");

	return v[index];
}

// operator overloaded for accessing readable elements
// param i - row
// param j - columns
// throws std::out_of_range in case of accessing out of range element
// returns matrix element from i-th row and j-th column
double Matrix::operator() (int i, int j) const
{
	int index = i * ncols + j;

	if(index < 0 || index >= v.size())
		throw std::out_of_range("matrix access error");

	return v[index];
}

// friend operator * for matrix multiplication
// param m1 - first matrix to multiply
// param m2 - second matrix to multiply
// throws exception if matrices cannot be multiplied together
// returns m1 * m2 product
Matrix operator*(const Matrix& m1, const Matrix& m2)
{
	if(m1.getNcols() != m2.getNrows()) 
	{
		string ex = "matrices cannot be multiplied together because m1 matrix has ";
		ex += Matrix::getString(m1.getNcols());
		ex += " columns and m2 matrix has ";
		ex += Matrix::getString(m2.getNrows());
		ex += " rows";

		throw invalid_argument(ex);
	}

	Matrix m(m1.getNrows(), m2.getNcols());

	for(int i = 0; i < m1.getNrows(); i++)
	{
		for(int j = 0; j < m2.getNcols(); j++)
		{
			m(i, j) = 0;
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
bool operator==(const Matrix& m1, const Matrix& m2)
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

// friend operator for keyboard input
// param is - input stream object
// param m - matrix
// throws std::invalid_argument when improper input values
// returns stream object
istream& operator>>(istream& is, Matrix& m)
{
	int rows, cols;

	cout << "input the size for the matrix (rows columns) : ";
	is >> rows >> cols;

	//check input sanity
	if((rows < 0) || (cols < 0))
		throw std::invalid_argument("read error - negative matrix size");

	if(rows == 0 && cols != 0)
		throw std::invalid_argument("read error - improper number of rows");

	if(cols == 0 && rows != 0)
		throw std::invalid_argument("read error - improper number of columns");


	// prepare the matrix to hold rows x cols elements
	m = Matrix(rows, cols);

	// input the elements
	cout << "input "<<rows * cols<<" matrix  elements"<<endl;
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
ostream& operator<<(ostream& os, const Matrix& m)
{
	if (m.getNcols() > 0 && m.getNrows() > 0)
	{
		os << "The matrix elements are" << endl;
		for (int i = 0; i < m.getNrows(); i++) 
		{
			for(int j = 0; j < m.getNcols(); j++)
			{
				os << m(i, j)  << " ";
			}

			os << endl;
		}
	}
	else
	{
		os << "Matrix is empty." << endl;
	}
	return os;
}

// overloaded friend operator for file input 
// param ifs - input file stream object
// throws std::invalid_argument exception when improper input values
// returns stream object
ifstream& operator>>(ifstream& ifs, Matrix& m)
{
	int rows, cols;

	ifs >> rows >> cols;

	//check input sanity
	if((rows < 0) || (cols < 0))
		throw std::invalid_argument("read error - negative matrix size");

	if(rows == 0 && cols != 0)
		throw std::invalid_argument("read error - improper number of rows");

	if(cols == 0 && rows != 0)
		throw std::invalid_argument("read error - improper number of columns");


	// prepare the matrix to hold rows x cols elements
	m = Matrix(rows, cols);

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
ofstream& operator<<(ofstream& ofs, const Matrix& m)
{
	//put matrix size in first line (even if it is empty)
	ofs << m.getNrows() <<" "<< m.getNcols() << endl;
	//put data in second line (if empty matrix nothing will be put)
	for (int i = 0; i < m.getNrows(); i++) 
	{
		for(int j = 0; j < m.getNcols(); j++)
		{
			ofs << m(i, j)  <<  " ";
		}
		ofs << endl;
	}
	return ofs;
}

// Converts integer to string
// param i - integert to convert
// returns string object
string Matrix::getString(int i)
{
	// object to manipulate on strings
	std::ostringstream ss;		
	ss << i;

	return ss.str();
}
