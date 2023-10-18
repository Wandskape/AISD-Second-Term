#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <stack>
using namespace std;

struct Albhabet {
    int code;
    char symbol;
};

class graph {

private: int vertexes;
       vector<vector<pair<int, int>>> list;//список смежности

public:

    graph(int vertices) : vertexes(vertices) {
        list.resize(vertexes);//список смежности
    }


    //список смежности
    void CreateList(int u, int v, int weight) {
        list[u].push_back(make_pair(v, weight));
        list[v].push_back(make_pair(u, weight));
    }

    void printAdjacencyList(Albhabet RUSSIAN[], int node) {
        for (int i = 0; i < node; ++i) {
            cout << "Вершина " << RUSSIAN[i].symbol << " смежна с: ";
            for (const auto& adjacent : list[i]) {
                cout << RUSSIAN[adjacent.first].symbol << "(" << adjacent.second << ") ";
            }
            cout << endl;
        }
    }

    void dejkstra(int startVertex, Albhabet RUSSIAN[], int node) {
        vector<int> distance(vertexes, numeric_limits<int>::max());
        vector<bool> visited(vertexes, false);

        distance[startVertex] = 0;

        for (int count = 0; count < node; ++count) {
            int minDistance = numeric_limits<int>::max();
            int minVertex;

            // Находим вершину с минимальным расстоянием, которая еще не посещена
            for (int v = 0; v < node; ++v) {
                if (!visited[v] && distance[v] < minDistance) {
                    minDistance = distance[v];
                    minVertex = v;
                }
            }

            visited[minVertex] = true;

            // Обновляем расстояния до смежных вершин
            for (const auto& adjacent : list[minVertex]) {
                int v = adjacent.first;
                int weight = adjacent.second;

                if (!visited[v] && distance[minVertex] != numeric_limits<int>::max() && distance[minVertex] + weight < distance[v]) {
                    distance[v] = distance[minVertex] + weight;
                }
            }
        }

        // Выводим найденные расстояния
        cout << "Минимальные расстояния от вершины " << RUSSIAN[startVertex].symbol << " до остальных вершин:" << endl;
        for (int i = 0; i < node; ++i) {
            cout << RUSSIAN[startVertex].symbol << " -> " << RUSSIAN[i].symbol << ": " << distance[i] << endl;
        }
    }

};




int main()
{
    setlocale(LC_ALL, "Russian");

    graph NotGraph(11);

    //АЛФАВИТ
    
    Albhabet RUSSIAN[32];

    RUSSIAN[0].code = 0;
    RUSSIAN[0].symbol = 'A';

    RUSSIAN[1].code = 1;
    RUSSIAN[1].symbol = 'B';

    RUSSIAN[2].code = 2;
    RUSSIAN[2].symbol = 'C';

    RUSSIAN[3].code = 3;
    RUSSIAN[3].symbol = 'D';

    RUSSIAN[4].code = 4;
    RUSSIAN[4].symbol = 'E';

    RUSSIAN[5].code = 5;
    RUSSIAN[5].symbol = 'F';

    RUSSIAN[6].code = 6;
    RUSSIAN[6].symbol = 'G';

    RUSSIAN[7].code = 7;
    RUSSIAN[7].symbol = 'H';

    RUSSIAN[8].code = 8;
    RUSSIAN[8].symbol = 'I';

    RUSSIAN[9].code = 9;
    RUSSIAN[9].symbol = 'J';
    

    //список смежности
    {
        NotGraph.CreateList(RUSSIAN[0].code, RUSSIAN[1].code, 7);
        NotGraph.CreateList(RUSSIAN[1].code, RUSSIAN[6].code, 27);
        NotGraph.CreateList(RUSSIAN[0].code, RUSSIAN[2].code, 10);
        NotGraph.CreateList(RUSSIAN[1].code, RUSSIAN[5].code, 9);
        NotGraph.CreateList(RUSSIAN[6].code, RUSSIAN[8].code, 15);
        NotGraph.CreateList(RUSSIAN[2].code, RUSSIAN[5].code, 8);
        NotGraph.CreateList(RUSSIAN[2].code, RUSSIAN[4].code, 31);
        NotGraph.CreateList(RUSSIAN[5].code, RUSSIAN[7].code, 11);
        NotGraph.CreateList(RUSSIAN[4].code, RUSSIAN[3].code, 32);
        NotGraph.CreateList(RUSSIAN[7].code, RUSSIAN[3].code, 17);
        NotGraph.CreateList(RUSSIAN[7].code, RUSSIAN[8].code, 15);
    }

    NotGraph.printAdjacencyList(RUSSIAN, 9);

    NotGraph.dejkstra(1, RUSSIAN, 9);
}
