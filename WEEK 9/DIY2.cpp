#include <iostream>
#include <exception>
using namespace std;

class Overflow : public exception {
public:
    const char* what() const noexcept override {
        return "Stack Overflow";
    }
};

class Underflow : public exception {
public:
    const char* what() const noexcept override {
        return "Stack Underflow";
    }
};

class Stack {
    int arr[5];
    int top;
public:
    Stack() : top(-1) {}
    void push(int x) {
        if (top == 4) {
            throw Overflow();
        }
        arr[++top] = x;
    }
    int pop() {
        if (top == -1) {
            throw Underflow();
        }
        return arr[top--];
    }
};

int main() {
    Stack s;
    try {
        for (int i = 1; i <= 6; i++) {
            s.push(i * 10);
            cout << "Pushed " << i * 10 << endl;
        }
    } catch (const Overflow& e) {
        cout << "Error: " << e.what() << endl;
    }

    try {
        for (int i = 0; i < 6; i++) {
            cout << "Popped " << s.pop() << endl;
        }
    } catch (const Underflow& e) {
        cout << "Error: " << e.what() << endl;
    }
    return 0;
}