#include <iostream>
using namespace std;

class Time {
private:
    int hh;
    int mm;

public:
    Time(int h = 0, int m = 0) {
        // Normalize so 90 minutes becomes 1:30
        hh = h + m / 60;
        mm = m % 60;
        if (mm < 0) { mm += 60; hh--; }
    }

    void display() const {
        if (hh < 10) cout << '0';
        cout << hh << ':';
        if (mm < 10) cout << '0';
        cout << mm;
    }

    friend Time laterOf(Time a, Time b);
};

// Not a member: accesses private hh and mm because it is a friend
Time laterOf(Time a, Time b) {
    if (a.hh != b.hh)
        return (a.hh > b.hh) ? a : b;
    return (a.mm >= b.mm) ? a : b;
}

int main() {
    Time t1(9, 45), t2(14, 5), t3(14, 30);

    cout << "Later of ";
    t1.display(); cout << " and "; t2.display();
    cout << " is "; laterOf(t1, t2).display(); cout << endl;

    cout << "Later of ";
    t2.display(); cout << " and "; t3.display();
    cout << " is "; laterOf(t2, t3).display(); cout << endl;

    return 0;
}