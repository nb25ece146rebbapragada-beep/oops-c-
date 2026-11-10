#include <iostream>
using namespace std;

class Shape {
protected:
    string name;
public:
    Shape(string n) : name(n) {
        cout << "Shape constructor called (name = " << name << ")" << endl;
    }
    ~Shape() { cout << "Shape destructor called" << endl; }
};

class Polygon : public Shape {
protected:
    int sides;
public:
    Polygon(string n, int s) : Shape(n), sides(s) {
        cout << "Polygon constructor called (sides = " << sides << ")" << endl;
    }
    ~Polygon() { cout << "Polygon destructor called" << endl; }
};

class Rectangle : public Polygon {
    double length, width;
public:
    Rectangle(double l, double w) : Polygon("Rectangle", 4), length(l), width(w) {
        cout << "Rectangle constructor called (" << length << " x " << width << ")" << endl;
    }
    ~Rectangle() { cout << "Rectangle destructor called" << endl; }
    void display() const {
        cout << "Name: " << name << ", Sides: " << sides
             << ", Area: " << length * width << endl;
    }
};

int main() {
    cout << "Creating Rectangle object:" << endl;
    Rectangle r(5, 3);
    cout << endl;
    r.display();
    cout << endl << "Object going out of scope:" << endl;
    return 0;
}
