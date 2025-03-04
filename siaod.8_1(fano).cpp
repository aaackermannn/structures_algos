#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// Структура для символов и их кодов
struct Symbol {
    char ch;
    int freq;
    string code;
};

// Функция для сортировки по убыванию частоты
bool compareByFrequency(const Symbol& a, const Symbol& b) {
    return a.freq > b.freq;
}

// Рекурсивное построение кодов методом Шеннона-Фано
void buildShannonFano(vector<Symbol>& symbols, int start, int end) {
    if (start >= end) return;

    // Найти точку разделения
    int totalFreq = 0;
    for (int i = start; i <= end; i++) {
        totalFreq += symbols[i].freq;
    }

    int halfFreq = 0;
    int splitIndex = start;
    for (int i = start; i <= end; i++) {
        halfFreq += symbols[i].freq;
        if (halfFreq >= totalFreq / 2) {
            splitIndex = i;
            break;
        }
    }

    // Назначить "0" для одной группы и "1" для другой
    for (int i = start; i <= splitIndex; i++) {
        symbols[i].code += "0";
    }
    for (int i = splitIndex + 1; i <= end; i++) {
        symbols[i].code += "1";
    }

    // Рекурсивно обработать обе группы
    buildShannonFano(symbols, start, splitIndex);
    buildShannonFano(symbols, splitIndex + 1, end);
}

// Кодирование текста
string encode(const string& text, const map<char, string>& codes) {
    string encoded = "";
    for (char ch : text) {
        encoded += codes.at(ch);
    }
    return encoded;
}

// Декодирование текста
string decode(const string& encoded, const map<string, char>& reverseCodes) {
    string decoded = "";
    string buffer = "";

    for (char bit : encoded) {
        buffer += bit;
        if (reverseCodes.count(buffer)) {
            decoded += reverseCodes.at(buffer);
            buffer = "";
        }
    }

    return decoded;
}

int main() {
    setlocale(LC_ALL, "ru");
    // Исходный текст
    string text = "Мищенко Павел Викторович";

    // Подсчёт частот символов
    map<char, int> frequencies;
    for (char ch : text) {
        frequencies[ch]++;
    }

    // Создать вектор символов с частотами
    vector<Symbol> symbols;
    for (auto& pair : frequencies) {
        symbols.push_back({ pair.first, pair.second, "" });
    }

    // Сортировать символы по частоте
    sort(symbols.begin(), symbols.end(), compareByFrequency);

    // Построить коды методом Шеннона-Фано
    buildShannonFano(symbols, 0, symbols.size() - 1);

    // Создать словарь кодов
    map<char, string> codes;
    map<string, char> reverseCodes;
    for (const auto& symbol : symbols) {
        codes[symbol.ch] = symbol.code;
        reverseCodes[symbol.code] = symbol.ch;
    }

    // Кодирование текста
    string encodedText = encode(text, codes);

    // Декодирование текста
    string decodedText = decode(encodedText, reverseCodes);

    // Вывод результатов
    cout << "Исходный текст: " << text << endl;
    cout << "Закодированный текст: " << encodedText << endl;
    cout << "Декодированный текст: " << decodedText << endl;

    cout << "\nКоды Шеннона-Фано:" << endl;
    for (const auto& symbol : symbols) {
        cout << symbol.ch << " -> " << symbol.code << endl;
    }

    // Расчёт коэффициента сжатия
    int originalSize = text.length() * 8;  // Размер исходного текста в битах (1 символ = 8 бит)
    int compressedSize = encodedText.length();  // Размер закодированного текста
    double compressionRatio = (double)originalSize / compressedSize;

    cout << "\nКоэффициент сжатия: " << compressionRatio << endl;

    return 0;
}


