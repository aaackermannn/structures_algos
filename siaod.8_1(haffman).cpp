#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <memory>

using namespace std;

// Структура для узлов дерева Хаффмана
struct Node {
    char ch;
    int freq;
    shared_ptr<Node> left, right;

    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

// Компаратор для приоритетной очереди
struct Compare {
    bool operator()(const shared_ptr<Node>& a, const shared_ptr<Node>& b) {
        return a->freq > b->freq;  // Минимальная частота имеет приоритет
    }
};

// Функция для построения кодов
void buildCodes(const shared_ptr<Node>& node, const string& code, map<char, string>& huffmanCodes) {
    if (!node) return;

    if (node->ch != '\0') {  // Листовой узел
        huffmanCodes[node->ch] = code;
    }

    buildCodes(node->left, code + "0", huffmanCodes);
    buildCodes(node->right, code + "1", huffmanCodes);
}

// Функция кодирования текста
string encode(const string& text, const map<char, string>& huffmanCodes) {
    string encoded = "";
    for (char ch : text) {
        encoded += huffmanCodes.at(ch);
    }
    return encoded;
}

// Функция декодирования текста
string decode(const string& encoded, const shared_ptr<Node>& root) {
    string decoded = "";
    auto current = root;

    for (char bit : encoded) {
        current = (bit == '0') ? current->left : current->right;

        if (!current->left && !current->right) {  // Лист
            decoded += current->ch;
            current = root;
        }
    }

    return decoded;
}

int main() {
    setlocale(LC_ALL, "ru");
    // Исходный текст
    string text = "Мищенко Павел Викторович";

    // Шаг 1: Подсчёт частот символов
    map<char, int> frequencies;
    for (char ch : text) {
        frequencies[ch]++;
    }

    // Шаг 2: Построение дерева Хаффмана
    priority_queue<shared_ptr<Node>, vector<shared_ptr<Node>>, Compare> pq;
    for (auto& pair : frequencies) {
        pq.push(make_shared<Node>(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        auto left = pq.top(); pq.pop();
        auto right = pq.top(); pq.pop();

        auto merged = make_shared<Node>('\0', left->freq + right->freq);
        merged->left = left;
        merged->right = right;
        pq.push(merged);
    }

    auto root = pq.top();

    // Шаг 3: Построение кодов Хаффмана
    map<char, string> huffmanCodes;
    buildCodes(root, "", huffmanCodes);

    // Шаг 4: Кодирование текста
    string encodedText = encode(text, huffmanCodes);

    // Шаг 5: Декодирование текста
    string decodedText = decode(encodedText, root);

    // Шаг 6: Вывод результатов
    cout << "Исходный текст: " << text << endl;
    cout << "Закодированный текст: " << encodedText << endl;
    cout << "Декодированный текст: " << decodedText << endl;

    cout << "\nКоды Хаффмана:" << endl;
    for (auto& pair : huffmanCodes) {
        cout << pair.first << " -> " << pair.second << endl;
    }

    // Шаг 7: Расчёт коэффициента сжатия
    int originalSize = text.length() * 8;  // Размер исходного текста в битах (1 символ = 8 бит)
    int compressedSize = encodedText.length();  // Размер закодированного текста
    double compressionRatio = (double)originalSize / compressedSize;

    cout << "\nКоэффициент сжатия: " << compressionRatio << endl;

    return 0;
}




