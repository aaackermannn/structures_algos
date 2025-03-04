#include <iomanip>
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Структура элемента множества
struct InsurancePolicy {
    int number;          // Номер полиса (ключ)
    string company;      // Название компании
    string owner;        // Фамилия владельца
};

// Класс хеш-таблицы с открытой адресацией
class HashTable {
private:
    struct HashNode {
        InsurancePolicy data;
        bool isOccupied; // Флаг занятости
        bool isDeleted;  // Флаг удаления
    };

    vector<HashNode> table;
    int size;
    int count;

    // Хеш-функция
    int hashFunction(int key) {
        return key % size;
    }

    // Увеличение размера и рехеширование
    void rehash() {
        int oldSize = size;
        vector<HashNode> oldTable = table;

        size *= 2;
        table = vector<HashNode>(size, { {}, false, false });
        count = 0;

        cout << "Таблица переполнена. Выполняется рехеширование. Новый размер таблицы: " << size << "." << endl;

        for (const auto& node : oldTable) {
            if (node.isOccupied && !node.isDeleted) {
                insert(node.data);
            }
        }
    }

public:
    HashTable(int initialSize = 8) : size(initialSize), count(0) {
        table = vector<HashNode>(size, { {}, false, false });
    }

    // Вставка записи
    void insert(const InsurancePolicy& policy) {
        if (count >= size / 2) {
            rehash();
        }

        int index = hashFunction(policy.number);
        while (table[index].isOccupied && !table[index].isDeleted) {
            if (table[index].data.number == policy.number) {
                cout << "Полис с номером " << policy.number
                    << " уже существует." << endl;
                return;
            }
            index = (index + 1) % size; // Линейное пробирование
        }

        table[index] = { policy, true, false };
        count++;
    }

    // Удаление записи
    void remove(int number) {
        int index = hashFunction(number);
        for (int i = 0; i < size; i++) {
            int currentIndex = (index + i) % size;
            if (table[currentIndex].isOccupied && table[currentIndex].data.number == number) {
                table[currentIndex].isDeleted = true;
                count--;
                cout << "Полис с номером " << number << " удален." << endl;
                return;
            }
            if (!table[currentIndex].isOccupied) {
                break;
            }
        }
        cout << "Ошибка: Полис с номером " << number << " не найден." << endl;
    }

    // Поиск записи
    InsurancePolicy* search(int number) {
        int index = hashFunction(number);
        for (int i = 0; i < size; i++) {
            int currentIndex = (index + i) % size;
            if (table[currentIndex].isOccupied && table[currentIndex].data.number == number) {
                return &table[currentIndex].data;
            }
            if (!table[currentIndex].isOccupied) {
                break;
            }
        }
        return nullptr;
    }

    // Вывод таблицы
    void display() {
        cout << setw(5) << "Индекс" << setw(10) << "Номер" << setw(20) << "Компания" << setw(20) << "Владелец" << endl;
        cout << string(60, '-') << endl;
        for (int i = 0; i < size; i++) {
            cout << setw(5) << i;
            if (table[i].isOccupied && !table[i].isDeleted) {
                cout << setw(10) << table[i].data.number
                    << setw(20) << table[i].data.company
                    << setw(20) << table[i].data.owner << endl;
            }
            else {
                cout << setw(10) << "-" << setw(20) << "-" << setw(20) << "-" << endl;
            }
        }
    }
};

// Главная функция
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    HashTable table;
    int initialEntries;

    cout << "Введите количество записей, которые вы хотите добавить: ";
    cin >> initialEntries;

    for (int i = 0; i < initialEntries; i++) {
        InsurancePolicy policy;
        cout << "Введите номер полиса: ";
        cin >> policy.number;
        cout << "Введите название компании: ";
        cin.ignore();
        getline(cin, policy.company);
        cout << "Введите фамилию владельца: ";
        getline(cin, policy.owner);
        table.insert(policy);
    }

    int choice;
    do {
        cout << "\nМеню:\n"
            << "1. Добавить запись\n"
            << "2. Удалить запись\n"
            << "3. Найти запись\n"
            << "4. Показать таблицу\n"
            << "0. Выход\n"
            << "Ваш выбор: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            InsurancePolicy policy;
            cout << "Введите номер полиса: ";
            cin >> policy.number;
            cout << "Введите название компании: ";
            cin.ignore();
            getline(cin, policy.company);
            cout << "Введите фамилию владельца: ";
            getline(cin, policy.owner);
            table.insert(policy);
            break;
        }
        case 2: {
            int number;
            cout << "Введите номер полиса для удаления: ";
            cin >> number;
            table.remove(number);
            break;
        }
        case 3: {
            int number;
            cout << "Введите номер полиса для поиска: ";
            cin >> number;
            InsurancePolicy* policy = table.search(number);
            if (policy) {
                cout << "Найден полис: "
                    << "Компания: " << policy->company << ", "
                    << "Владелец: " << policy->owner << endl;
            }
            else {
                cout << "Полис с номером " << number << " не найден." << endl;
            }
            break;
        }
        case 4:
            table.display();
            break;
        case 0:
            cout << "Выход из программы." << endl;
            break;
        default:
            cout << "Некорректный выбор. Повторите ввод." << endl;
        }
    } while (choice != 0);

    return 0;
}





