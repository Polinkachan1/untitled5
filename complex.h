#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include <cmath>
#include <string>

class TComplex{
private:
    double re;
    double im;
public:
    TComplex();
    TComplex(double re, double im);
    TComplex(double re);
    double getRe() const;
    double getIm() const;

    // Операторы с const ссылками
    TComplex operator-(const TComplex &second) const;
    TComplex operator+(const TComplex &second) const;
    TComplex operator*(const TComplex &second) const;

    // Унарный минус
    TComplex operator-() const;

    TComplex& operator+=(const TComplex &second);
    TComplex& operator-=(const TComplex &second);
    TComplex& operator*=(const TComplex &second);
    TComplex& operator/=(const TComplex &second);

    TComplex& operator=(const TComplex &other);

    bool operator>(const TComplex &second) const;
    bool operator<(const TComplex &second) const;
    bool operator==(const TComplex &second) const;

    double modulus() const;
    std::string to_str() const;

    friend std::istream& operator >> (std::istream & in, TComplex & c);
    friend std::ostream& operator << (std::ostream & os, const TComplex & c);
    friend TComplex pow(const TComplex &complex, double n);
};

#endif