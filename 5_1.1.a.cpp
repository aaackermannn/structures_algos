#include <iostream>
using namespace std;

int main() {
    setlocale(LC_ALL, "ru");
    unsigned char x = 255;      // 11111111
    unsigned char maska = 1;    // 00000001
    x = x & (~(maska << 4));    // Устанавливаем 5-й бит в 0
    cout << "Результат: " << (int)x << endl;
    return 0;
}


