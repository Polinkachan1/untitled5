#include "headers/interface.h"

TInterface::TInterface(QWidget *parent)
    : QWidget(parent), currentDegree(0), rootsEntered(0), an(1, 0) {
    setWindowTitle("Работа с полиномами");
    setFixedSize(500, 500);

    polynom = new Polynom();
    rootsArray = new Array();

    // Элементы для задания степени
    degreeLabel = new QLabel("Степень:", this);
    degreeLabel->setGeometry(50, 20, 60, 25);
    degreeInput = new QLineEdit("0", this);
    degreeInput->setGeometry(120, 20, 50, 25);
    setDegreeButton = new QPushButton("Установить", this);
    setDegreeButton->setGeometry(180, 20, 80, 25);

    // Элементы для коэффициента an
    coefficientLead = new QLabel("an =", this);
    coefficientLead->setGeometry(50, 50, 30, 25);
    coefficientLeadRealNumber = new QLineEdit("1", this);
    coefficientLeadRealNumber->setGeometry(90, 50, 40, 25);
    (new QLabel("+ i*", this))->setGeometry(140, 50, 30, 25);
    coefficientLeadImaginaryNumber = new QLineEdit("0", this);
    coefficientLeadImaginaryNumber->setGeometry(180, 50, 40, 25);
    newLeadCoefficientButton = new QPushButton("Установить an", this);
    newLeadCoefficientButton->setGeometry(230, 50, 100, 25);

    // Элементы для ввода корней
    coefficient = new QLabel("Корень =", this);
    coefficient->setGeometry(50, 80, 50, 25);
    coefficientRealNumber = new QLineEdit("0", this);
    coefficientRealNumber->setGeometry(110, 80, 40, 25);
    delimeterCoefficient = new QLabel("+ i*", this);
    delimeterCoefficient->setGeometry(160, 80, 30, 25);
    coefficientImaginaryNumber = new QLineEdit("0", this);
    coefficientImaginaryNumber->setGeometry(200, 80, 40, 25);
    addRootsButton = new QPushButton("Добавить корень", this);
    addRootsButton->setGeometry(250, 80, 120, 25);
    rootsCounter = new QLabel("Корней: 0/0", this);
    rootsCounter->setGeometry(380, 80, 100, 25);

    // Элементы для изменения корней
    changeRootButton = new QPushButton("Изменить корень с индексом:", this);
    changeRootButton->setGeometry(50, 110, 180, 25);
    changeRoot = new QLineEdit("0", this);
    changeRoot->setGeometry(240, 110, 30, 25);

    // Элементы для изменения размерности
    resizeButton = new QPushButton("Изменить размерность", this);
    resizeButton->setGeometry(50, 140, 150, 30);

    // Элементы для вычисления значения
    calculateValue = new QLabel("Вычислить в точке x =", this);
    calculateValue->setGeometry(50, 180, 130, 25);
    calculateValueAtPoint = new QLineEdit("0", this);
    calculateValueAtPoint->setGeometry(190, 180, 40, 25);
    calculateValueAtPointButton = new QPushButton("Вычислить", this);
    calculateValueAtPointButton->setGeometry(240, 180, 80, 25);
    value = new QLabel("Результат: ", this);
    value->setGeometry(330, 180, 150, 25);

    // Поле вывода
    output = new QLabel(this);
    output->setGeometry(50, 220, 400, 250);
    output->setWordWrap(true);
    output->setAlignment(Qt::AlignTop);

    // Подключение сигналов
    connect(setDegreeButton, SIGNAL(clicked()), this, SLOT(setDegree()));
    connect(newLeadCoefficientButton, SIGNAL(clicked()), this, SLOT(addLeadCoefficient()));
    connect(addRootsButton, SIGNAL(clicked()), this, SLOT(addRoots()));
    connect(changeRootButton, SIGNAL(clicked()), this, SLOT(changeRootFunc()));
    connect(resizeButton, SIGNAL(clicked()), this, SLOT(resizePolynom()));
    connect(calculateValueAtPointButton, SIGNAL(clicked()), this, SLOT(findValueAtPoint()));

    print();
}

TInterface::~TInterface() {
    delete polynom;
    delete rootsArray;
}

void TInterface::setDegree() {
    bool ok;
    int degree = degreeInput->text().toInt(&ok);
    if (!ok || degree < 0) {
        output->setText("Ошибка: неверная степень");
        return;
    }

    currentDegree = degree;
    rootsEntered = 0; // Сбрасываем счетчик корней

    delete polynom;
    polynom = new Polynom(degree, an);

    rootsCounter->setText(QString("Корней: %1/%2").arg(rootsEntered).arg(currentDegree));
    print();
}

