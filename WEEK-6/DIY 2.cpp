#include <iostream>
#include <numeric> 

class Fraction {
private:
    int num;
    int den;

    void simplify() {
        if (den == 0) {
            std::cerr << "Error: Denominator cannot be zero." << std::endl;
            return;
        }
        int common = std::gcd(num, den);
        num /= common;
        den /= common;
       
        if (den < 0) {
            num = -num;
            den = -den;
        }
    }

public:
    Fraction(int n = 0, int d = 1) : num(n), den(d) {
        simplify();
    }

   
    friend std::ostream& operator<<(std::ostream& os, const Fraction& f) {
        if (f.den == 1) {
            os << f.num;
        } else {
            os << f.num << "/" << f.den;
        }
        return os;
    }

    
    friend std::istream& operator>>(std::istream& is, Fraction& f) {
        char slash;
        is >> f.num >> slash >> f.den;
        f.simplify();
        return is;
    }
};

int main() {
    Fraction f1(12, 18);
    std::cout << "Auto-simplified fraction (12/18): " << f1 << std::endl;

    Fraction f2;
    std::cout << "Enter a fraction in the format num/den: ";
    std::cin >> f2;
    std::cout << "You entered (simplified): " << f2 << std::endl;

    return 0;
}
