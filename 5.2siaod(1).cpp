#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Enterprise {
    int licenseNumber;        // Ключ записи: номер лицензии
    char name[50];            // Название предприятия
    char founder[50];         // Учредитель
};

// Функция для генерации случайного уникального номера лицензии
int generateUniqueLicenseNumber(unordered_set<int>& licenses) {
    int number;
    do {
        number = rand() % 10000 + 1; // Генерация номера от 1 до 10000
    } while (licenses.find(number) != licenses.end());
    licenses.insert(number);
    return number;
}

// Функция для создания текстового и двоичного файлов
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

int main() {
    setlocale(LC_ALL, "ru");
    createBinaryFile("enterprises.txt", "enterprises.bin", 100); // Создаем файл на 100 записей
    cout << "Файлы успешно созданы." << endl;
    return 0;
}

