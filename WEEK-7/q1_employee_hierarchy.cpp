#include <iostream>
#include <string>
using namespace std;

class Employee {
protected:
    string name;
    int id;
public:
    Employee(string n, int i) : name(n), id(i) {}
    void display() const {
        cout << "Name: " << name << ", ID: " << id << endl;
    }
};

class Manager : public Employee {
    int teamSize;
public:
    Manager(string n, int i, int t) : Employee(n, i), teamSize(t) {}
    void display() const {
        cout << "[Manager] ";
        Employee::display();
        cout << "Team size: " << teamSize << endl;
    }
};

class Engineer : public Employee {
    string skill;
public:
    Engineer(string n, int i, string s) : Employee(n, i), skill(s) {}
    void display() const {
        cout << "[Engineer] ";
        Employee::display();
        cout << "Skill: " << skill << endl;
    }
};

int main() {
    Employee e("Ravi", 101);
    Manager m("Anita", 102, 8);
    Engineer g("Kiran", 103, "Embedded C");

    cout << "[Employee] ";
    e.display();
    cout << endl;
    m.display();
    cout << endl;
    g.display();
    return 0;
}
