#include <iostream>
#include <string>
using namespace std;

class Person {
protected:
    string name;
public:
    Person(string n = "Unknown") : name(n) {
        cout << "Person constructor called" << endl;
    }
    void showPerson() const { cout << "Name: " << name << endl; }
};


class Student : virtual public Person {
protected:
    int rollNo;
public:
    Student(string n, int r) : Person(n), rollNo(r) {
        cout << "Student constructor called" << endl;
    }
};

class Employee : virtual public Person {
protected:
    int empId;
public:
    Employee(string n, int e) : Person(n), empId(e) {
        cout << "Employee constructor called" << endl;
    }
};

class TA : public Student, public Employee {
    string course;
public:
    
    TA(string n, int r, int e, string c)
        : Person(n), Student(n, r), Employee(n, e), course(c) {
        cout << "TA constructor called" << endl;
    }
    void display() const {
        showPerson();  
        cout << "Roll No: " << rollNo << ", Emp ID: " << empId
             << ", Course assisted: " << course << endl;
    }
};

int main() {
    TA t("Meera", 2301, 9001, "C++ Programming");
    cout << endl;
    t.display();
    return 0;
}
