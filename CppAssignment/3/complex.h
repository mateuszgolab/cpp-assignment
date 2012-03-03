#ifndef COMPLEX_H //include guard
#define COMPLEX_H

#include <iostream> //Generic IO operations
#include <fstream>  //File IO operations
#include <stdexcept> //provides exceptions

//needed for ofstream output
//see inside this file for explanation
#include "ofstream_workaround.h"

// The complex number class,
// with some of the functions written inline
class Complex {
private:
    double re, im;
public:
	
	// default constructor (0 + 0i)
	Complex() : re(0), im(0) {}

	// alternative constructor (re + 0i)
	// param re - real part
	Complex(double re) : re(re), im(0) {} 

	// alternative constructor (re + im i)
	// param re - real part
	// param im - imaginary part
	Complex(double re, double im) : re(re), im(im) {}

	// copy constructor
	// param c - complex number
	Complex(const Complex& c) : re(c.getReal()), im(c.getImag()) {};

	// gets real part
	// returns real part
	// inline method
	double getReal() const { return re; }

	// gets imaginary part
	// returns real part
	// inline method
	double getImag() const { return im; }

	// sets real part
	// param re - real part to set
	// returns modified complex
	// inline method
	Complex& setReal(double re);

	// sets imaginary part
	// param im - imaginary part to set
	// returns modified complex
	// inline method
	Complex& setImag(double im);

    // inline, overloaded + operator  
	// param c - complex to add
	// returns result of addition
	Complex operator+(const Complex& c) const { return Complex(re + c.getReal(), im + c.getImag()); }

	// inline, overloaded * operator  
	// param c - complex to multiply
	// returns result of multiplication
    Complex operator*(const Complex& c) const { return Complex(re * c.getReal() - im * c.getImag(), im * c.getReal() + re * c.getImag());}
   
	// inline, overloaded == operator  
	// param c - complex to compare
	// returns result of comparison
	bool operator==(const Complex& c) const { return (re == c.getReal() && im == c.getImag()); }

	// inline, overloaded += operator  
	// param c - complex to add
	// returns result of addition
	Complex& operator+=(const Complex& c);

	// inline, overloaded = operator  
	// param c - complex to assign
	// returns assigned object
    inline Complex& operator=(const Complex& c); 

    friend std::ostream& operator<<(std::ostream& os, const Complex& c); //screen output
    friend std::istream& operator>>(std::istream& is, Complex& c); //keyboard input

    //the file output operator should be compatible with file input operator,
    //ie. everything written can be read later.
    friend std::ofstream& operator<<(std::ofstream& ofs, const Complex& c); //file output
	friend std::ifstream& operator>>(std::ifstream& ifs, Complex& c); //file input
};

#endif