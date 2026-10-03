#include <iostream>
using namespace std;

class Tracer {
private:
    int id;

public:
    Tracer(int i) : id(i) {
        cout << "  Tracer " << id << " created" << endl;
    }
    ~Tracer() {
        cout << "  Tracer " << id << " destroyed" << endl;
    }
};

int main() {
    cout << "Loop 1: with delete" << endl;
    for (int i = 1; i <= 3; i++) {
        Tracer* t = new Tracer(i);
        delete t;                     // destructor runs here
    }

    cout << "Loop 2: forgot delete (leaks)" << endl;
    for (int i = 4; i <= 6; i++) {
        Tracer* t = new Tracer(i);
        // no delete: destructor never runs, memory is lost
    }

    cout << "End of main" << endl;
    return 0;
}