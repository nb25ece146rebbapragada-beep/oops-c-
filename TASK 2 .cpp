#include <algorithm>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

const int    NUM_SUBJECTS = 5;
const double MAX_MARK     = 100.0;   // maximum marks per subject
const double PASS_MARK    = 40.0;    // minimum marks to pass a subject
const string DATA_FILE    = "students.txt";
const string SUBJECTS[NUM_SUBJECTS] = {"Maths", "Physics", "Electronics",
                                       "Programming", "English"};

class InvalidMarksException : public runtime_error {
public:
    explicit InvalidMarksException(const string& msg) : runtime_error(msg) {}
};

// Small helper: number -> text without trailing zeros (88, 87.5, 410)
string plain(double v) {
    ostringstream os;
    os << v;
    return os.str();
}

class Student {
protected:
    int    rollNo;
    string name;
    string department;

public:
    Student(int r = 0, const string& n = "", const string& d = "")
        : rollNo(r), name(n), department(d) {}

    virtual ~Student() {}                       // virtual destructor

    int           getRollNo()     const { return rollNo; }
    const string& getName()       const { return name; }
    const string& getDepartment() const { return department; }

    // Virtual functions: derived classes may override them
    virtual void displayDetails() const {
        cout << "Roll No      : " << rollNo     << '\n'
             << "Name         : " << name       << '\n'
             << "Department   : " << department << '\n';
    }

    virtual void displayMarks() const {
        cout << "Marks        : not available for a plain Student\n";
    }
};

class Result : public Student {
private:
    vector<double> marks;      // one entry per subject
    double         total;
    double         percentage;

    void calculate() {
        total = 0;
        for (double m : marks) total += m;
        percentage = total / (NUM_SUBJECTS * MAX_MARK) * 100.0;
    }

public:
    // Throws InvalidMarksException if a mark is outside 0..MAX_MARK
    static void validateMark(double m, int subject) {
        if (m < 0 || m > MAX_MARK) {
            throw InvalidMarksException("Invalid marks " + plain(m) + " for " +
                                        SUBJECTS[subject] + " (allowed range 0-" +
                                        plain(MAX_MARK) + ")");
        }
    }

    Result(int r, const string& n, const string& d, const vector<double>& m)
        : Student(r, n, d), marks(m), total(0), percentage(0) {
        if ((int)marks.size() != NUM_SUBJECTS)
            throw InvalidMarksException("Exactly " + to_string(NUM_SUBJECTS) +
                                        " subject marks are required");
        for (int i = 0; i < NUM_SUBJECTS; i++) validateMark(marks[i], i);
        calculate();
    }

    double getTotal()      const { return total; }
    double getPercentage() const { return percentage; }

    string getGrade() const {
        if (percentage >= 90) return "A+";
        if (percentage >= 80) return "A";
        if (percentage >= 70) return "B";
        if (percentage >= 60) return "C";
        if (percentage >= 50) return "D";
        if (percentage >= 40) return "E";
        return "F";
    }

    // A student passes only if every subject is at or above PASS_MARK
    bool isPass() const {
        return all_of(marks.begin(), marks.end(),
                      [](double m) { return m >= PASS_MARK; });
    }
    string getStatus() const { return isPass() ? "PASS" : "FAIL"; }

    // Overridden virtual functions
    void displayDetails() const override {
        cout << "=========== STUDENT RESULT CARD ===========\n";
        Student::displayDetails();                 // reuse the base version
    }

    void displayMarks() const override {
        cout << "-------------------------------------------\n";
        cout << left << setw(20) << "Subject" << "Marks\n";
        for (int i = 0; i < NUM_SUBJECTS; i++)
            cout << left << setw(20) << SUBJECTS[i] << plain(marks[i]) << '\n';
        cout << "-------------------------------------------\n";
        cout << "Total Marks  : " << plain(total) << " / "
             << plain(NUM_SUBJECTS * MAX_MARK) << '\n';
        cout << "Percentage   : " << fixed << setprecision(2) << percentage
             << " %\n" << defaultfloat;
        cout << "Grade        : " << getGrade()  << '\n';
        cout << "Result       : " << getStatus() << '\n';
    }

