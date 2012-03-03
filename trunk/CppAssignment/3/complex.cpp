#include "complex.h"

using namespace std;


// sets real part
// param re - real part to set
// returns modified complex
// inline method
inline Complex & Complex::setReal(double re)
{
	this->re = re;
	return *this;
}

// sets imaginary part
// param im - imaginary part to set
// returns modified complex
// inline method
inline Complex & Complex::setImag(double im)
{
	this->im = im;
	return *this;
}

// inline, overloaded += operator  
// param c - complex to add
// returns result of addition
inline Complex& Complex::operator+=(const Complex& c)
{
	this->re += c.getReal();
	this->im += c.getImag();

	return *this;
}

// inline, overloaded = operator  
// param c - complex to assign
// returns assigned object
inline Complex& Complex::operator=(const Complex& c)
{
	if(*this == c) return *this;

	this->re = c.getReal();
	this->im = c.getImag();

	return *this;
}


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
