#ifndef STRUCTS_H
#define STRUCTS_H

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

#endif