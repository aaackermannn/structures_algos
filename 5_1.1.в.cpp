#include <iostream>
using namespace std;

int main() {
    setlocale(LC_ALL, "ru");
    int x = 25;                  // Число 25
    unsigned int mask = 1 << 31; // Маска с 31-го бита

    for (int i = 31; i >= 0; i--) {
        if (x & mask) {
            cout << "Бит " << i << " установлен." << endl;
        }
        mask >>= 1; // Сдвигаем маску вправо
    }

    return 0;
}
