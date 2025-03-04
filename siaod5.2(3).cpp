#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono>

using namespace std;

struct Enterprise {
    int licenseNumber;        // Ключ записи: номер лицензии
    char name[50];            // Название предприятия
    char founder[50];         // Учредитель
};

// Создаем таблицу индексов
void createIndexTable(const string& binaryFileName, vector<pair<int, streampos>>& indexTable) {
    ifstream binaryFile(binaryFileName, ios::binary);
    if (!binaryFile) {
        cerr << "Ошибка открытия файла." << endl;
        return;
    }

    streampos position = 0;
    Enterprise record;
    while (binaryFile.read(reinterpret_cast<char*>(&record), sizeof(record))) {
        indexTable.emplace_back(record.licenseNumber, position);
        position = binaryFile.tellg();
    }
    binaryFile.close();

    // Сортируем таблицу индексов по ключу
    sort(indexTable.begin(), indexTable.end());
}

// Бинарный поиск в таблице индексов
streampos binarySearchIndex(const vector<pair<int, streampos>>& indexTable, int searchKey) {
    int left = 0;
    int right = indexTable.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (indexTable[mid].first == searchKey) {
            return indexTable[mid].second;
        }
        else if (indexTable[mid].first < searchKey) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1; // Ключ не найден
}

// Чтение записи из файла по смещению
bool readRecord(const string& binaryFileName, streampos position, Enterprise& result) {
    ifstream binaryFile(binaryFileName, ios::binary);
    if (!binaryFile) {
        cerr << "Ошибка открытия файла." << endl;
        return false;
    }

    binaryFile.seekg(position);
    if (binaryFile.read(reinterpret_cast<char*>(&result), sizeof(result))) {
        binaryFile.close();
        return true;
    }

    binaryFile.close();
    return false;
}

// Генерация уникального номера лицензии
int generateUniqueLicenseNumber(unordered_set<int>& licenses) {
    int number;
    do {
        number = rand() % 10000 + 1; // Генерация номера от 1 до 10000
    } while (licenses.find(number) != licenses.end());
    licenses.insert(number);
    return number;
}

// Создание текстового и бинарного файлов
void createBinaryFile(const string& textFileName, const string& binaryFileName, int recordCount) {
    ofstream textFile(textFileName);
    ofstream binaryFile(binaryFileName, ios::binary);
    unordered_set<int> licenses;

    srand(time(0)); // Инициализация генератора случайных чисел

    for (int i = 0; i < recordCount; i++) {
        Enterprise record;
        record.licenseNumber = generateUniqueLicenseNumber(licenses);
        snprintf(record.name, sizeof(record.name), "Enterprise_%d", i + 1);
        snprintf(record.founder, sizeof(record.founder), "Founder_%d", i + 1);

        textFile << record.licenseNumber << " " << record.name << " " << record.founder << endl;
        binaryFile.write(reinterpret_cast<char*>(&record), sizeof(record));
    }

    textFile.close();
    binaryFile.close();
}

int main() {
    setlocale(LC_ALL, "ru");

    const string textFileName = "enterprises.txt";
    const string binaryFileName = "enterprises.bin";
    vector<int> recordCounts = { 100, 1000, 10000 };

    for (int recordCount : recordCounts) {
        cout << "Тест для " << recordCount << " записей:" << endl;

        // Создание файлов
        createBinaryFile(textFileName, binaryFileName, recordCount);

        // Создание таблицы индексов
        vector<pair<int, streampos>> indexTable;
        createIndexTable(binaryFileName, indexTable);

        int searchKey;
        cout << "Введите номер лицензии для поиска: ";
        cin >> searchKey;

        auto startIndexSearch = chrono::high_resolution_clock::now();
        streampos position = binarySearchIndex(indexTable, searchKey);
        auto endIndexSearch = chrono::high_resolution_clock::now();
        chrono::duration<double> indexSearchTime = endIndexSearch - startIndexSearch;

        if (position != -1) {
            Enterprise foundRecord;
            auto startRead = chrono::high_resolution_clock::now();
            bool found = readRecord(binaryFileName, position, foundRecord);
            auto endRead = chrono::high_resolution_clock::now();
            chrono::duration<double> readTime = endRead - startRead;

            if (found) {
                cout << "Предприятие найдено: " << foundRecord.licenseNumber << " - "
                    << foundRecord.name << " - " << foundRecord.founder << endl;
                cout << "Время поиска в таблице индексов: " << indexSearchTime.count() << " секунд" << endl;
                cout << "Время чтения записи: " << readTime.count() << " секунд" << endl;
            }
            else {
                cout << "Ошибка чтения записи." << endl;
            }
        }
        else {
            cout << "Предприятие с номером лицензии " << searchKey << " не найдено." << endl;
            cout << "Время поиска в таблице индексов: " << indexSearchTime.count() << " секунд" << endl;
        }

        cout << endl;
    }

    return 0;
}












