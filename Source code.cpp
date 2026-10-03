#include <iostream>
#include <string>
using namespace std;

class Student {
private:                      
    string name;
    int rollNo;
    float marks;
    static int count;          

public:
    
    Student(string n, int r, float m) : name(n), rollNo(r), marks(m) {
        count++;
    }


    Student(const Student& other)
        : name(other.name), rollNo(other.rollNo), marks(other.marks) {
        count++;
    }

    ~Student() { count--; }


    string getName() const { return name; }
    int getRollNo() const { return rollNo; }
    float getMarks() const { return marks; }


    void setMarks(float m) {                       
        marks = m;
    }
    void setMarks(float m1, float m2, float m3) {  
        marks = (m1 + m2 + m3) / 3;
    }

    
    void display() const {
        cout << "Name: " << name << ", Roll No: " << rollNo
             << ", Marks: " << marks << endl;
    }
    void display(bool showGrade) const {
        display();
        if (showGrade) {
            char grade = marks >= 90 ? 'A' : marks >= 75 ? 'B'
                       : marks >= 60 ? 'C' : marks >= 40 ? 'D' : 'F';
            cout << "Grade: " << grade << endl;
        }
    }


    static int getCount() { return count; }


    bool operator>(const Student& other) const {
        return marks > other.marks;
    }

    
    friend void showPrivateDetails(const Student& s);
};

int Student::count = 0;       

void showPrivateDetails(const Student& s) {
    cout << "[Friend] " << s.name << " (Roll " << s.rollNo
         << ") scored " << s.marks << endl;
}

int main() {
    Student s1("Akshitha", 101, 85.5f);
    Student s2("Preetham", 102, 78.0f);
    Student s3("Gagan", 103, 0);

    s3.setMarks(90, 88, 95);  
    s2.setMarks(82.5f);       

    
    s1.display();             
    s2.display(true);          
    s3.display(true);

    showPrivateDetails(s1);


    if (s1 > s2)
        cout << s1.getName() << " has higher marks than " << s2.getName() << endl;
    else
        cout << s2.getName() << " has higher or equal marks compared to "
             << s1.getName() << endl;

    if (s3 > s1)
        cout << s3.getName() << " has higher marks than " << s1.getName() << endl;

    cout << "\nTotal students: " << Student::getCount() << endl;

    {
        Student temp("Temp", 999, 50);
        cout << "Inside block, total students: " << Student::getCount() << endl;
    }
    cout << "After block, total students: " << Student::getCount() << endl;

    return 0;
}
