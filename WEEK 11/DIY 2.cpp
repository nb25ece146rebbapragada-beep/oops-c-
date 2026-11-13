#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& val) : data(val), next(nullptr) {}
    };

    Node* frontPtr;
    Node* rearPtr;
    int count;

public:
    Queue() : frontPtr(nullptr), rearPtr(nullptr), count(0) {}

    ~Queue() {
        while (!isEmpty())
            dequeue();
    }

    bool isEmpty() const {
        return count == 0;
    }

    int size() const {
        return count;
    }

    void enqueue(const T& value) {
        Node* newNode = new Node(value);
        if (rearPtr == nullptr) {
            frontPtr = rearPtr = newNode;
        } else {
            rearPtr->next = newNode;
            rearPtr = newNode;
        }
        count++;
    }

    void dequeue() {
        if (isEmpty())
            throw runtime_error("Queue is empty, cannot dequeue");
        Node* temp = frontPtr;
        frontPtr = frontPtr->next;
        if (frontPtr == nullptr)
            rearPtr = nullptr;
        delete temp;
        count--;
    }

    T& front() {
        if (isEmpty())
            throw runtime_error("Queue is empty, no front element");
        return frontPtr->data;
    }
};

int main() {
    Queue<string> q;

    q.enqueue("Alice");
    q.enqueue("Bob");
    q.enqueue("Charlie");

    cout << "Queue size: " << q.size() << endl;
    cout << "Front: " << q.front() << endl;

    q.dequeue();
    cout << "After one dequeue, front: " << q.front() << endl;

    q.dequeue();
    cout << "After two dequeues, front: " << q.front() << endl;

    q.dequeue();
    cout << "Is queue empty? " << (q.isEmpty() ? "Yes" : "No") << endl;

    try {
        q.dequeue();
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}