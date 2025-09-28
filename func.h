#ifndef FUNC_H
#define FUNC_H

#include "structs.h"

// Функции для Point
void readPoint(Point& p);
void printPoint(const Point& p);

// Функции для Circle
void readCircle(Circle& c);
void printCircle(const Circle& c);
double circleCircumference(const Circle& c);
double circleArea(const Circle& c);

// Функции для Square
void readSquare(Square& s);
void printSquare(const Square& s);
double SquareArea(const Square& s);
double SquarePerimeter(const Square& s);

// Проверка вхождения точки в фигуры
bool isPointInsideCircle(const Point& p, const Circle& c);
bool isPointInsideSquare(const Point& p, const Square& s);
bool isPointOnCircle(const Point& p, const Circle& c);
bool isPointOnSquare(const Point& p, const Square& s);

// Проверка пересечений
bool doCirclesIntersect(const Circle& c1, const Circle& c2);
bool doSquaresIntersect(const Square& s1, const Square& s2);
bool doCircleAndSquareIntersect(const Circle& c, const Square& s);

// Дополнительные функции пересечения
bool doCirclesStrictlyIntersect(const Circle& c1, const Circle& c2);
bool doSquaresStrictlyIntersect(const Square& s1, const Square& s2);

// Проверка принадлежности фигур
bool isCircleInsideSquare(const Circle& c, const Square& s);
bool isSquareInsideSquare(const Square& s1, const Square& s2);
bool isSquareInsideCircle(const Square& s, const Circle& c);

#endif