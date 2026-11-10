#include <iostream>
using namespace std;

class Base {
public:
    Base() {
        cout << "Base constructed" << endl;
    }
    ~Base() {
        cout << "Base destroyed" << endl;
    }
};

class Derived : public Base {
    int* data;
public:
    Derived() {
        data = new int[100];
        cout << "Derived constructed, memory allocated" << endl;
    }
    ~Derived() {
        delete[] data;
        cout << "Derived destroyed, memory freed" << endl;
    }
};

int main() {
    Base* p = new Derived();
    delete p;
    return 0;
}