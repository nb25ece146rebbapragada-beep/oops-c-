#include <iostream>
using namespace std;

class Counter {
private:
    int count;

public:
    Counter() : count(0) {}

    void increment() { count++; }
    void reset()     { count = 0; }
    int get() const  { return count; }
};

int main() {
    Counter c[3];

    c[0].increment();
    c[0].increment();
    c[0].increment();

    c[1].increment();

    // c[2] is left untouched

    cout << "Before reset:" << endl;
    for (int i = 0; i < 3; i++)
        cout << "Counter " << i << ": " << c[i].get() << endl;

    c[0].reset();

    cout << "After resetting counter 0:" << endl;
    for (int i = 0; i < 3; i++)
        cout << "Counter " << i << ": " << c[i].get() << endl;

    return 0;
}