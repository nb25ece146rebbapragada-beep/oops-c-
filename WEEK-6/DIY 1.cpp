#include <iostream>
#include <cmath>

class Money {
private:
    long rupees;
    int paise;

    void normalize() {
        
        if (paise >= 100) {
            rupees += paise / 100;
            paise %= 100;
        } else if (paise < 0) {
            int borrow = (abs(paise) + 99) / 100;
            rupees -= borrow;
            paise += borrow * 100;
        }
    }

public:
    Money(long r = 0, int p = 0) : rupees(r), paise(p) {
        normalize();
    }

    
    Money operator+(const Money& other) const {
        return Money(rupees + other.rupees, paise + other.paise);
    }

    
    Money operator-(const Money& other) const {
        return Money(rupees - other.rupees, paise - other.paise);
    }

    void display() const {
        std::cout << "Rs. " << rupees << "." << (paise < 10 ? "0" : "") << paise << std::endl;
    }
};

int main() {
    Money m1(50, 75);
    Money m2(20, 50);

    Money sum = m1 + m2;
    Money diff = m1 - m2;

    std::cout << "m1: "; m1.display();
    std::cout << "m2: "; m2.display();
    std::cout << "Sum: "; sum.display();
    std::cout << "Difference: "; diff.display();

    return 0;
}
