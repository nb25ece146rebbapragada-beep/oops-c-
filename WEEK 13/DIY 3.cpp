#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

int counter = 0;
mutex mtx;

void work() {
    for (int i = 0; i < 100000; i++) {
#ifdef USE_LOCK
        lock_guard<mutex> lock(mtx);
#endif
        counter++;
    }
}

int main() {
    for (int run = 1; run <= 5; run++) {
        counter = 0;
        thread t1(work);
        thread t2(work);
        t1.join();
        t2.join();
        cout << "Run " << run << ": total = " << counter
             << (counter == 200000 ? "  (correct)" : "  (WRONG)") << endl;
    }
    return 0;
}