#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> graph;
vector<int> path;
vector<bool> visited;
vector<vector<int>> hamiltonian_cycles;

// Функция для поиска всех гамильтоновых циклов
void findHamiltonianCycles(int node, int start, int count, int V) {
    visited[node] = true;
    path.push_back(node);

    if (count == V && graph[node][start]) {
        path.push_back(start);
        hamiltonian_cycles.push_back(path);
        path.pop_back();
    }
    else {
        for (int next = 0; next < V; ++next) {
            if (!visited[next] && graph[node][next]) {
                findHamiltonianCycles(next, start, count + 1, V);
            }
        }
    }

    visited[node] = false;
    path.pop_back();
}

void hamiltonianCycle(int V) {
    visited.assign(V, false);
    for (int start = 0; start < V; ++start) {
        findHamiltonianCycles(start, start, 1, V);
    }

    cout << "Гамильтоновы циклы:\n";
    for (const auto& cycle : hamiltonian_cycles) {
        for (int node : cycle) {
            cout << node + 1 << " ";
        }
        cout << endl;
    }
}

int main() {
    setlocale(LC_ALL, "ru");
    int V, E;
    cout << "Введите количество вершин и рёбер графа: ";
    cin >> V >> E;

    if (V <= 0 || E < 0) {
        cout << "Неверное количество вершин или рёбер!" << endl;
        return 1;
    }

    graph.assign(V, vector<int>(V, 0));

    cout << "Введите рёбра (u v):" << endl;
    for (int i = 0; i < E; ++i) {
        int u, v;
        cin >> u >> v;

        if (u < 1 || u > V || v < 1 || v > V) {
            cout << "Ошибка: Вершины должны быть от 1 до " << V << ". Попробуйте снова." << endl;
            return 1;
        }

        --u; --v; // Переводим в 0-based индексацию
        graph[u][v] = graph[v][u] = 1;
    }

    hamiltonianCycle(V);

    return 0;
}

