#include <iostream>
#include <cstdlib>

int main() {
    double a, b;
    std::cout << "Введите a:";
    std::cin >> a;

    std::cout << "Введите b:";
    std::cin >> b;

    std::cout << "Исходные значениея:" << "a = " << a << ", " << "b = " << b << std::endl;

    //создаем указатели
    double* pa = new double;
    double* pb = new double;

    pa = &a;
    pb = &b;

    std::cout << "Адреса переменных:" << std::endl;
    std::cout << "Аресс a:" << &a << std::endl;
    std::cout << "Аресс b:" << &b << std::endl;
    std::cout << "Значение указателя a:" << pa << std::endl;
    std::cout << "Значение указателя b:" << pb << std::endl;

    *pa *= 3;

    std::cout << "а увелич. в 3 раза: ";
    std::cout << "a = " << a << " ";
    std::cout << "b = " << b << std::endl;

    double tmp = *pa;
    *pa = *pb;
    *pb = tmp;

    std::cout << "После обмена: " << "a = " << a << ", " << "b = " << b << std::endl;

    pa = &a;
    pb = &b;

    delete pa;
    delete pb;

    pa = nullptr;
    pb = nullptr;

    return 0;
    
}