#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <format>
#include <windows.h>

using namespace std;

class Graph {
    unordered_map<string, vector<string>> adjList; // Список смежности

public:
    // Добавление вершины
    void addVertex(const string& vertex) {
        adjList[vertex] = {};
    }

    // Добавление ребра
    void addEdge(const string& from, const string& to) {
        adjList[from].push_back(to); // Для ориентированного графа
    }

    // Проверка связности
    bool isConnected() {
        unordered_set<string> visited;
        dfsVisit(adjList.begin()->first, visited); // Запуск DFS с первой вершины
        return visited.size() == adjList.size();
    }

    // Проверка на циклы
    bool isAcyclic() {
        unordered_set<string> visited;
        unordered_set<string> path;
        for (const auto& pair : adjList) {
            if (dfsCycle(pair.first, visited, path))
                return false; // Найден цикл
        }
        return true;
    }

private:
    // DFS для проверки связности
    void dfsVisit(const string& vertex, unordered_set<string>& visited) {
        visited.insert(vertex);
        for (const string& neighbor : adjList[vertex]) {
            if (visited.find(neighbor) == visited.end()) {
                dfsVisit(neighbor, visited);
            }
        }
    }

    // DFS для проверки на цикл
    bool dfsCycle(const string& vertex, unordered_set<string>& visited, unordered_set<string>& path) {
        if (path.find(vertex) != path.end()) return true; // Найден цикл
        if (visited.find(vertex) != visited.end()) return false;

        visited.insert(vertex);
        path.insert(vertex);
        for (const string& neighbor : adjList[vertex]) {
            if (dfsCycle(neighbor, visited, path)) return true;
        }
        path.erase(vertex); // Убираем вершину из текущего пути
        return false;
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Graph g;

    // Добавление вершин
    g.addVertex("v1");
    g.addVertex("v2");
    g.addVertex("v3");
    g.addVertex("v4");
    g.addVertex("v5");
    g.addVertex("v6");
    g.addVertex("v7");

    // Добавление рёбер
    g.addEdge("v1", "v4");
    g.addEdge("v1", "v7");
    g.addEdge("v1", "v5");
    g.addEdge("v4", "v5");
    g.addEdge("v3", "v4");
    g.addEdge("v3", "v5");
    g.addEdge("v2", "v3");
    g.addEdge("v2", "v5");
    g.addEdge("v2", "v6");
    g.addEdge("v6", "v7");
    g.addEdge("v5", "v6");
    g.addEdge("v5", "v7");


    // Проверка связности и ацикличности
    cout << "Граф связный? " << (g.isConnected() ? "Да" : "Нет") << endl;
    cout << "Граф ацикличный? " << (g.isAcyclic() ? "Да" : "Нет") << endl;

    return 0;
}


