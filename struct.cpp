#include <iostream>
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

// Структура Point
struct Point {
    double x;
    double y;
};

// Функции для Point
void readPoint(Point& p) {
    cout << "Введите координату x: ";
    cin >> p.x;
    cout << "Введите координату y: ";
    cin >> p.y;
}

void printPoint(const Point& p) {
    cout << "(" << p.x << ", " << p.y << ")";
}

// Структура Circle
struct Circle {
    Point center;
    double radius;
};

// Функции для Circle
void readCircle(Circle& c) {
    cout << "Введите координаты центра круга:\n";
    readPoint(c.center);
    cout << "Введите радиус круга: ";
    cin >> c.radius;
}

void printCircle(const Circle& c) {
    cout << "Круг: центр = ";
    printPoint(c.center);
    cout << ", радиус = " << c.radius;
}

double circleCircumference(const Circle& c) {
    return 2 * M_PI * c.radius;
}

double circleArea(const Circle& c) {
    return M_PI * c.radius * c.radius;
}

// Структура Square
struct Square {
    Point topLeft; // левый верхний угол
    double side;   // длина стороны
};

// Функции для Square
void readSquare(Square& s) {
    cout << "Введите координаты левого верхнего угла квадрата:\n";
    readPoint(s.topLeft);
    cout << "Введите длину стороны квадрата: ";
    cin >> s.side;
}

void printSquare(const Square& s) {
    cout << "Квадрат: левый верхний угол = ";
    printPoint(s.topLeft);
    cout << ", длина стороны = " << s.side;
}

double squarePerimeter(const Square& s) {
    return 4 * s.side;
}

double squareArea(const Square& s) {
    return s.side * s.side;
}

// Функция для проверки пересечения точек (с точностью 10^-5)
bool pointsIntersect(const Point& p1, const Point& p2) {
    const double epsilon = 1e-5;
    return (abs(p1.x - p2.x) < epsilon) && (abs(p1.y - p2.y) < epsilon);
}

int main() {
    // Демонстрация работы с точкой
    cout << "=== Работа с точкой ===\n";
    Point p1, p2;
    
    cout << "Точка 1:\n";
    readPoint(p1);
    cout << "Точка 2:\n";
    readPoint(p2);
    
    cout << "Точка 1: ";
    printPoint(p1);
    cout << "\nТочка 2: ";
    printPoint(p2);
    cout << "\nТочки пересекаются: " << (pointsIntersect(p1, p2) ? "да" : "нет") << "\n\n";
    
    // Демонстрация работы с кругом
    cout << "=== Работа с кругом ===\n";
    Circle circle;
    readCircle(circle);
    
    printCircle(circle);
    cout << "\nДлина окружности: " << circleCircumference(circle);
    cout << "\nПлощадь круга: " << circleArea(circle) << "\n\n";
    
    // Демонстрация работы с квадратом
    cout << "=== Работа с квадратом ===\n";
    Square square;
    readSquare(square);
    
    printSquare(square);
    cout << "\nПериметр квадрата: " << squarePerimeter(square);
    cout << "\nПлощадь квадрата: " << squareArea(square) << "\n";
    
    return 0;
}