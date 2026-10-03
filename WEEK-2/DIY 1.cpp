#include <iostream>
using namespace std;

const double PI = 3.14159265358979;

// Cube: side
double volume(double side) {
    return side * side * side;
}

// Cylinder: radius, height
double volume(double radius, double height) {
    return PI * radius * radius * height;
}

// Cuboid: length, breadth, height
double volume(double l, double b, double h) {
    return l * b * h;
}

int main() {
    cout << "Cube (side 3): " << volume(3.0) << endl;
    cout << "Cuboid (2 x 3 x 4): " << volume(2.0, 3.0, 4.0) << endl;
    cout << "Cylinder (r=2, h=5): " << volume(2.0, 5.0) << endl;
    return 0;
}