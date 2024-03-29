#include "vector.h"

// default constructor (empty vector)
Vector::Vector() : num(0), pdata(0) {}

// initialise data, called by the constructors
void Vector::Init(int Num)
{
    //check input sanity
    if(Num < 0) throw std::invalid_argument("vector size negative");
    num = Num;
    if (num <= 0)
        pdata = 0;  // empty vector, nothing to allocate
    else
        pdata = new double[num];  // Allocate memory for vector
}

// alternate constructor 
Vector::Vector(int Num)
{
    Init(Num);
}

// copy constructor
Vector::Vector(const Vector& copy)
{
    Init(copy.size()); // allocate the memory 

    // copy the data members (if vector is empty then pdata==0 and num==0)
    for (int i=0; i<num; i++) pdata[i]=copy.pdata[i]; 
}

// destructor
Vector::~Vector()
{
    delete [] pdata; // free the dynamic memory 
}

// assignment operator 
Vector& Vector::operator=(const Vector& copy)
{
    if (this == &copy) return *this; // Can't copy self to self (that is v = v 
    // in main is dealt with)
    delete [] pdata; // delete existing memory
    Init(copy.size()); // create new memory then copy data
    for (int i=0; i<num; i++) pdata[i] = copy.pdata[i]; 
    return *this;
}


// array access operator for assigning values
double& Vector::operator[](int i)
{
    //check the range, throw appropriate exception 
    if(i<0 || i>=num) throw std::out_of_range("vector access error");
    return pdata[i];
}

// array access operator for reading values
double Vector::operator[](int i) const
{
    //check the range, throw appropriate exception 
    if(i<0 || i>=num) throw std::out_of_range("vector access error");
    return pdata[i];
}

// return the size of the vector
int Vector::size() const
{
    return num;
}


// keyboard input - user friendly
std::istream& operator>>(std::istream& is, Vector& v)
{
    int n;

    std::cout << "input the size for the vector" << std::endl;
    is >> n;
    //check input sanity
    if(n < 0) throw std::invalid_argument("read error - negative vector size");

    // prepare the vector to hold n elements
    v = Vector(n);

    // input the elements
    std::cout << "input "<<n<<" vector elements" << std::endl;
    for (int i=0; i<n; i++) is >> v[i];

    // return the stream object
    return is;
}

// file input - raw data, compatible with file writing operator
std::ifstream& operator>>(std::ifstream& ifs, Vector& v) 
{
    int n;

    // read size from the file
    ifs >> n;
    //check input sanity
    if(n < 0) throw std::invalid_argument("file read error - negative vector size");

    // prepare the vector to hold n elements
    v = Vector(n);

    // input the elements
    for (int i=0; i<n; i++) ifs >> v[i];

    // return the stream object
    return ifs;
}

// screen output - user friendly
std::ostream& operator<<(std::ostream& os, const Vector& v)
{
    if (v.pdata) {
        os << "The vector elements are" << std::endl;
        for (int i=0; i<v.size(); i++) os << v[i]  << " ";
        os << std::endl;
    }
    else
    {
        os << "Vector is empty." << std::endl;
    }
    return os;
}

// file output - raw data, comaptible with file reading operator
std::ofstream& operator<<(std::ofstream& ofs, const Vector& v)
{
    //put vector size in first line (even if it is zero)
    ofs << v.size() << std::endl;
    //put data in second line (if size==zero nothing will be put)
    for (int i=0; i<v.size(); i++) ofs << v[i]  <<  " ";
    ofs << std::endl;
    return ofs;
}