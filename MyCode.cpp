#include <iostream>
#include <cmath>
using namespace std;

struct Point {
    float x, y;
};

struct Circle {
    Point center;
    double radius;
};

struct Square {
    Point topLeft;
    double side;
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

// Функции для Square
void readSquare(Square &s) {
    cout << "Введите координаты верхнего левого угла:\n";
    readPoint(s.topLeft);
    cout << "Введите длину стороны: ";
    cin >> s.side;
}

void printSquare(const Square &d) {
    cout << "Верхний левый угол: ";
    printPoint(d.topLeft);
    cout << ", длина стороны: " << d.side;
}

double SquareArea(const Square &d) {
    return d.side * d.side;
}

double SquarePerimeter(const Square &d) {
    return d.side * 4;
}

// Проверка вхождения точки в круг (строго внутри)
bool isPointInsideCircle(const Point& p, const Circle& c) {
    double distanceSquared = pow(p.x - c.center.x, 2) + pow(p.y - c.center.y, 2);
    return distanceSquared < pow(c.radius, 2);
}

// Проверка вхождения точки в квадрат (строго внутри)
bool isPointInsideSquare(const Point& p, const Square& s) {
    return (p.x > s.topLeft.x && 
            p.x < s.topLeft.x + s.side && 
            p.y < s.topLeft.y && 
            p.y > s.topLeft.y - s.side);
}

// Проверка нахождения точки на круге (на границе)
bool isPointOnCircle(const Point& p, const Circle& c) {
    double distanceSquared = pow(p.x - c.center.x, 2) + pow(p.y - c.center.y, 2);
    double radiusSquared = pow(c.radius, 2);
    // С учетом погрешности 1e-5
    return abs(distanceSquared - radiusSquared) < 1e-5;
}

// Проверка нахождения точки на квадрате (на границе)
bool isPointOnSquare(const Point& p, const Square& s) {
    double left = s.topLeft.x;
    double right = s.topLeft.x + s.side;
    double top = s.topLeft.y;
    double bottom = s.topLeft.y - s.side;
    
    // Проверяем, лежит ли точка на одной из сторон квадрата
    bool onLeft = abs(p.x - left) < 1e-5 && p.y >= bottom && p.y <= top;
    bool onRight = abs(p.x - right) < 1e-5 && p.y >= bottom && p.y <= top;
    bool onTop = abs(p.y - top) < 1e-5 && p.x >= left && p.x <= right;
    bool onBottom = abs(p.y - bottom) < 1e-5 && p.x >= left && p.x <= right;
    
    return onLeft || onRight || onTop || onBottom;
}

// Проверка пересечения двух кругов (хотя бы одна общая точка на границах)
bool doCirclesIntersect(const Circle& c1, const Circle& c2) {
    double distance = sqrt(pow(c1.center.x - c2.center.x, 2) + 
                          pow(c1.center.y - c2.center.y, 2));
    
    // Круги пересекаются, если расстояние между центрами меньше или равно сумме радиусов
    // и больше или равно разности радиусов (с учетом погрешности)
    return distance <= c1.radius + c2.radius + 1e-5 && 
           distance >= abs(c1.radius - c2.radius) - 1e-5;
}

// Проверка пересечения двух квадратов (хотя бы одна общая точка на границах)
bool doSquaresIntersect(const Square& s1, const Square& s2) {
    double s1_left = s1.topLeft.x;
    double s1_right = s1.topLeft.x + s1.side;
    double s1_top = s1.topLeft.y;
    double s1_bottom = s1.topLeft.y - s1.side;
    
    double s2_left = s2.topLeft.x;
    double s2_right = s2.topLeft.x + s2.side;
    double s2_top = s2.topLeft.y;
    double s2_bottom = s2.topLeft.y - s2.side;
    
    // Квадраты пересекаются, если они не разнесены по осям
    return s1_left <= s2_right + 1e-5 && 
           s1_right >= s2_left - 1e-5 && 
           s1_top >= s2_bottom - 1e-5 && 
           s1_bottom <= s2_top + 1e-5;
}

// Проверка пересечения круга и квадрата (хотя бы одна общая точка на границах)
bool doCircleAndSquareIntersect(const Circle& c, const Square& s) {
    double left = s.topLeft.x;
    double right = s.topLeft.x + s.side;
    double top = s.topLeft.y;
    double bottom = s.topLeft.y - s.side;
    
    // Находим ближайшую к центру круга точку квадрата
    double closestX = max(left, min(c.center.x, right));
    double closestY = max(bottom, min(c.center.y, top));
    
    // Вычисляем расстояние от центра круга до ближайшей точки квадрата
    double distanceX = c.center.x - closestX;
    double distanceY = c.center.y - closestY;
    double distanceSquared = distanceX * distanceX + distanceY * distanceY;
    
    // Пересечение есть, если расстояние до ближайшей точки <= радиусу
    return distanceSquared <= c.radius * c.radius + 1e-5;
}

// Дополнительная функция: проверка строгого пересечения кругов (исключая касание)
bool doCirclesStrictlyIntersect(const Circle& c1, const Circle& c2) {
    double distance = sqrt(pow(c1.center.x - c2.center.x, 2) + 
                          pow(c1.center.y - c2.center.y, 2));
    
    // Строгое пересечение: расстояние меньше суммы радиусов и больше разности
    return distance < c1.radius + c2.radius - 1e-5 && 
           distance > abs(c1.radius - c2.radius) + 1e-5;
}

// Дополнительная функция: проверка строгого пересечения квадратов
bool doSquaresStrictlyIntersect(const Square& s1, const Square& s2) {
    double s1_left = s1.topLeft.x;
    double s1_right = s1.topLeft.x + s1.side;
    double s1_top = s1.topLeft.y;
    double s1_bottom = s1.topLeft.y - s1.side;
    
    double s2_left = s2.topLeft.x;
    double s2_right = s2.topLeft.x + s2.side;
    double s2_top = s2.topLeft.y;
    double s2_bottom = s2.topLeft.y - s2.side;
    
    // Строгое пересечение: перекрытие по всем осям
    return s1_left < s2_right - 1e-5 && 
           s1_right > s2_left + 1e-5 && 
           s1_top > s2_bottom + 1e-5 && 
           s1_bottom < s2_top - 1e-5;
}

//Проверка 2-х кругов на принадлежность одного другому
bool isCircleInsideSquare(const Circle& c, const Square& s) {
    double left = s.topLeft.x;
    double right = s.topLeft.x + s.side;
    double top = s.topLeft.y;
    double bottom = s.topLeft.y - s.side;
    
    bool leftOK = (c.center.x - c.radius) >= left;
    bool rightOK = (c.center.x + c.radius) <= right;
    bool topOK = (c.center.y + c.radius) <= top;
    bool bottomOK = (c.center.y - c.radius) >= bottom;
    
    return leftOK && rightOK && topOK && bottomOK; // ← Исправлено
}

// Функция проверки, находится ли квадрат s1 внутри квадрата s2
bool isSquareInsideSquare(const Square& s1, const Square& s2) {
    // Получаем координаты всех углов квадрата s1
    Point s1_bottomRight = {s1.topLeft.x + s1.side, s1.topLeft.y - s1.side};
    Point s1_bottomLeft = {s1.topLeft.x, s1.topLeft.y - s1.side};
    Point s1_topRight = {s1.topLeft.x + s1.side, s1.topLeft.y};
    
    // Получаем координаты границ квадрата s2
    double s2_left = s2.topLeft.x;
    double s2_right = s2.topLeft.x + s2.side;
    double s2_top = s2.topLeft.y;
    double s2_bottom = s2.topLeft.y - s2.side;
    
    // Проверяем, что все углы квадрата s1 находятся внутри квадрата s2
    // (включая границы)
    return (s1.topLeft.x >= s2_left && s1.topLeft.x <= s2_right &&
            s1.topLeft.y <= s2_top && s1.topLeft.y >= s2_bottom &&
            
            s1_topRight.x >= s2_left && s1_topRight.x <= s2_right &&
            s1_topRight.y <= s2_top && s1_topRight.y >= s2_bottom &&
            
            s1_bottomLeft.x >= s2_left && s1_bottomLeft.x <= s2_right &&
            s1_bottomLeft.y <= s2_top && s1_bottomLeft.y >= s2_bottom &&
            
            s1_bottomRight.x >= s2_left && s1_bottomRight.x <= s2_right &&
            s1_bottomRight.y <= s2_top && s1_bottomRight.y >= s2_bottom);
}

// Функция проверки, находится ли квадрат внутри круга
bool isSquareInsideCircle(const Square& s, const Circle& c) {
    // Получаем координаты всех углов квадрата
    Point topLeft = s.topLeft;
    Point topRight = {s.topLeft.x + s.side, s.topLeft.y};
    Point bottomLeft = {s.topLeft.x, s.topLeft.y - s.side};
    Point bottomRight = {s.topLeft.x + s.side, s.topLeft.y - s.side};
    
    // Проверяем, что все углы квадрата находятся внутри круга
    // (включая границу круга)
    double r_squared = c.radius * c.radius;
    
    // Проверяем расстояние от центра круга до каждого угла
    bool topLeftInside = pow(topLeft.x - c.center.x, 2) + pow(topLeft.y - c.center.y, 2) <= r_squared;
    bool topRightInside = pow(topRight.x - c.center.x, 2) + pow(topRight.y - c.center.y, 2) <= r_squared;
    bool bottomLeftInside = pow(bottomLeft.x - c.center.x, 2) + pow(bottomLeft.y - c.center.y, 2) <= r_squared;
    bool bottomRightInside = pow(bottomRight.x - c.center.x, 2) + pow(bottomRight.y - c.center.y, 2) <= r_squared;
    return topLeftInside && topRightInside && bottomLeftInside && bottomRightInside;
}

// Функция проверки, находится ли круг внутри квадрата
bool isCircleInsideSquare(const Circle& c, const Square& s) {
    // Получаем границы квадрата
    double left = s.topLeft.x;
    double right = s.topLeft.x + s.side;
    double top = s.topLeft.y;
    double bottom = s.topLeft.y - s.side;
    
    // Проверяем, что круг полностью внутри квадрата:
    // Центр круга должен быть удален от каждой стороны на расстояние >= радиуса
    
    bool leftOK = (c.center.x - c.radius) >= left;
    bool rightOK = (c.center.x + c.radius) <= right;
    bool topOK = (c.center.y + c.radius) <= top;
    bool bottomOK = (c.center.y - c.radius) >= bottom;
    
    return leftOK && rightOK && rightOK && topOK && bottomOK;
}