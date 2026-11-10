#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Logger {
public:
    virtual void write(const string& msg) = 0;
    virtual ~Logger() {}
};

class ConsoleLogger : public Logger {
public:
    void write(const string& msg) override {
        cout << "[Console] " << msg << endl;
    }
};

class FileLogger : public Logger {
    ofstream file;
public:
    FileLogger(const string& name) {
        file.open(name, ios::app);
    }
    void write(const string& msg) override {
        file << "[File] " << msg << endl;
    }
    ~FileLogger() {
        file.close();
    }
};

int main() {
    ConsoleLogger console;
    FileLogger fileLog("log.txt");
    Logger* logger = &console;

    int choice;
    do {
        cout << "1. Console  2. File  0. Exit: ";
        cin >> choice;
        if (choice == 1) {
            logger = &console;
            logger->write("Logging to console");
        } else if (choice == 2) {
            logger = &fileLog;
            logger->write("Logging to file");
            cout << "Written to log.txt" << endl;
        }
    } while (choice != 0);

    return 0;
}