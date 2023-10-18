#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

class graph {

    private: int vertexes;
    vector<pair<int, int>> edges;//список пар(рёбер)
    vector<vector<int>> list;//список смежности
    vector<vector<int>> matrix;//матрица смежности

    public:

        graph(int vertices) : vertexes(vertices) {
            list.resize(vertexes);//список смежности
            matrix.resize(vertexes, vector<int>(vertexes, 0));//матрица смежности
        }

        //создание пар(рёбер)
        void addEdge(int u, int v) {
            edges.push_back(make_pair(u, v));
        }

        //список смежности
        void CreateList(int u, int v) {
            list[u].push_back(v);
            list[v].push_back(u);
        }

        //матрица смежности
        void CreateMatrix(int u, int v) {
            matrix[u][v] = 1;
            matrix[v][u] = 1;
        }

        void printAdjacencyList() {
            for (int i = 1; i < vertexes; ++i) {
                cout << "Вершина " << i << " смежна с: ";
                for (int j : list[i]) {
                    cout << j << " ";
                }
                cout << endl;
            }
        }

        // Поиск в ширину (BFS)
        void BFS(int startVertex) {
            vector<bool> visited(vertexes, false);
            queue<int> q;

            visited[startVertex] = true;
            q.push(startVertex);

            while (!q.empty()) {
                int currentVertex = q.front();
                cout << currentVertex << " ";
                q.pop();

                for (int neighbourVertex : list[currentVertex]) {
                    if (!visited[neighbourVertex]) {
                        visited[neighbourVertex] = true;
                        q.push(neighbourVertex);
                    }
                }
            }
        }

        // Поиск в глубину (DFS)
        void DFS(int startVertex) {
            vector<bool> visited(vertexes, false);
            stack<int> s;

            visited[startVertex] = true;
            s.push(startVertex);

            while (!s.empty()) {
                int currentVertex = s.top();
                cout << currentVertex << " ";
                s.pop();

                for (int neighbourVertex : list[currentVertex]) {
                    if (!visited[neighbourVertex]) {
                        visited[neighbourVertex] = true;
                        s.push(neighbourVertex);
                    }
                }
            }
        }

};

int main()
{
    setlocale(LC_ALL, "Russian");

    graph NotGraph(11);

    //создание пар(рёбер)
    {
        NotGraph.addEdge(1, 2);
        NotGraph.addEdge(1, 5);
        NotGraph.addEdge(2, 1);
        NotGraph.addEdge(2, 7);
        NotGraph.addEdge(2, 8);
        NotGraph.addEdge(3, 8);
        NotGraph.addEdge(4, 6);
        NotGraph.addEdge(4, 9);
        NotGraph.addEdge(5, 1);
        NotGraph.addEdge(5, 6);
        NotGraph.addEdge(6, 4);
        NotGraph.addEdge(6, 5);
        NotGraph.addEdge(6, 9);
        NotGraph.addEdge(7, 2);
        NotGraph.addEdge(7, 8);
        NotGraph.addEdge(8, 2);
        NotGraph.addEdge(8, 3);
        NotGraph.addEdge(8, 7);
        NotGraph.addEdge(9, 4);
        NotGraph.addEdge(9, 6);
        NotGraph.addEdge(10, 9);
    }

    //список смежности
    {
        NotGraph.CreateList(1, 2);
        NotGraph.CreateList(1, 5);
        NotGraph.CreateList(2, 1);
        NotGraph.CreateList(2, 7);
        NotGraph.CreateList(2, 8);
        NotGraph.CreateList(3, 8);
        NotGraph.CreateList(4, 6);
        NotGraph.CreateList(4, 9);
        NotGraph.CreateList(5, 1);
        NotGraph.CreateList(5, 6);
        NotGraph.CreateList(6, 4);
        NotGraph.CreateList(6, 5);
        NotGraph.CreateList(6, 9);
        NotGraph.CreateList(7, 2);
        NotGraph.CreateList(7, 8);
        NotGraph.CreateList(8, 2);
        NotGraph.CreateList(8, 3);
        NotGraph.CreateList(8, 7);
        NotGraph.CreateList(9, 4);
        NotGraph.CreateList(9, 6);
        NotGraph.CreateList(10, 9);
    }

    //матрица смежности
    {
        NotGraph.CreateMatrix(1, 2);
        NotGraph.CreateMatrix(1, 5);
        NotGraph.CreateMatrix(2, 7);
        NotGraph.CreateMatrix(2, 8);
        NotGraph.CreateMatrix(3, 8);
        NotGraph.CreateMatrix(4, 6);
        NotGraph.CreateMatrix(4, 9);
        NotGraph.CreateMatrix(5, 6);
        NotGraph.CreateMatrix(6, 9);
        NotGraph.CreateMatrix(7, 8);
        NotGraph.CreateMatrix(10, 9);
    }

    NotGraph.printAdjacencyList();

    cout << "Обход в ширину: ";
    NotGraph.BFS(2);

    cout << "\nОбход в глубину: ";
    NotGraph.DFS(1);
}
