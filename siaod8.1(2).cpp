#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Graph {
private:
    int V; // Количество вершин
    vector<vector<int>> adjList; // Списки смежности графа

public:
    // Конструктор
    Graph(int vertices) : V(vertices) {
        adjList.resize(V);
    }

    // Добавление ребра
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u); // Неориентированный граф
    }

    // Вывод графа
    void displayGraph() {
        cout << "Граф (списки смежности):\n";
        for (int i = 0; i < V; ++i) {
            cout << i << " -> ";
            for (int adj : adjList[i]) {
                cout << adj << " ";
            }
            cout << endl;
        }
    }

    // Раскраска графа
    void colorGraph() {
        vector<int> result(V, -1); // Результаты раскраски: -1 означает, что вершина не раскрашена
        vector<bool> availableColors(V, false); // Доступность цветов

        // Назначаем первый цвет первой вершине
        result[0] = 0;

        // Проходим по всем вершинам и назначаем им цвета
        for (int u = 1; u < V; ++u) {
            // Помечаем цвета соседей как недоступные
            for (int adj : adjList[u]) {
                if (result[adj] != -1) {
                    availableColors[result[adj]] = true;
                }
            }

            // Ищем первый доступный цвет
            int color;
            for (color = 0; color < V; ++color) {
                if (!availableColors[color]) break;
            }

            // Назначаем найденный цвет текущей вершине
            result[u] = color;

            // Сбрасываем доступность цветов для следующей итерации
            for (int adj : adjList[u]) {
                if (result[adj] != -1) {
                    availableColors[result[adj]] = false;
                }
            }
        }

        // Вывод результата
        cout << "Минимальное количество цветов: " << *max_element(result.begin(), result.end()) + 1 << endl;
        cout << "Раскраска вершин:\n";
        for (int u = 0; u < V; ++u) {
            cout << "Вершина " << u << " -> Цвет " << result[u] << endl;
        }
    }
};

int main() {
    setlocale(LC_ALL, "ru");
    int V, E;
    cout << "Введите количество вершин: ";
    cin >> V;
    cout << "Введите количество рёбер: ";
    cin >> E;

    Graph graph(V);

    cout << "Введите рёбра (u v):\n";
    for (int i = 0; i < E; ++i) {
        int u, v;
        cin >> u >> v;
        graph.addEdge(u, v);
    }

    graph.displayGraph();

    cout << "\nРаскраска графа:\n";
    graph.colorGraph();

    return 0;
}

