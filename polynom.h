#ifndef OOP2_POLYNOM_H
#define OOP2_POLYNOM_H
#include "array.h"
#include "number.h"
#include <iostream>

class Polynom {
private:
    int degree;
    number an;
    Array* roots;
    Array* coefficients;
    void calculateCoefficients();
public:
    Polynom();
    ~Polynom();
    Polynom(int n, number an_value);
    Polynom(int n, number an_value, Array& roots_array);
    //гетры
    int getDegree();
    number getCoefficient(int index);
    number getRoot(int index);

    void input(std::istream& in);
    void outputForm1(std::ostream& out);
    void outputForm2(std::ostream& out);
    number findNumberInPoint(number x);
    void resize(int new_degree);
    void setAn(number new_an);
    void setRoot(int index, number new_root);
    void setRootsFromArray(Array& sourceArray, int startIndex = 0);
    std::string getForm1();
    std::string getForm2();
};


#endif //OOP2_POLYNOM_H