#include <iostream>
#include <map>
#include <string>
using namespace std;

class Contact {
private:
    string name;
    string phone;
public:
    Contact(string n = "", string p = "") : name(n), phone(p) {}
    string getName() const { return name; }
    string getPhone() const { return phone; }
    void display() const {
        cout << name << ": " << phone << endl;
    }
};

int main() {
    setlocale(LC_ALL, "RU");

    Contact c1("Анна", "89171234567");
    Contact c2("Борис", "89271234567");

    c1.display();
    c2.display();

    return 0;
}