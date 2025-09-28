#include "structs.h"
#include "func.h"
#include <iostream>
using namespace std;

int main() {
    // Демонстрация работы функций
    cout << "=== Демонстрация работы с геометрическими фигурами ===\n\n";
    
    // Создание и работа с точкой
    Point p;
    cout << "Ввод точки:\n";
    readPoint(p);
    cout << "Точка: ";
    printPoint(p);
    cout << "\n\n";
    
    // Создание и работа с кругом
    Circle c;
    cout << "Ввод круга:\n";
    readCircle(c);
    cout << "Круг: ";
    printCircle(c);
    cout << "\nПлощадь круга: " << circleArea(c);
    cout << "\nДлина окружности: " << circleCircumference(c) << "\n\n";
    
    // Создание и работа с квадратом
    Square s;
    cout << "Ввод квадрата:\n";
    readSquare(s);
    cout << "Квадрат: ";
    printSquare(s);
    cout << "\nПлощадь квадрата: " << SquareArea(s);
    cout << "\nПериметр квадрата: " << SquarePerimeter(s) << "\n\n";
    
    // Проверка вхождения точки в фигуры
    cout << "Проверка вхождения точки в фигуры:\n";
    cout << "Точка внутри круга: " << (isPointInsideCircle(p, c) ? "да" : "нет") << "\n";
    cout << "Точка внутри квадрата: " << (isPointInsideSquare(p, s) ? "да" : "нет") << "\n";
    cout << "Точка на круге: " << (isPointOnCircle(p, c) ? "да" : "нет") << "\n";
    cout << "Точка на квадрате: " << (isPointOnSquare(p, s) ? "да" : "нет") << "\n";
    
    return 0;
}