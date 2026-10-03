#include <iostream>
#include <string>
using namespace std;

class Order {
private:
    int id;
    string item;
    static int nextId;

public:
    Order(const string& itemName) : id(nextId++), item(itemName) {
        cout << "Created order " << id << " for " << item << endl;
    }

    int getId() const { return id; }
    string getItem() const { return item; }
};

int Order::nextId = 1001;

int main() {
    Order o1("Keyboard");
    Order o2("Monitor");
    Order o3("Mouse");

    cout << "IDs: " << o1.getId() << ", "
         << o2.getId() << ", " << o3.getId() << endl;

    return 0;
}