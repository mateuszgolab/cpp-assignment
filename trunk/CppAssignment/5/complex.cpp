#include "complex.h"

using namespace std;



// overloaded friend operator for screen output , comaptible with file reading operator
// param os - screen output stream object
// param c - complex number
// returns stream object
ostream& operator<<(ostream& os, const Complex& c)
{
	os<<c.getReal()<<" ";

	if(c.getImag() > 0) 
	{
		os<<"+";
	}

	os<<c.getImag()<<"i ";

	return os;
}

// overloaded friend operator for keyboard input 
// param is - keyboard input stream object
// param c - complex number
// returns stream object
istream& operator>>(istream& is, Complex& c)
{
	double re, im;
	cout<<"Input real and imaginary : ";
	is>>re>>im;
	c.setReal(re);
	c.setImag(im);

	return is;
}

// overloaded friend operator for file output 
// param ofs - file output stream object
// param c - complex number
// returns stream object
ofstream& operator<<(ofstream& ofs, const Complex& c)
{
	ofs<<c.getReal()<<" "<<c.getImag();

	return ofs;
}

// overloaded friend operator for file input 
// param ifs - file input stream object
// param c - complex number
// returns stream object
ifstream& operator>>(ifstream& ifs, Complex& c)
{
	double re, im;
	ifs>>re>>im;

	c.setReal(re);
	c.setImag(im);

	return ifs;
}
