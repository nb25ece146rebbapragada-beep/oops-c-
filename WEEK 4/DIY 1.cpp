#include <iostream>
using namespace std;

class Matrix {
private:
    int rows, cols;
    int** data;

    void allocate() {
        data = new int*[rows];
        for (int i = 0; i < rows; i++)
            data[i] = new int[cols]();   // () zero-initializes
    }

    void release() {
        for (int i = 0; i < rows; i++)
            delete[] data[i];
        delete[] data;
    }

public:
    Matrix(int m, int n) : rows(m), cols(n), data(nullptr) {
        allocate();
    }

    // Deep copy constructor
    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols), data(nullptr) {
        allocate();
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                data[i][j] = other.data[i][j];
    }

    // Copy assignment (Rule of Three)
    Matrix& operator=(const Matrix& other) {
        if (this == &other) return *this;
        release();
        rows = other.rows;
        cols = other.cols;
        allocate();
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                data[i][j] = other.data[i][j];
        return *this;
    }

    ~Matrix() {
        release();
        cout << "Matrix " << rows << "x" << cols << " freed" << endl;
    }

    void set(int i, int j, int value) { data[i][j] = value; }
    int get(int i, int j) const { return data[i][j]; }

    void display() const {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++)
                cout << data[i][j] << " ";
            cout << endl;
        }
    }
};

int main() {
    Matrix a(2, 3);
    int v = 1;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++)
            a.set(i, j, v++);

    Matrix b = a;        // deep copy
    b.set(0, 0, 99);     // must not affect a

    cout << "Matrix a:" << endl;
    a.display();
    cout << "Matrix b (copy, modified):" << endl;
    b.display();
    return 0;
}