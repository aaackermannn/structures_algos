#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <windows.h>

using namespace std;

// Функция для построения таблицы сдвигов для Бойера-Мура
unordered_map<char, int> buildBadMatchTable(const string& pattern) {
    unordered_map<char, int> badMatchTable;
    int m = pattern.length();

    for (int i = 0; i < m - 1; i++) {
        badMatchTable[pattern[i]] = m - 1 - i;
    }

    return badMatchTable;
}

// Алгоритм Бойера-Мура с турбосдвигом
vector<int> boyerMooreSearch(const string& text, const string& pattern, int& comparisonCount, vector<int>& shiftIndices) {
    int n = text.length();
    int m = pattern.length();
    vector<int> result;

    unordered_map<char, int> badMatchTable = buildBadMatchTable(pattern);

    int i = 0; // Индекс в тексте
    while (i <= n - m) {
        shiftIndices.push_back(i); // Сохраняем текущий индекс сдвига

        int j = m - 1;
        while (j >= 0 && pattern[j] == text[i + j]) {
            comparisonCount++;
            j--;
        }

        if (j < 0) {
            result.push_back(i);
            comparisonCount++;
            i += (i + m < n) ? m - badMatchTable[text[i + m]] : 1;
        } else {
            comparisonCount++;
            i += max(1, badMatchTable.count(text[i + j]) ? badMatchTable[text[i + j]] : m);
        }
    }

    return result;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string pattern, text;

    // Ввод данных пользователем
    cout << "Введите образец для поиска: ";
    getline(cin, pattern);

    cout << "Введите текст для поиска: ";
    getline(cin, text);

    // Сохранение данных в файл
    ofstream outputFile("input.txt");
    if (!outputFile) {
        cerr << "Ошибка: не удалось создать файл 'input.txt'!" << endl;
        return 1;
    }

    outputFile << pattern << endl;
    outputFile << text << endl;
    outputFile.close();
    cout << "Данные успешно сохранены в файл 'input.txt'." << endl;

    // Чтение данных из файла
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Ошибка: не удалось открыть файл 'input.txt'!" << endl;
        return 1;
    }

    getline(inputFile, pattern);
    getline(inputFile, text);
    inputFile.close();
    cout << "Данные успешно считаны из файла 'input.txt'." << endl;

    // Переменная для подсчёта сравнений
    int comparisonCount = 0;

    // Список индексов сдвигов
    vector<int> shiftIndices;

    // Поиск образца в тексте
    vector<int> indices = boyerMooreSearch(text, pattern, comparisonCount, shiftIndices);

    // Вывод результатов
    if (!indices.empty()) {
        cout << "Образец найден в следующих позициях:" << endl;
        for (int index : indices) {
            cout << index << " ";
        }
        cout << endl;
    } else {
        cout << "Образец не найден в тексте." << endl;
    }

    cout << "Индексы сдвигов алгоритма: ";
    for (int shift : shiftIndices) {
        cout << shift << " ";
    }
    cout << endl;

    cout << "Количество сравнений: " << comparisonCount << endl;

    return 0;
}




