#include "headers/array.h"

#include <cmath>
#include <iostream>
#include "headers/complex.h"
#include "headers/number.h"
using namespace std;

Array::Array(int length) {
    if (length < 0) {
        this->length = 0;
        cout << "Введите неотрицательное число, сейчас по-умолчанию длина массива 0";
    }
    else {
        this->length = length;
    }
    array = new number[length];
}
Array::~Array() {
    delete[] array;
}
void Array::add() {
    for (int i = 0; i < length; i++) {
        cin >> array[i];
    }
}
int Array::changeLength(int new_length) {
    if (new_length <= 0) return length;

    number* new_array = new number[new_length];
    for (int i = 0; i < min(length, new_length); i++) {
        new_array[i] = array[i];
    }
    delete[] array;
    array = new_array;
    for (int i = length; i < new_length; i++) {
        cout << "Введите новый элемент массива";
        cin >> array[i];
    }
    length = new_length;
    return length;
}

void Array::printArray() {
    for (int i = 0; i < length; i++) {
        cout << array[i] <<" ";
    }
    cout << "\n";
}
double Array::average() {
    double summa = 0;
    if (length != 0) {
        for (int i = 0; i < length; i++) {
            summa += array[i].getRe();
        }
        summa /= length;
    }
    return summa;
}
double Array::sko() {
    double result = 0;
    double average = 1;
    if (length != 0) {
        for (int i = 0; i < length; i++) {
            result += pow((array[i].getRe()-average),2);
        }
        result /= (length-1);
        result = pow(result, 0.5);
    }
    return result;
}
void Array::sortIncrease(){
    for (int i = 0; i < length - 1; i++) {
        for (int j=0; j < length - i - 1; j++) {
            if (array[j] > array[j+1]) {
                swap(array[j], array[j+1]);
            }
        }
    }
}
void Array::sortDecrease() {
    for (int i = 0; i < length - 1; i++) {
        for (int j=0; j < length - i - 1; j++) {
            if (array[j] < array[j+1]) {
                swap(array[j], array[j+1]);
            }
        }
    }
}

void Array::changeElem(int index) {
    if (index <= length && index >= 0) {
        cout << "Введите новое значение: ";
        cin >> array[index];
    }
}

void Array::changeElem(int index, number value) {
    if (index >= 0 && index < length) {
        array[index] = value;
    }
}

number Array::findElem(int index) {
    if (index >= 0 && index < length) {
        return array[index];
    }
    return number(0,0);
}

int Array::getLength() const {
    return length;
}