#include"matrix.h"
#include<string>
#include<sstream>


using namespace std;

// default constructor, uses default constructor for v
Matrix::Matrix() : v(), nrows(0), ncols(0) 
{
}

// alternate constructor
Matrix::Matrix(int Nrows, int Ncols) : v(Nrows * Ncols) , nrows(Nrows), ncols(Ncols)
{
}

// get the number of rows
int Matrix::getNrows() const
{
	return nrows;
}

// get the number of cols
int Matrix::getNcols() const
{
	return ncols;
}

//  function call overload (-,-) for assignment
double& Matrix::operator() (int i, int j)
{
	if(i < 0 || i >= nrows || j < 0 || j >= ncols) throw std::out_of_range("matrix access error");
	return v[i * ncols + j];
}

// for reading matrix values
double Matrix::operator() (int i, int j) const
{
	if(i < 0 || i >= nrows || j < 0 || j >= ncols) throw std::out_of_range("matrix access error");
	return v[i * ncols + j];
}

// operator * for matrix multiplication
Matrix operator*(const Matrix& m1, const Matrix& m2)
{
	if(m1.getNcols() != m2.getNrows()) 
	{
		ostringstream ss;
	
		string ex = "m1 matrix has ";
		ss << m1.getNcols() ;
		ex += ss.str();
		ex += " columns";
		ss.str("");
		ex += " and m2 matrix has ";
		ss << m2.getNrows() ;
		ex += ss.str();
		ex += " rows";

		throw invalid_argument(ex);
		
	}

	int n = m1.getNcols();
	
	Matrix m(n, n);

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

// keyboard input
istream& operator>>(istream& is, Matrix& m)
{
	int rows, cols;

    cout << "input the size for the matrix (rows x cols)" << endl;
    is >> rows >> cols;
    //check input sanity
    if((rows < 0) || (cols < 0)) throw std::invalid_argument("read error - negative matrix size");

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

// screen output - user friendly
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

// file input - raw data, compatible with file writing operator
ifstream& operator>>(ifstream& ifs, Matrix& m)
{
	int rows, cols;

	// read sizes from the file
    ifs >> rows >> cols;
    //check input sanity
    if((rows < 0) || (cols < 0)) throw std::invalid_argument("read error - negative matrix size");

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

// file output - raw data, comaptible with file reading operator
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