    // One line of the data file:  roll,name,department,m1,m2,m3,m4,m5
    string toCSV() const {
        ostringstream os;
        os << rollNo << ',' << name << ',' << department;
        for (double m : marks) os << ',' << m;
        return os.str();
    }
};

// ---------------------------------------------------------------------------
//  Parsing helpers (all throw exceptions on bad input)
// ---------------------------------------------------------------------------
double parseMark(const string& s) {
    size_t pos = 0;
    double v = 0;
    try {
        v = stod(s, &pos);
    } catch (const exception&) {
        throw InvalidMarksException("'" + s + "' is not a number");
    }
    while (pos < s.size() && isspace((unsigned char)s[pos])) pos++;
    if (pos != s.size())
        throw InvalidMarksException("'" + s + "' is not a number");
    return v;
}

int parseRoll(const string& s) {
    size_t pos = 0;
    int v = 0;
    try {
        v = stoi(s, &pos);
    } catch (const exception&) {
        throw runtime_error("Roll number must be a whole number");
    }
    if (pos != s.size() || v <= 0)
        throw runtime_error("Roll number must be a positive whole number");
    return v;
}

// Build a Result from one line of the data file
Result parseRecord(const string& line) {
    vector<string> f;
    string item;
    istringstream ss(line);
    while (getline(ss, item, ',')) f.push_back(item);

    if ((int)f.size() != 3 + NUM_SUBJECTS)
        throw runtime_error("Malformed record (expected " +
                            to_string(3 + NUM_SUBJECTS) + " fields)");

    vector<double> m;
    for (int i = 0; i < NUM_SUBJECTS; i++) m.push_back(parseMark(f[3 + i]));
    return Result(parseRoll(f[0]), f[1], f[2], m);   // validates the marks
}

// ---------------------------------------------------------------------------
//  Operations on the vector of records
// ---------------------------------------------------------------------------
bool rollExists(const vector<Result>& records, int roll) {
    return any_of(records.begin(), records.end(),
                  [roll](const Result& r) { return r.getRollNo() == roll; });
}

void addStudent(vector<Result>& records) {
    string line;

    cout << "Roll No      : ";
    getline(cin, line);
    int roll = parseRoll(line);
    if (rollExists(records, roll))
        throw runtime_error("Roll number " + to_string(roll) + " already exists");

    cout << "Name         : ";
    string name;
    getline(cin, name);
    replace(name.begin(), name.end(), ',', ' ');   // ',' is the file separator
    if (name.empty()) throw runtime_error("Name cannot be empty");

    cout << "Department   : ";
    string dept;
    getline(cin, dept);
    replace(dept.begin(), dept.end(), ',', ' ');

    vector<double> marks;
    for (int i = 0; i < NUM_SUBJECTS; i++) {
        while (true) {                       // keep asking until the mark is valid
            cout << "Marks in " << left << setw(12) << SUBJECTS[i] << ": ";
            getline(cin, line);
            try {
                double m = parseMark(line);
                Result::validateMark(m, i);
                marks.push_back(m);
                break;
            } catch (const InvalidMarksException& e) {
                cout << "  Error: " << e.what() << ". Please re-enter.\n";
            }
        }
    }
    records.emplace_back(roll, name, dept, marks);
    cout << "Record added successfully.\n";
}

void displayAll(const vector<Result>& records) {
    if (records.empty()) {
        cout << "No records to display.\n";
        return;
    }
    for (const Result& r : records) {
        const Student& s = r;        // base-class reference -> runtime polymorphism
        s.displayDetails();          // calls Result::displayDetails()
        s.displayMarks();            // calls Result::displayMarks()
        cout << '\n';
    }
    cout << "Total records: " << records.size() << '\n';
}

