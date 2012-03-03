#ifndef VECTOR_TEMPL_H //Include guard
#define VECTOR_TEMPL_H

#include <iostream> //Generic IO operations
#include <fstream>  //File IO operations
#include <stdexcept> //provides exceptions

//forward declarations - needed to tell the compiler that friends are templates
template <typename T> class Vector;
template <typename T> std::istream& operator>> (std::istream& is, Vector<T>& v);
template <typename T> std::ostream& operator<< (std::ostream& os, const Vector<T>& v);
template <typename T> std::ifstream& operator>>(std::ifstream& ifs, Vector<T>& v);
template <typename T> std::ofstream& operator<<(std::ofstream& ofs, const Vector<T>& v);

template <typename T>
class Vector {
private:
    int n; // Number of elements
    T* pdata; // Pointer to the data
    void init(int n); // private function since user should not call it
public:
    Vector(); // construct empty vector
    //alternate constructor, it is explicit since implicit
    //type conversion T -> vector doesn't make sense
    explicit Vector(int size); //construct vector of given size
    Vector(const Vector<T>& rv); // copy constructor
    virtual ~Vector(); // destructor is virtual since it is
    //a good thing to have virtual destr. in base class

    int size() const; // get number of elements in the vector
    Vector<T>& operator=(const Vector& rv); //overloaded assignment operator
    T& operator[] (int i); //access for writing
    const T& operator[] (int i) const; // access for reading

    friend std::istream& operator>>  <>(std::istream& is, Vector<T>& v);// keyboard input
    friend std::ostream& operator<<  <>(std::ostream& os, const Vector<T>& v);// screen output

    //the file output operator is compatible with file input operator,
    //ie. everything written can be read later.
    friend std::ifstream& operator>> <>(std::ifstream& ifs, Vector<T>& v);// file input
    friend std::ofstream& operator<< <>(std::ofstream& ofs, const Vector<T>& v);// file output
};

// initialise data, called by the constructors
template <typename T>
void Vector<T>::init(int n)
{
    //check input sanity
    if(n < 0) throw std::invalid_argument("vector size negative");
    this->n = n;
    if(n==0)
        pdata = 0;  // empty vector, nothing to allocate
    else
        pdata = new T[n];  // Allocate memory for vector
}


// default constructor
template <typename T>
Vector<T>::Vector() : n(0), pdata(0)
{}

// alternate constructor 
template <typename T>
Vector<T>::Vector(int size)
{
    init(size);
}

// copy constructor
template <typename T>
Vector<T>::Vector(const Vector& rv)
{
    init(rv.n); // allocate the memory 

    // copy the data members (if vector is empty then pdata==0 and num==0)
    for (int i=0; i<n; i++) pdata[i] = rv.pdata[i];
}

// destructor
template <typename T>
Vector<T>::~Vector()
{
    delete[] pdata; // free the dynamic memory 
}


// assignment operator 
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& rv)
{
    if (this == &rv) return *this; //check self-assignment
    delete[] pdata; // delete existing memory
    init(rv.n); // create new memory then copy data
    for (int i=0; i<n; i++) pdata[i] = rv.pdata[i];
    return *this;
}

// array access operator for assigning values
template <typename T>
T& Vector<T>::operator[](int i)
{
    //check the range, throw appropriate exception 
    if(i<0 || i>=n) throw std::out_of_range("vector access error");
    return pdata[i];
}

// array access operator for reading values
template <typename T>
const T& Vector<T>::operator[](int i) const
{
    //check the range, throw appropriate exception 
    if(i<0 || i>=n) throw std::out_of_range("vector access error");
    return pdata[i];
}

// return the size of the vector
template <typename T>
int Vector<T>::size() const
{
    return n;
}


// keyboard input - user friendly
template <typename T>
std::istream& operator>>(std::istream& is, Vector<T>& v)
{
    int n;

    std::cout << "input the size for the vector<"<<typeid(T).name()<<">"<<std::endl;
    is >> n;
    //check input sanity
    if(n < 0) throw std::invalid_argument("read error - negative vector size");

    // prepare the vector to hold n elements
    v = Vector<T>(n);

    // input the elements
    std::cout << "input "<<n<<" elements of type "<<typeid(T).name()<<std::endl;
    for (int i=0; i<n; i++) is >> v[i];

    // return the stream object
    return is;
}

// file input - raw data, compatible with file writing operator
template <typename T>
std::ifstream& operator>>(std::ifstream& ifs, Vector<T>& v) 
{
    int n;

    // read size from the file
    ifs >> n;
    //check input sanity
    if(n < 0) throw std::invalid_argument("file read error - negative vector size");

    // prepare the vector to hold n elements
    v = Vector<T>(n);

    // input the elements
    for (int i=0; i<n; i++) ifs >> v[i];

    // return the stream object
    return ifs;
}

// screen output - user friendly
template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& v)
{
    if (v.pdata) {
        os << "The vector elements are" << std::endl;
        for (int i=0; i<v.size(); i++) os << v[i]  << "\t";
        os << std::endl;
    }
    else
    {
        os << "Vector is empty." << std::endl;
    }
    return os;
}

// file output - raw data, comaptible with file reading operator
template <typename T>
std::ofstream& operator<<(std::ofstream& ofs, const Vector<T>& v)
{
    //put vector size in first line (even if it is zero)
    ofs << v.size() << std::endl;
    //put data in second line (if size==zero nothing will be put)
    for (int i=0; i<v.size(); i++)
    {
        ofs << v[i] <<  " ";
    }
    ofs << std::endl;
    return ofs;
}


#endif