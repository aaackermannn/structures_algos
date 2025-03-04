#include <iostream>
#include <queue>
#include <string>
#include <algorithm>
#include <iomanip> // Для форматирования вывода
#include <windows.h>

using namespace std;

// Структура узла бинарного дерева
struct TreeNode {
    string city;
    TreeNode* left;
    TreeNode* right;
    TreeNode(string value) : city(value), left(nullptr), right(nullptr) {}
};

// Вставка элемента
TreeNode* insert(TreeNode* root, const string& city) {
    if (!root) return new TreeNode(city);
    if (city < root->city)
        root->left = insert(root->left, city);
    else if (city > root->city)
        root->right = insert(root->right, city);
    return root;
}

// Симметричный обход
void inOrderTraversal(TreeNode* root) {
    if (root) {
        inOrderTraversal(root->left);
        cout << root->city << " ";
        inOrderTraversal(root->right);
    }
}

// Обход в ширину
void breadthFirstTraversal(TreeNode* root) {
    if (!root) return;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();
        cout << current->city << " ";
        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }
}

// Длина пути до заданного значения
int pathLength(TreeNode* root, const string& city) {
    int length = 0;
    while (root) {
        if (city == root->city) return length;
        root = (city < root->city) ? root->left : root->right;
        length++;
    }
    return -1; // Город не найден
}

// Высота дерева
int treeHeight(TreeNode* root) {
    if (!root) return 0;
    return 1 + max(treeHeight(root->left), treeHeight(root->right));
}

// Печать дерева
void printTree(TreeNode* node, int level = 0) {
    if (node) {
        printTree(node->right, level + 1); // Рекурсивный вызов для правого поддерева
        cout << setw(4 * level) << "" << node->city << endl; // Вывод узла с отступом
        printTree(node->left, level + 1);  // Рекурсивный вызов для левого поддерева
    }
}

// Меню
void menu() {
    TreeNode* root = nullptr;
    int choice;
    do {
        cout << "\nМеню:\n"
            << "1. Добавить город\n"
            << "2. Симметричный обход\n"
            << "3. Обход в ширину\n"
            << "4. Найти длину пути до города\n"
            << "5. Высота дерева\n"
            << "6. Печать дерева\n"
            << "7. Выход\n"
            << "Выберите операцию: ";
        cin >> choice;
        cin.ignore();

        string city;
        switch (choice) {
        case 1:
            cout << "Введите название города: ";
            getline(cin, city);
            root = insert(root, city);
            break;
        case 2:
            cout << "Симметричный обход: ";
            inOrderTraversal(root);
            cout << "\n";
            break;
        case 3:
            cout << "Обход в ширину: ";
            breadthFirstTraversal(root);
            cout << "\n";
            break;
        case 4:
            cout << "Введите название города: ";
            getline(cin, city);
            int length;
            length = pathLength(root, city);
            if (length != -1)
                cout << "Длина пути до " << city << ": " << length << "\n";
            else
                cout << city << " не найден в дереве.\n";
            break;
        case 5:
            cout << "Высота дерева: " << treeHeight(root) << "\n";
            break;
        case 6:
            cout << "Печать дерева:\n";
            printTree(root);
            break;
        case 7:
            cout << "Выход из программы.\n";
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 7);
}

// Главная функция
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    menu();
    return 0;
}


