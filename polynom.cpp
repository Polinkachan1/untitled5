#include "headers/polynom.h"
#include "headers/array.h"
#include "headers/number.h"
#include <cmath>
#include <iostream>

using namespace std;

Polynom::Polynom() {
    degree = 0;
    an = number(1, 0);
    roots = new Array(degree);
    coefficients = new Array(degree + 1);
    coefficients->changeElem(0, an);
}

Polynom::Polynom(int n, number an_value) {
    degree = n;
    an = an_value;
    roots = new Array(degree);
    coefficients = new Array(degree + 1);

    for (int i = 0; i < degree; i++) {
        roots->changeElem(i, number(0, 0));
    }
    calculateCoefficients();
}

Polynom::Polynom(int n, number an_value, Array& roots_array) {
    degree = n;
    an = an_value;
    roots = new Array(roots_array);
    coefficients = new Array(degree + 1);
    calculateCoefficients();
}

Polynom::~Polynom() {
    delete roots;
    delete coefficients;
}

void Polynom::calculateCoefficients() {
    // Очищаем коэффициенты
    for (int i = 0; i <= degree; i++) {
        coefficients->changeElem(i, number(0, 0));
    }

    if (degree == 0) {
        coefficients->changeElem(0, an);
        return;
    }

    // Простой алгоритм: начинаем с полинома 1 и последовательно умножаем на (x - root_i)
    number* poly = new number[degree + 1];
    for (int i = 0; i <= degree; i++) {
        poly[i] = number(0, 0);
    }
    poly[0] = number(1, 0);

    for (int i = 0; i < degree; i++) {
        number root = roots->findElem(i);

        // Временный массив для нового полинома
        number* new_poly = new number[degree + 1];
        for (int j = 0; j <= degree; j++) {
            new_poly[j] = number(0, 0);
        }

        // Умножаем текущий полином на (x - root)
        // new_poly = poly * x - poly * root
        for (int j = 0; j <= i; j++) {
            // poly * x (сдвиг вправо)
            if (j < degree) {
                new_poly[j + 1] = new_poly[j + 1] + poly[j];
            }
            // -poly * root
            new_poly[j] = new_poly[j] - (poly[j] * root);
        }

        // Копируем результат
        for (int j = 0; j <= degree; j++) {
            poly[j] = new_poly[j];
        }

        delete[] new_poly;
    }

    // Умножаем на an
    for (int i = 0; i <= degree; i++) {
        coefficients->changeElem(i, poly[i] * an);
    }

    delete[] poly;
}

// Остальные методы остаются без изменений...
int Polynom::getDegree() {
    return degree;
}

number Polynom::getCoefficient(int index) {
    if (index >= 0 && index <= degree) {
        return coefficients->findElem(index);
    }
    return number(0, 0);
}

number Polynom::getRoot(int index) {
    if (index >= 0 && index < degree) {
        return roots->findElem(index);
    }
    return number(0, 0);
}

void Polynom::setAn(number new_an) {
    an = new_an;
    calculateCoefficients();
}

void Polynom::setRoot(int index, number new_root) {
    if (index >= 0 && index < degree) {
        roots->changeElem(index, new_root);
        calculateCoefficients();
    }
}

void Polynom::resize(int new_degree) {
    if (new_degree < 0) return;

    Array* new_roots = new Array(new_degree);

    int min_degree = (degree < new_degree) ? degree : new_degree;
    for (int i = 0; i < min_degree; i++) {
        new_roots->changeElem(i, roots->findElem(i));
    }

    for (int i = min_degree; i < new_degree; i++) {
        new_roots->changeElem(i, number(0, 0));
    }

    delete roots;
    roots = new_roots;
    degree = new_degree;

    delete coefficients;
    coefficients = new Array(degree + 1);

    calculateCoefficients();
}

number Polynom::findNumberInPoint(number x) {
    number result(0, 0);

    for (int i = degree; i >= 0; i--) {
        result = result * x + coefficients->findElem(i);
    }

    return result;
}
void Polynom::input(std::istream& in) {
    cout << "Введите степень полинома: ";
    in >> degree;

    cout << "Введите коэффициент an: ";
    in >> an;

    delete roots;
    delete coefficients;

    roots = new Array(degree);
    coefficients = new Array(degree + 1);

    if (degree > 0) {
        cout << "Введите " << degree << " корней полинома: " << endl;
        for (int i = 0; i < degree; i++) {
            cout << "Корень номер "<< i+1 << ": ";
            number root;
            in >> root;
            roots->changeElem(i, root);
        }
    }
    calculateCoefficients();
    cout << "Полином успешно создан!!" << endl;
}

void Polynom::setRootsFromArray(Array& sourceArray, int startIndex) {
    if (startIndex < 0 || startIndex >= sourceArray.getLength()) {
        cout << "Неверный начальный индекс" << endl;
        return;
    }

    int availableRoots = sourceArray.getLength() - startIndex;
    if (availableRoots < degree) {
        cout << "В массиве недостаточно элементов для всех корней. Нужно: " << degree
             << ", доступно: " << availableRoots << endl;
        return;
    }

    for (int i = 0; i < degree; i++) {
        number root = sourceArray.findElem(startIndex + i);
        roots->changeElem(i, root);
    }

    calculateCoefficients();
    cout << "Корни полинома успешно установлены из массива!" << endl;
}
void Polynom::outputForm1(std::ostream& out) {
    bool firstItem = true;

    for (int i = degree; i >= 0; i--) {
        number coeff = coefficients->findElem(i);

        if (coeff.getRe() == 0 && coeff.getIm() == 0) {
            continue;
        }

        if (!firstItem) {
            out << " + ";
        }

        out << "(" << coeff << ")";

        if (i > 0) {
            out << "*x";
            if (i > 1) {
                out << "^" << i;
            }
        }
        firstItem = false;
    }

    if (firstItem) {
        out << "0";
    }
}

void Polynom::outputForm2(std::ostream& out) {
    out << "(" << an << ")";
    for (int i = 0; i < degree; i++) {
        number root = roots->findElem(i);
        out << "*(x - (" << root << "))";
    }
}

std::string Polynom::getForm1() {
    std::string result;
    bool firstItem = true;

    for (int i = degree; i >= 0; i--) {
        number coeff = coefficients->findElem(i);

        if (coeff.getRe() == 0 && coeff.getIm() == 0) {
            continue;
        }

        if (!firstItem) {
            result += " + ";
        }

        result += "(" + coeff.to_str() + ")";

        if (i > 0) {
            result += "*x";
            if (i > 1) {
                result += "^" + std::to_string(i);
            }
        }
        firstItem = false;
    }

    if (firstItem) {
        result = "0";
    }

    return result;
}

std::string Polynom::getForm2() {
    std::string result = "(" + an.to_str() + ")";
    for (int i = 0; i < degree; i++) {
        number root = roots->findElem(i);
        result += "*(x - (" + root.to_str() + "))";
    }
    return result;
}