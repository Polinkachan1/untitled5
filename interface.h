#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include "array.h"
#include "polynom.h"

class TInterface : public QWidget {
    Q_OBJECT

    // Элементы для задания степени
    QLabel *degreeLabel;
    QLineEdit *degreeInput;
    QPushButton *setDegreeButton;

    // Элементы для коэффициента an
    QLabel *coefficientLead;
    QLineEdit *coefficientLeadRealNumber, *coefficientLeadImaginaryNumber;
    QPushButton *newLeadCoefficientButton;

    // Элементы для ввода корней
    QLabel *coefficient, *delimeterCoefficient;
    QLineEdit *coefficientRealNumber, *coefficientImaginaryNumber;
    QPushButton *addRootsButton;
    QLabel *rootsCounter;

    // Элементы для изменения корней
    QPushButton *changeRootButton;
    QLineEdit *changeRoot;
    QLineEdit *changeRootReal, *changeRootImag;  // ДОБАВИТЬ ЭТИ СТРОКИ

    // Элементы для изменения размерности
    QLineEdit *resizeInput;  // ДОБАВИТЬ ЭТУ СТРОКУ
    QPushButton *resizeButton;

    // Элементы для вычисления значения
    QLabel *value;
    QLabel *calculateValue;
    QLineEdit *calculateValueAtPoint;
    QPushButton *calculateValueAtPointButton;

    // Поле вывода
    QLabel *output;

    Polynom *polynom;
    Array *rootsArray;
    int currentDegree;
    int rootsEntered;
    number an;

public:
    TInterface(QWidget *parent = 0);
    ~TInterface();

public slots:
    void setDegree();
    void addLeadCoefficient();
    void addRoots();
    void changeRootFunc();
    void resizePolynom();
    void findValueAtPoint();
    void print();
};
#endif // INTERFACE_H