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
        contacts[c.getName()] = c;
    }

    void removeContact(const string& name) {
        auto it = contacts.find(name);
        if (it != contacts.end()) {
            contacts.erase(it);
            cout << "Контакт " << name << " удалён" << endl;
        }
        else {
            cout << "Контакт " << name << " не найден" << endl;
        }
    }

    void findContact(const string& name) const {
        auto it = contacts.find(name);
        if (it != contacts.end()) {
            it->second.display();
        }
        else {
            cout << "Контакт " << name << " не найден" << endl;
        }
    }

    void displayAll() const {
        if (contacts.empty()) {
            cout << "Телефонная книга пуста" << endl;
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
            file << pair.first << ": " << pair.second.getPhone() << endl;
            cout << "Контакты успешно сохрнались в файле " << filename << endl;
        }
        file.close();
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Не удалось открыть файл для чтения" << endl;
            return;
        }
        string line;
        while (getline(file, line)) {
            size_t pos = line.find(": ");
            if (pos != string::npos) {
                string name = line.substr(0, pos);
                string phone = line.substr(pos + 2);
                contacts[name] = Contact(name, phone);
            }
        }
        file.close();
        cout << "Контакты загружены из " << filename << endl;
    }
};

class Menu {
public:
    void run(PhoneBook& book) {
        int choice;
        bool running = true;

        cout << "Добро пожаловать в телефонный справочник!" << endl;

        while (running) {
            cout << "\nВыберите действие:" << endl;
            cout << "1. Добавить контакт" << endl;
            cout << "2. Удалить контакт" << endl;
            cout << "3. Найти контакт" << endl;
            cout << "4. Показать все контакты" << endl;
            cout << "5. Сохранить в файл" << endl;
            cout << "6. Загрузить из файла" << endl;
            cout << "0. Выход" << endl;
            cout << "Ваш выбор: ";

            cin >> choice;

            switch (choice) {
            case 1: {
                string name, phone;
                cout << "Введите имя: ";
                cin >> name;
                cout << "Введите телефон: ";
                cin >> phone;
                book.addContact(Contact(name, phone));
                cout << "Контакт добавлен!" << endl;
                break;
            }
            case 2: {
                string name;
                cout << "Введите имя для удаления: ";
                cin >> name;
                book.removeContact(name);
                break;
            }
            case 3: {
                string name;
                cout << "Введите имя для поиска: ";
                cin >> name;
                book.findContact(name);
                break;
            }
            case 4:
                book.displayAll();
                break;
            case 5:
                book.saveToFile("contacts.txt");
                break;
            case 6:
                book.loadFromFile("contacts.txt");
                break;
            case 0:
                cout << "До свидания!" << endl;
                running = false;
                break;
            default:
                cout << "Неверный выбор! Попробуйте снова." << endl;
            }
        }
    }
};

int main() {
    setlocale(LC_ALL, "RU");

    PhoneBook book;
    Menu menu;

    // Загружаем контакты при старте
    book.loadFromFile("contacts.txt");

    // Запускаем меню
    menu.run(book);

    return 0;
}