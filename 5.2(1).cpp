#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <cstdlib>
#include <ctime>

using namespace std;

struct CityRecord {
    int cityCode;            // Ключ записи: код города
    char cityName[30];       // Название города
};

// Функция для генерации случайного уникального кода города
int generateUniqueCityCode(unordered_set<int>& codes) {
    int code;
    do {
        code = rand() % 10000 + 1; // Генерация кода в диапазоне от 1 до 10000
    } while (codes.find(code) != codes.end());
    codes.insert(code);
    return code;
}

void createBinaryFile(const string& textFileName, const string& binaryFileName, int recordCount) {
    ofstream textFile(textFileName);
    ofstream binaryFile(binaryFileName, ios::binary);
    unordered_set<int> cityCodes; // Хранит уникальные коды городов

    srand(time(0)); // Инициализация генератора случайных чисел

    // Создание записей
    for (int i = 0; i < recordCount; i++) {
        CityRecord record;
        record.cityCode = generateUniqueCityCode(cityCodes);

        // Пример фиксированных названий городов (можно расширить)
        snprintf(record.cityName, sizeof(record.cityName), "City_%d", i + 1);

        // Запись в текстовый файл
        textFile << record.cityCode << " " << record.cityName << endl;

        // Запись в бинарный файл
        binaryFile.write(reinterpret_cast<char*>(&record), sizeof(record));
    }

    textFile.close();
    binaryFile.close();
}

int main() {
    setlocale(LC_ALL, "ru");
    createBinaryFile("cities.txt", "cities.bin", 100); // Создаем файл на 100 записей
    cout << "Файлы успешно созданы." << endl;
    return 0;
}

