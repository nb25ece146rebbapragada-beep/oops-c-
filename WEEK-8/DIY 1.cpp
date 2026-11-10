#include <iostream>
using namespace std;

class Account {
protected:
    double balance;
public:
    Account(double b) : balance(b) {}
    virtual double calculateInterest() const = 0;
    virtual void show() const = 0;
    virtual ~Account() {}
};

class Savings : public Account {
public:
    Savings(double b) : Account(b) {}
    double calculateInterest() const override {
        return balance * 0.04;
    }
    void show() const override {
        cout << "Savings   balance: " << balance << "  interest: " << calculateInterest() << endl;
    }
};

class Current : public Account {
public:
    Current(double b) : Account(b) {}
    double calculateInterest() const override {
        return balance * 0.01;
    }
    void show() const override {
        cout << "Current   balance: " << balance << "  interest: " << calculateInterest() << endl;
    }
};

int main() {
    Account* accounts[4];
    accounts[0] = new Savings(10000);
    accounts[1] = new Current(25000);
    accounts[2] = new Savings(5000);
    accounts[3] = new Current(8000);

    double total = 0;
    for (int i = 0; i < 4; i++) {
        accounts[i]->show();
        total += accounts[i]->calculateInterest();
    }
    cout << "Total interest: " << total << endl;

    for (int i = 0; i < 4; i++) {
        delete accounts[i];
    }
    return 0;
}