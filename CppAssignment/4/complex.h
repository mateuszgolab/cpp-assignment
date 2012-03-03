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
    Complex();                    
	Complex(double re);          
    Complex(double re, double im);
    Complex(const Complex& c); 
	double getReal() const;
	double getImag() const; 
	Complex& setReal(double re); 
    Complex& setImag(double im); 

    // overloaded operators
    Complex operator+(const Complex& c) const;
    Complex operator*(const Complex& c) const;
    bool operator==(const Complex& c) const;
    Complex& operator+=(const Complex& c);
    Complex& operator=(const Complex& c); 

    friend std::ostream& operator<<(std::ostream& os, const Complex& c); //screen output
    friend std::istream& operator>>(std::istream& is, Complex& c); //keyboard input

    //the file output operator should be compatible with file input operator,
    //ie. everything written can be read later.
    friend std::ofstream& operator<<(std::ofstream& ofs, const Complex& c); //file output
	friend std::ifstream& operator>>(std::ifstream& ifs, Complex& c); //file input
};

#endif