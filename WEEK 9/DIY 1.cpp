#include <iostream>
#include <string>
#include <exception>
using namespace std;

class InsufficientFunds : public exception {
    string msg;
public:
    InsufficientFunds(double balance, double requested) {
        msg = "Insufficient funds: balance " + to_string(balance) + ", requested " + to_string(requested);
    }
    const char* what() const noexcept override {
        return msg.c_str();
    }
};

class BankAccount {
    double balance;
public:
    BankAccount(double b = 0) : balance(b) {}
    void deposit(double amt) {
        balance += amt;
    }
    void withdraw(double amt) {
        if (amt > balance) {
            throw InsufficientFunds(balance, amt);
        }
        balance -= amt;
    }
    double getBalance() const {
        return balance;
    }
};

int main() {
    BankAccount acc(500);
    try {
        acc.withdraw(200);
        cout << "Balance: " << acc.getBalance() << endl;
        acc.withdraw(400);
        cout << "Balance: " << acc.getBalance() << endl;
    } catch (const InsufficientFunds& e) {
        cout << "Error: " << e.what() << endl;
    }
    return 0;
}