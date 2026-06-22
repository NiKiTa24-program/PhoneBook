#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

class Contact {
private:
    string name;
    string phone;
public:
    Contact(string n = "", string p = "") : name(n), phone(p) {}

    string getName() const { return name; }
    string getPhone() const { return phone; }

    void changeName(const string& newName) { name = newName; }
    void changePhone(const string& newPhone) { phone = newPhone; }

    void display() const {
        cout << name << ": " << phone << endl;
    }
};

class PhoneBook {
private:
    map<string, Contact> contacts;
public:
    void addContact(const Contact& c) {
        contacts[c.getName()] = c.getPhone();
    }

    void removeContact(const string& name) {
        auto it = contacts.find(name);
        if (it != contacts.end()) {
            contacts.erase(it);
            cout << "Контакт " << name << " удалён" << endl;
        }
        else {
            cout << "Контакт " << name << " не найден" << endl;;
        }
    }

    void findContact(const string& name) const {
        auto it = contacts.find(name);
        if (it != contacts.end()) {
            it->second.display();
        }
        else {
            cout << "Контакт " << name << " не найден" << endl;;
        }
    }

    void displayAll() const {
        if (contacts.empty()) {
            cout << "Телефонная книга пуста" << endl;;
            return;
        }
        for (const auto& pair : contacts) {
            pair.second.display();
        }
    }

    void saveToFile(const string& filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "Не удалось открыть файл для записи" << endl;
        }
        for (const auto& pair : contacts) {
            file << pair.first << ": " << pair.second.changePhone() << endl;
            file.close();
            cout << "Контакты успешно сохрнались в файле " << filename << endl;
        }
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Не удалось открыть файл для чтения" << endl;
        }
        else {
            string line;
            while (getline(file, line)) {
                cout << line << endl;
            }
            file.close();
        }
    }
};

class Menu {

};

int main() {
    setlocale(LC_ALL, "RU");

    Contact c1("Анна", "89171234567");
    Contact c2("Борис", "89271234567");

    c1.display();
    c2.display();
    

    return 0;
}