void TInterface::addLeadCoefficient() {
    bool ok1, ok2;
    double re = coefficientLeadRealNumber->text().toDouble(&ok1);
    double im = coefficientLeadImaginaryNumber->text().toDouble(&ok2);

    if (!ok1 || !ok2) {
        output->setText("Ошибка: неверный ввод an");
        return;
    }

    an = number(re, im);

    if (polynom) {
        polynom->setAn(an);
    }

    print();
}

void TInterface::addRoots() {
    // Если все корни уже введены, но есть возможность увеличить размерность
    if (rootsEntered >= currentDegree) {
        // Автоматически увеличиваем размерность на 1
        currentDegree++;
        polynom->resize(currentDegree);
        rootsCounter->setText(QString("Корней: %1/%2").arg(rootsEntered).arg(currentDegree));
    }

    bool ok1, ok2;
    double re = coefficientRealNumber->text().toDouble(&ok1);
    double im = coefficientImaginaryNumber->text().toDouble(&ok2);

    if (!ok1 || !ok2) {
        output->setText("Ошибка: неверный ввод корня");
        return;
    }

    number root(re, im);

    // Если это новый корень (не все позиции заполнены)
    if (rootsEntered < currentDegree) {
        polynom->setRoot(rootsEntered, root);
        rootsEntered++;
    } else {
        // Если массив полный, добавляем в конец (после увеличения размерности)
        polynom->setRoot(currentDegree - 1, root);
        rootsEntered = currentDegree;
    }

    rootsCounter->setText(QString("Корней: %1/%2").arg(rootsEntered).arg(currentDegree));
    print();
}

void TInterface::changeRootFunc() {
    bool ok;
    int index = changeRoot->text().toInt(&ok);
    if (!ok || index < 0 || index >= currentDegree) {
        output->setText("Ошибка: неверный индекс");
        return;
    }

    bool ok1, ok2;
    double re = coefficientRealNumber->text().toDouble(&ok1);
    double im = coefficientImaginaryNumber->text().toDouble(&ok2);

    if (!ok1 || !ok2) {
        output->setText("Ошибка: неверный ввод корня");
        return;
    }

    number root(re, im);
    polynom->setRoot(index, root);

    print();
}

void TInterface::resizePolynom() {
    bool ok;
    int newDegree = degreeInput->text().toInt(&ok);
    if (!ok || newDegree < 0) {
        output->setText("Ошибка: неверная степень");
        return;
    }

    // Сохраняем старую степень для логики
    int oldDegree = currentDegree;

    // Изменяем размерность
    polynom->resize(newDegree);
    currentDegree = newDegree;

    // Обновляем счетчик корней
    if (newDegree < oldDegree) {
        // Если уменьшили размерность - обрезаем счетчик
        rootsEntered = (rootsEntered > newDegree) ? newDegree : rootsEntered;
    }
    // Если увеличили размерность - rootsEntered не меняется (новые позиции пустые)

    rootsCounter->setText(QString("Корней: %1/%2").arg(rootsEntered).arg(currentDegree));
    print();
}

void TInterface::findValueAtPoint() {
    bool ok;
    double x = calculateValueAtPoint->text().toDouble(&ok);
    if (!ok) {
        output->setText("Ошибка: неверная точка");
        return;
    }

    number point(x, 0);
    number result = polynom->findNumberInPoint(point);

    QString resultStr;
    if (result.getIm() == 0) {
        resultStr = QString::number(result.getRe());
    } else {
        resultStr = QString("%1 + i*%2").arg(result.getRe()).arg(result.getIm());
    }

    value->setText("Результат: " + resultStr);
    print();
}

void TInterface::print() {
    QString outputText;

    outputText += "Текущий полином:\n";
    outputText += "Степень: " + QString::number(currentDegree) + "\n";
    outputText += "an: " + QString::fromStdString(an.to_str()) + "\n";
    outputText += "Корней введено: " + QString::number(rootsEntered) + "/" + QString::number(currentDegree) + "\n\n";

    outputText += "Форма 1: " + QString::fromStdString(polynom->getForm1()) + "\n\n";
    outputText += "Форма 2: " + QString::fromStdString(polynom->getForm2()) + "\n\n";

    if (currentDegree > 0) {
        outputText += "Корни: ";
        for (int i = 0; i < currentDegree; i++) {
            outputText += "r" + QString::number(i) + "=";
            if (i < rootsEntered) {
                outputText += QString::fromStdString(polynom->getRoot(i).to_str());
            } else {
                outputText += "не задан";
            }
            if (i < currentDegree - 1) outputText += ", ";
        }
    }

    output->setText(outputText);
}