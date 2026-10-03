#include <iostream>
using namespace std;

class Counter {
private:
    int count;
    static int totalCreated;   // objects ever created
    static int alive;          // objects currently alive

public:
    Counter() : count(0) {
        totalCreated++;
        alive++;
    }

    // Copies are new objects too, so they must be counted
    Counter(const Counter& other) : count(other.count) {
        totalCreated++;
        alive++;
    }

    ~Counter() {
        alive--;
    }

    void increment() { count++; }
    void reset()     { count = 0; }
    int get() const  { return count; }

    static int getTotalCreated() { return totalCreated; }
    static int getAlive()        { return alive; }
};

// Definitions of the static members (required, outside the class)
int Counter::totalCreated = 0;
int Counter::alive = 0;

void report(const char* label) {
    cout << label << " -> created: " << Counter::getTotalCreated()
         << ", alive: " << Counter::getAlive() << endl;
}

int main() {
    report("Start");

    Counter a, b;
    report("After a, b");

    {
        Counter arr[3];
        report("Inside block (array of 3)");
    }
    report("After block ends");

    Counter* p = new Counter;
    report("After new Counter");
    delete p;
    report("After delete");

    return 0;
}