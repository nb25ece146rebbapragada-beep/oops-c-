#include <iostream>
#include <string>
using namespace std;

class Student {
public:
    string name;
    int age;
    Student(string n, int a) : name(n), age(a) {}
    void show() const { cout << name << " (" << age << ")" << endl; }
};

int main() {
    int n;
    cout << "How many marks? ";
    cin >> n;

    int* marks = new int[n];
    for (int i = 0; i < n; i++) cin >> marks[i];

    Student* s = new Student("Asha", 21);
    s->show();

    int sum = 0;
    for (int i = 0; i < n; i++) sum += marks[i];
    cout << "Total: " << sum << endl;

    delete s;
    delete[] marks;
    return 0;
}