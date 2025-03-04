#include <iostream>
using namespace std;

int main() {
    setlocale(LC_ALL, "ru");
    unsigned char x = 25;       // 00011001
    x = x | (1 << 6);           // Устанавливаем 7-й бит в 1
    cout << "Результат: " << (int)x << endl;
    return 0;
}

