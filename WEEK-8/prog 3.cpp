#include <iostream>
using namespace std;

class Shape {
    public:
    virtual double area() const = 0;
    virtual void name() const = 0;
    virtual ~Shape() { }
};
class Circle : public Shape {
    double radius;
    public:
    Circle(double r) : radius(r) { }
    double area() const override { return 3.14159 * radius * radius; }
    void name() const override { cout << "Circle\n"; }
};
class Square : public Shape {
    double side;
    public:
    Square(double s) : side(s) { }
    double area() const override { return side * side; }
    void name() const override { cout << "Square\n"; }
};
int main(){
    Shape* shapes[] = { new Circle(2), new Square(3) };
    for (Shape* s : shapes) {
        s->name();
        cout << "Area: " << s->area() << endl;
    }
    for(Shape* s : shapes) delete s;
    return 0;
}
    