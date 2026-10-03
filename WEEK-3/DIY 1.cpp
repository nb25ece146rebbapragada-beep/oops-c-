#include <iostream>
using namespace std;

class Rectangle {
private:
    double length;
    double width;

public:
    Rectangle() : length(0), width(0) {}

    void setLength(double l) {
        if (l < 0) {
            cout << "Error: length cannot be negative. Value unchanged." << endl;
            return;
        }
        length = l;
    }

    void setWidth(double w) {
        if (w < 0) {
            cout << "Error: width cannot be negative. Value unchanged." << endl;
            return;
        }
        width = w;
    }

    double area() const {
        return length * width;
    }

    double perimeter() const {
        return 2 * (length + width);
    }
};

int main() {
    Rectangle r;
    r.setLength(5);
    r.setWidth(3);
    cout << "Area: " << r.area() << endl;
    cout << "Perimeter: " << r.perimeter() << endl;

     r.setLength(-2);   // rejected
    cout << "Area after invalid set: " << r.area() << endl;
    return 0;
}