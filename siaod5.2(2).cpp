﻿#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <unordered_set>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Enterprise {
    int licenseNumber;        // Ключ записи: номер лицензии
    char name[50];            // Название предприятия
    char founder[50];         // Учредитель
};

// Функция для генерации уникального номера лицензии
int generateUniqueLicenseNumber(unordered_set<int>& licenses) {
    int number;
    do {
        number = rand() % 10000 + 1; // Генерация номера от 1 до 10000
    } while (licenses.find(number) != licenses.end());
    licenses.insert(number);
    return number;
}

// Функция для создания текстового и бинарного файлов
void createBinaryFile(const string& textFileName, const string& binaryFileName, int recordCount) {
    ofstream textFile(textFileName); // Открываем текстовый файл для записи
    ofstream binaryFile(binaryFileName, ios::binary); // Открываем бинарный файл для записи
    unordered_set<int> licenses; // Хранит уникальные номера лицензий

    srand(time(0)); // Инициализация генератора случайных чисел

    for (int i = 0; i < recordCount; i++) {
        Enterprise record;
        record.licenseNumber = generateUniqueLicenseNumber(licenses);

        // Создаем примерные данные для предприятия
        snprintf(record.name, sizeof(record.name), "Enterprise_%d", i + 1);
        snprintf(record.founder, sizeof(record.founder), "Founder_%d", i + 1);

        // Запись в текстовый файл для проверки
        textFile << record.licenseNumber << " " << record.name << " " << record.founder << endl;

        // Запись в бинарный файл
        binaryFile.write(reinterpret_cast<char*>(&record), sizeof(record));
    }

    textFile.close();
    binaryFile.close();
}

// Линейный поиск записи по ключу
bool linearSearch(const string& binaryFileName, int searchKey, Enterprise& result) {
    ifstream binaryFile(binaryFileName, ios::binary);
    if (!binaryFile) {
        cerr << "Ошибка открытия файла." << endl;
        return false;
    }

    Enterprise record;
    while (binaryFile.read(reinterpret_cast<char*>(&record), sizeof(record))) {
        if (record.licenseNumber == searchKey) {
            result = record;
            binaryFile.close();
            return true;
        }
    }

    binaryFile.close();
    return false;
}

int main() {
    setlocale(LC_ALL, "ru");

    const string textFileName = "enterprises.txt";
    const string binaryFileName = "enterprises.bin";

    // Создаем текстовый и бинарный файлы
    createBinaryFile(textFileName, binaryFileName, 10000); 

    int searchKey;
    cout << "Введите номер лицензии для поиска: ";
    cin >> searchKey;

    Enterprise foundRecord;
    auto start = chrono::high_resolution_clock::now();
    bool found = linearSearch(binaryFileName, searchKey, foundRecord);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    if (found) {
        cout << "Предприятие найдено: " << foundRecord.licenseNumber << " - "
             << foundRecord.name << " - " << foundRecord.founder << endl;
    } else {
        cout << "Предприятие с номером лицензии " << searchKey << " не найдено." << endl;
    }

    cout << "Время поиска: " << elapsed.count() << " секунд" << endl;

    return 0;
}




