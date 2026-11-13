#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <cctype>
using namespace std;

const double PI = 3.14159265358979;

class Shape {
public:
    virtual double area() const = 0;
    virtual string name() const = 0;
    virtual ~Shape() = default;
};

class Circle : public Shape {
    double r;
public:
    Circle(double r) : r(r) {}
    double area() const override { return PI * r * r; }
    string name() const override { return "Circle"; }
};

class Rectangle : public Shape {
    double w, h;
public:
    Rectangle(double w, double h) : w(w), h(h) {}
    double area() const override { return w * h; }
    string name() const override { return "Rectangle"; }
};

class Triangle : public Shape {
    double b, h;
public:
    Triangle(double b, double h) : b(b), h(h) {}
    double area() const override { return 0.5 * b * h; }
    string name() const override { return "Triangle"; }
};

// Factory: returns nullptr for an unknown shape name
unique_ptr<Shape> createShape(const string& type) {
    if (type == "circle") {
        double r;
        cout << "  Radius: ";
        cin >> r;
        return make_unique<Circle>(r);
    }
    if (type == "rectangle") {
        double w, h;
        cout << "  Width and height: ";
        cin >> w >> h;
        return make_unique<Rectangle>(w, h);
    }
    if (type == "triangle") {
        double b, h;
        cout << "  Base and height: ";
        cin >> b >> h;
        return make_unique<Triangle>(b, h);
    }
    return nullptr;
}

int main() {
    vector<unique_ptr<Shape>> shapes;
    string input;

    cout << "Enter shape name (circle / rectangle / triangle), or 'done' to finish.\n";
    while (true) {
        cout << "Shape: ";
        cin >> input;
        transform(input.begin(), input.end(), input.begin(),
                  [](unsigned char c) { return tolower(c); });

        if (input == "done") break;

        unique_ptr<Shape> s = createShape(input);
        if (s)
            shapes.push_back(move(s));   // unique_ptr must be moved
        else
            cout << "  Unknown shape, try again.\n";
    }

    cout << "\nCreated shapes:\n";
    for (const auto& s : shapes)
        cout << s->name() << " -> area = " << s->area() << endl;

    return 0;   // vector destroys every shape automatically
}