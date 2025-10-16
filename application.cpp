#include "headers/application.h"
#include "headers/polynom.h"
#include "iostream"

using namespace std;
Application::Application() {
    currentArray = nullptr;
}

void Application::menu() {
    cout << "МЕНЮ РАБОТЫ С МАССИВОМ" << endl;
    cout << "1 - Создать массив заданной длины" << endl;
    cout << "2 - Заполнить массив" << endl;
    cout << "3 - Изменить размерность массива" << endl;
    cout << "4 - Вывести элементы массива" << endl;
    cout << "5 - Вычислить среднее и СКО" << endl;
    cout << "6 - Сортировать по возрастанию" << endl;
    cout << "7 - Сортировать по убыванию" << endl;
    cout << "8 - Изменить значение выбранного элемента массива" << endl;
    cout << "9 - Выход" << endl;
}
void Application::menuPolynom() {
    cout << "МЕНЮ РАБОТЫ С ПОЛИНОМОМ" << endl;
    cout << "1 - Создать полином 0-й степени" << endl;
    cout << "2 - Ввести полином n-й степени" << endl;
    cout << "3 - Изменить коэффициент an" << endl;
    cout << "4 - Изменить корень по индексу" << endl;
    cout << "5 - Изменить размерность полинома" << endl;
    cout << "6 - Вывести полином в форме 1 (anx^n + ... + a0)" << endl;
    cout << "7 - Вывести полином в форме 2 (an(x-rn)...(x-r1))" << endl;
    cout << "8 - Вычислить значение полинома в точке" << endl;
    cout << "9 - Установить корни из массива" << endl;
    cout << "10 - Выход" << endl;
}
int Application::polynomExec() {
    int option;
    Polynom* polynom = new Polynom(); // Полином по умолчанию

    while (true) {
        menuPolynom();
        cout << "Выберите вариант: ";
        cin >> option;

        switch (option) {
            case 1: {
                delete polynom;
                polynom = new Polynom();
                cout << "Создан полином по умолчанию (нулевой степени)" << endl;
                break;
            }
            case 2: {
                polynom->input(cin);
                break;
            }
            case 3: {
                number new_an;
                cout << "Введите новый коэффициент an: ";
                cin >> new_an;
                polynom->setAn(new_an);
                cout << "Коэффициент an успешно изменен" << endl;
                break;
            }
            case 4: {
                int index;
                number new_root;
                cout << "Введите индекс корня для изменения (0-" << polynom->getDegree()-1 << "): ";
                cin >> index;
                cout << "Введите новое значение корня: ";
                cin >> new_root;
                polynom->setRoot(index, new_root);
                cout << "Корень успешно изменен" << endl;
                break;
            }
            case 5: {
                int new_degree;
                cout << "Введите новую степень полинома: ";
                cin >> new_degree;
                polynom->resize(new_degree);
                cout << "Размерность полинома изменена" << endl;
                break;
            }
            case 6: {
                cout << "Полином в форме 1: ";
                polynom->outputForm1(cout);
                cout << endl;
                break;
            }
            case 7: {
                cout << "Полином в форме 2: ";
                polynom->outputForm2(cout);
                cout << endl;
                break;
            }
            case 8: {
                number x, result;
                cout << "Введите точку x для вычисления: ";
                cin >> x;
                result = polynom->findNumberInPoint(x);
                cout << "Значение полинома в точке " << x << " равно: " << result << endl;
                break;
            }
            case 9: {
                if (currentArray != nullptr && currentArray->getLength() > 0) {
                    int startIndex;
                    cout << "Текущий массив: ";
                    currentArray->printArray();
                    cout << "Введите начальный индекс в массиве (0-" << currentArray->getLength()-1 << "): ";
                    cin >> startIndex;
                    polynom->setRootsFromArray(*currentArray, startIndex);
                } else {
                    cout << "Сначала создайте и заполните массив в меню для массива!" << endl;
                }
                break;
            }
            case 10: {
                delete polynom;
                return 0;
            }
            default: {
                cout << "Введите корректное значение" << endl;
            }
        }
    }
}
int Application::allMenu() {
    int option;
    while (true) {
        cout << "1 - действия с массивом"<< endl;
        cout << "2 - действия с полиномом"<< endl;
        cout << "3 - выход"<< endl;
        cin >> option;
        switch (option) {
            case 1:
                {
                exec();
                break;
            }
            case 2: {
                polynomExec();
                break;
            }
            case 3:
                return 0;
        }
    }
}

int Application::exec() {
    int option, length;
    if (currentArray == nullptr) {
        currentArray = new Array();
    }

    while (true) {
        menu();
        cout << "Выберите вариант: " << endl;
        cin >> option;

        switch (option) {
        case 1:
        {
            cout << "Введите длину массива: ";
            cin >> length;
            delete currentArray;
            currentArray = new Array(length);
            cout << "Массив создан с длиной: " << length << endl;
            break;
        }
        case 2:
        {
            if (currentArray->getLength() == 0) {
                cout << "Сначала создайте массив (пункт 1)!" << endl;
            } else {
                cout << "Введите " << currentArray->getLength() << " элементов для заполнения массива: ";
                currentArray->add();
            }
            break;
        }
        case 3:
        {
            cout << "Введите новую длину массива: ";
            cin >> length;
            currentArray->changeLength(length);
            cout << "Новая длина массива: " << currentArray->getLength() << endl;
            break;
        }
        case 4:
        {
            cout << "Ваш массив: ";
            currentArray->printArray();
            break;
        }
        case 5:
        {
            cout << "Среднее значение: " << currentArray->average() << ", ";
            cout << "СКО: " << currentArray->sko() << endl;
            break;
        }
        case 6:
        {
            cout << "Исходный массив: ";
            currentArray->printArray();
            cout << "Отсортированный по возрастанию: ";
            currentArray->sortIncrease();
            currentArray->printArray();
            break;
        }
        case 7:
        {
            cout << "Исходный массив: ";
            currentArray->printArray();
            cout << "Отсортированный по убыванию: ";
            currentArray->sortDecrease();
            currentArray->printArray();
            break;
        }
        case 8:
        {
            int index;
            cout << "Исходный массив: ";
            currentArray->printArray();
            cout << "Введите индекс элемента для изменения (0-" << currentArray->getLength()-1 << "): ";
            cin >> index;
            currentArray->changeElem(index);
            cout << "Измененный массив: ";
            currentArray->printArray();
            break;
        }
        case 9:
        {
            return 0;
        }
        default:
        {
            cout << "Введите корректное значение" << endl;
        }
        }
    }
}