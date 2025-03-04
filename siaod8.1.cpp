#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <set>

using namespace std;

class Graph {
public:
    vector<vector<int>> adj; // Список смежности
    bool isDirected; // Флаг для направленного графа

    Graph(int vertices, bool directed = false) : isDirected(directed) {
        adj.resize(vertices);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        if (!isDirected) {
            adj[v].push_back(u);
        }
    }

    bool isConnected() {
        vector<bool> visited(adj.size(), false);
        int nonZeroDegreeVertex = -1;

        for (int i = 0; i < adj.size(); i++) {
            if (!adj[i].empty()) {
                nonZeroDegreeVertex = i;
                break;
            }
        }

        if (nonZeroDegreeVertex == -1) return true; // Если нет рёбер, граф связный

        stack<int> s;
        s.push(nonZeroDegreeVertex);
        visited[nonZeroDegreeVertex] = true;

        while (!s.empty()) {
            int v = s.top();
            s.pop();

            for (int neighbor : adj[v]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    s.push(neighbor);
                }
            }
        }

        for (int i = 0; i < adj.size(); i++) {
            if (!visited[i] && !adj[i].empty())
                return false;
        }
        return true;
    }

    bool isEulerianCycle() {
        if (isDirected) {
            // Проверка условий для направленного графа
            for (int i = 0; i < adj.size(); i++) {
                int inDegree = 0, outDegree = adj[i].size();
                for (int j = 0; j < adj.size(); j++) {
                    if (find(adj[j].begin(), adj[j].end(), i) != adj[j].end()) {
                        inDegree++;
                    }
                }
                if (inDegree != outDegree) {
                    return false;
                }
            }
        }
        else {
            // Проверка условий для ненаправленного графа
            for (const auto& neighbors : adj) {
                if (neighbors.size() % 2 != 0) {
                    return false;
                }
            }
        }
        return isConnected();
    }

    void printEulerianCycle() {
        stack<int> currPath;
        vector<int> circuit;
        vector<vector<int>> tempAdj = adj; // Копия графа для модификации

        currPath.push(0); // Начинаем с первой вершины (индекс 0)
        int currV = 0; // Текущая вершина

        while (!currPath.empty()) {
            if (!tempAdj[currV].empty()) {
                currPath.push(currV);
                int nextV = tempAdj[currV].back();
                tempAdj[currV].pop_back();
                if (!isDirected) {
                    tempAdj[nextV].erase(find(tempAdj[nextV].begin(), tempAdj[nextV].end(), currV));
                }
                currV = nextV;
            }
            else {
                circuit.push_back(currV);
                currV = currPath.top();
                currPath.pop();
            }
        }

        // Вывод цикла
        cout << "Эйлеров цикл: ";
        for (int i = circuit.size() - 1; i >= 0; --i) {
            cout << (circuit[i] + 1) << (i == 0 ? "\n" : " -> ");
        }
    }

    void display() {
        cout << "Список смежностей графа:\n";
        for (int i = 0; i < adj.size(); i++) {
            cout << (i + 1) << ": ";
            for (int j : adj[i]) {
                cout << (j + 1) << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    setlocale(LC_ALL, "ru");
    int V, E;
    cout << "Введите количество вершин: ";
    cin >> V;
    cout << "Граф ориентированный? (1 - да, 0 - нет): ";
    bool isDirected;
    cin >> isDirected;

    Graph graph(V, isDirected);

    cout << "Введите количество рёбер: ";
    cin >> E;
    cout << "Введите рёбра (u v):\n";
    for (int i = 0; i < E; ++i) {
        int u, v;
        cin >> u >> v;
        graph.addEdge(u - 1, v - 1); // Переход к 0-индексации
    }

    graph.display();

    if (graph.isEulerianCycle()) {
        cout << "Граф имеет эйлеров цикл.\n";
        graph.printEulerianCycle();
    }
    else {
        cout << "Граф не имеет эйлерова цикла.\n";
    }

    return 0;
}