void showAboveMark(const vector<Result>& records, double threshold) {
    vector<Result> selected;

    // STL algorithm + lambda: copy every record whose total exceeds threshold
    copy_if(records.begin(), records.end(), back_inserter(selected),
            [threshold](const Result& r) { return r.getTotal() > threshold; });

    // Lambda comparator: highest total first
    sort(selected.begin(), selected.end(),
         [](const Result& a, const Result& b) { return a.getTotal() > b.getTotal(); });

    cout << "\nStudents scoring above " << plain(threshold) << " marks: "
         << selected.size() << '\n';
    if (selected.empty()) return;

    cout << string(76, '-') << '\n'
         << left << setw(6) << "Roll" << setw(20) << "Name" << setw(8) << "Dept"
         << setw(9) << "Total" << setw(10) << "Percent" << setw(7) << "Grade"
         << "Result\n" << string(76, '-') << '\n';
    for (const Result& r : selected) {
        ostringstream pct;
        pct << fixed << setprecision(2) << r.getPercentage();
        cout << left << setw(6) << r.getRollNo() << setw(20) << r.getName()
             << setw(8) << r.getDepartment() << setw(9) << plain(r.getTotal())
             << setw(10) << pct.str() << setw(7) << r.getGrade()
             << r.getStatus() << '\n';
    }
    cout << string(76, '-') << '\n';
}

// ---------------------------------------------------------------------------
//  File handling
// ---------------------------------------------------------------------------
void saveToFile(const vector<Result>& records, const string& filename) {
    ofstream out(filename);
    if (!out) throw runtime_error("Cannot open '" + filename + "' for writing");
    for (const Result& r : records) out << r.toCSV() << '\n';
    cout << records.size() << " record(s) saved to " << filename << '\n';
}

void loadFromFile(vector<Result>& records, const string& filename) {
    ifstream in(filename);
    if (!in) throw runtime_error("Cannot open '" + filename + "' for reading");

    vector<Result> loaded;
    string line;
    int lineNo = 0, skipped = 0;
    while (getline(in, line)) {
        lineNo++;
        if (line.empty()) continue;
        try {
            loaded.push_back(parseRecord(line));
        } catch (const exception& e) {          // bad line: report it and carry on
            cout << "  Skipping line " << lineNo << ": " << e.what() << '\n';
            skipped++;
        }
    }
    records = loaded;
    cout << records.size() << " record(s) loaded from " << filename;
    if (skipped) cout << " (" << skipped << " skipped)";
    cout << '\n';
}

// ---------------------------------------------------------------------------
//  main : menu-driven program
// ---------------------------------------------------------------------------
int main() {
    vector<Result> records;
    string choice;

    cout << "====== STUDENT RESULT MANAGEMENT SYSTEM ======\n";
    while (true) {
        cout << "\n1. Add student record"
             << "\n2. Display all records"
             << "\n3. Find students scoring above a mark"
             << "\n4. Save records to file"
             << "\n5. Load records from file"
             << "\n6. Exit"
             << "\nEnter choice: ";
        if (!getline(cin, choice)) break;       // end of input

        try {
            if (choice == "1") {
                addStudent(records);
            } else if (choice == "2") {
                displayAll(records);
            } else if (choice == "3") {
                cout << "Enter minimum total marks (out of "
                     << plain(NUM_SUBJECTS * MAX_MARK) << "): ";
                string line;
                getline(cin, line);
                showAboveMark(records, parseMark(line));
            } else if (choice == "4") {
                saveToFile(records, DATA_FILE);
            } else if (choice == "5") {
                loadFromFile(records, DATA_FILE);
            } else if (choice == "6") {
                cout << "Goodbye!\n";
                break;
            } else {
                cout << "Invalid choice. Please enter 1-6.\n";
            }
        } catch (const InvalidMarksException& e) {
            cout << "Invalid marks error: " << e.what() << '\n';
        } catch (const exception& e) {
            cout << "Error: " << e.what() << '\n';
        }
    }
    return 0;
}
