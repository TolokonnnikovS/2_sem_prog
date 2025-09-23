#include <iostream>
#include <cmath>
using namespace std;

struct Point{
    void readPoint(Point& p) {
        cout << "Введите координату x: ";
        cin >> p.x;
        cout << "Введите координату y: ";
        cin >> p.y;
    }
};

void printPoint(const Point& p) {
    cout << "(" << p.x << ", " << p.y << ")";
}

struct Circle{
    float r, dl, S;
    void readCircle(Circle& c) {
        cout << "Введите координаты центра круга:\n";
        cin >> c.r;
    }
    void DlCircle(Circle& a) {
        a.dl = 2 * 3.14 * a.r;
        std::cout << a.dl << \n;
    }               
    void SCircle(Circle& b) {
        b.S = 4 * 3.14 * pow(b.r, 2)
        std::cout << b.S << \n;
    }
};

struct Square{
    float dls, sh;
};

int main() {

    Point a;
    Circle b;
    Square c;
    
    



}