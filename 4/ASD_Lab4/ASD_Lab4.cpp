#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <vector>
#include <algorithm>
using namespace std;

int** GettingMatrixInProgram() {
	int** MatrixGraph = new int* [6];
	for (int i = 0; i < 6; i++)
		MatrixGraph[i] = new int[6];

	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 6; j++)
			MatrixGraph[i][j] = 0;
	//1
	MatrixGraph[1][0] = 28;
	MatrixGraph[2][0] = 21;
	MatrixGraph[3][0] = 59;
	MatrixGraph[4][0] = 12;
	MatrixGraph[5][0] = 27;

	//2
	MatrixGraph[0][1] = 7;
	MatrixGraph[2][1] = 24;
	MatrixGraph[3][1] = 10000;
	MatrixGraph[4][1] = 21;
	MatrixGraph[5][1] = 9;

	//3
	MatrixGraph[0][2] = 9;
	MatrixGraph[1][2] = 32;
	MatrixGraph[3][2] = 13;
	MatrixGraph[4][2] = 11;
	MatrixGraph[5][2] = 10000;

	//4
	MatrixGraph[0][3] = 8;
	MatrixGraph[1][3] = 10000;
	MatrixGraph[2][3] = 5;
	MatrixGraph[4][3] = 16;
	MatrixGraph[5][3] = 10000;

	//5
	MatrixGraph[0][4] = 14;
	MatrixGraph[1][4] = 13;
	MatrixGraph[2][4] = 15;
	MatrixGraph[3][4] = 10;
	MatrixGraph[5][4] = 22;

	//6
	MatrixGraph[0][5] = 15;
	MatrixGraph[1][5] = 18;
	MatrixGraph[2][5] = 10000;
	MatrixGraph[3][5] = 10000;
	MatrixGraph[4][5] = 6;

	return MatrixGraph;
}

int** GettinMatrixInFile() {
	ifstream inputFile("MatrixGraph.txt");
	string line;
	string Number;
	bool flag = false;
	int k = 0;
	int m = 0;

	if (!inputFile) {
		cout << "Не удалось открыть файл!" << endl;
		return nullptr;
	}

	int rows = 0;
	int cols = 0;

	while (getline(inputFile, line)) {
		rows++;
		int count = 0;
		for (int i = 0; i < line.length(); i++) {
			if (line[i] == ' ') {
				count++;
			}
		}
		cols = max(cols, count);
	}

	int** MatrixGraph = new int* [rows];
	for (int i = 0; i < rows; i++) {
		MatrixGraph[i] = new int[cols];
	}

	inputFile.close();
	ifstream inputFileRead("MatrixGraph.txt");

	while (getline(inputFileRead, line)) {
		m = 0;
		if (flag) {
			k++;
		}
		for (int i = 0; i < line.length(); i++) {
			if (line[i] != ' ') {
				Number += line[i];
			}
			else {
				MatrixGraph[k][m] = stoi(Number);
				m++;
				Number = "";
			}
		}

		flag = true;
	}

	inputFileRead.close();
	return MatrixGraph;
}

int** UserInputMatrix() {
	int m;
	int n;
	cout << "Введите рамер матрицы строка/столбец: ";
	cin >> m >> n;
	int** MatrixGraph = new int* [m];
	for (int i = 0; i < m; i++)
		MatrixGraph[i] = new int[n];

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cout << "Введите элемент матрицы [" << i << "][" << j << "]: ";
			cin >> MatrixGraph[i][j];
		}
	}

	return MatrixGraph;
}

void ShowMatrix(int** MatrixGraph, int size) {

	cout << "Матрица  \n";
	int IntMax = numeric_limits<int>::min();
	string StringMax;
	string bufString;
	int tabs = 0;
	int StepTabs;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (IntMax < MatrixGraph[i][j]) {
				IntMax = MatrixGraph[i][j];
			}
		}
	}

	StringMax = to_string(IntMax);

	tabs = StringMax.size();

	for (int i = 0; i < size; i++) {
		if (i == 0) {
			cout << "   ";
		}
		cout << i + 1;

		for (int j = 0; j < tabs; j++) {
			cout << " ";
		}
	}

	cout << "\n";
	for (int i = 0; i < size; i++) {
		cout << i + 1 << "  ";
		for (int j = 0; j < size; j++) {

			bufString = to_string(MatrixGraph[i][j]);

			StepTabs = tabs - bufString.size();

			cout << MatrixGraph[i][j] << " ";
			for (int j = 0; j < StepTabs; j++) {
				cout << " ";
			}
		}
		cout << "\n";
	}
}

int** GenerateOrderVertexMatrix(int** MatrixGraph, int size) {
	int** PathMatrix = new int* [size];
	for (int i = 0; i < size; i++)
		PathMatrix[i] = new int[size];

	cout << "\nМатрица последовательности(путей) вершин\n";
	for (int i = 0; i < size; i++) {
		if (i == 0) {
			cout << "   ";
		}
		cout << i + 1 << " ";
	}
	cout << "\n";

	for (int i = 0; i < size; i++) {
		cout << i + 1 << "  ";
		for (int j = 0; j < size; j++) {
			if (MatrixGraph[j][i] != 0) {
				PathMatrix[j][i] = j + 1;
				cout << j + 1 << " ";
			}
			else {
				PathMatrix[j][i] = 0;
				cout << 0 << " ";
			}
		}
		cout << "\n";
	}
	return PathMatrix;
}

void FloydWarshellMatrix(int** MatrixGraph, int size, int** MatrixGraphPath) {
	cout << "Запуск алгоритма Флойда-Уоршелла\n";
	for (int k = 0; k < size; k++)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (MatrixGraph[i][j] > MatrixGraph[i][k] + MatrixGraph[k][j])
				{
					MatrixGraph[i][j] = MatrixGraph[i][k] + MatrixGraph[k][j];
					MatrixGraphPath[i][j] = MatrixGraphPath[k][j];
				}
			}
		}
	}

	cout << "\nМатрица последовательности(путей) вершин\n";
	for (int i = 0; i < size; i++) {
		if (i == 0) {
			cout << "   ";
		}
		cout << i + 1 << " ";
	}
	cout << "\n";

	for (int i = 0; i < size; i++) {
		cout << i + 1 << "  ";
		for (int j = 0; j < size; j++) {
			cout << MatrixGraphPath[i][j] << " ";
		}
		cout << "\n";
	}
}


//-----------------------------------------------------------------------------------------------//

int* InitMinGraph(int size) {
	int* minGraph = new int[size - 1];
	for (int i = 0; i < size - 1; i++)
		minGraph[i] = -2;
	return minGraph;
}

bool ElemetnNotInclude(int MatrixElement, int* minGraph, int size) {
	bool flag = true;
	for (int i = 0; i < size - 1; i++) {
		if (MatrixElement == minGraph[i]) {
			flag = false;
			break;
		}
	}

	if (flag)
		return true;
	else
		return false;
}

int GetCycleNumber(int** MatrixGraph, int size) {
	int edgeCount = 0;

	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			if (MatrixGraph[i][j] != 0 && MatrixGraph[i][j] != 10000) {
				edgeCount++;
			}
		}
	}
	return edgeCount - size + 1;
}

int GetEdgeCount(int** MatrixGraph, int size) {
	int edgeCount = 0;

	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			if (MatrixGraph[i][j] != 0 && MatrixGraph[i][j] != 10000) {
				edgeCount++;
			}
		}
	}
	return edgeCount;
}

void PrimeMinTreeGraph(int** MatrixGraph, int* minGraph, int size) {

	int indexI;
	int indexJ;
	int minGraphCounter = 0;
	int min = 1000000;
	int CycleNumber = size - 1;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (MatrixGraph[i][j] < min && MatrixGraph[i][j] != 0) {
				min = MatrixGraph[i][j];
				indexI = i;
				indexJ = j;
			}

		}
	}

	for (int cycle = 0; cycle < CycleNumber; cycle++) {

		minGraph[minGraphCounter] = MatrixGraph[indexI][indexJ];
		minGraphCounter++;

		for (int i = indexI; i < indexJ; i++) {
			for (int j = 0; j < size; j++) {
				if (ElemetnNotInclude(MatrixGraph[i][j], minGraph, size))
					MatrixGraph[i][j] = -1;
			}
		}

		min = 1000000;

		for (int i = 0; i < size; i++) {
			for (int j = indexI; j < indexJ; j++) {
				if (MatrixGraph[i][j] < min && MatrixGraph[i][j] != 0 && MatrixGraph[i][j] != -1) {
					min = MatrixGraph[i][j];
					indexI = i;
					indexJ = j;
				}

			}
		}
	}
}

void PrimeMinTree(int** MatrixGraph, int size) {
	int EdgeNumber = 0;
	int Iteration = size - 1;

	bool* selected = new bool[size];
	for (int i = 0; i < size; i++) {
		selected[i] = false;
	}
	selected[0] = true;

	int indexI;
	int indexJ;

	cout << "Ребро" << " : " << "вес" << endl;

	while (EdgeNumber < Iteration) {
		int min = 100000;
		indexI = 0;
		indexJ = 0;

		for (int i = 0; i < size; i++) {
			if (selected[i]) {
				for (int j = 0; j < size; j++) {
					if (!selected[j] && MatrixGraph[i][j] > 0) {
						if (min > MatrixGraph[i][j]) {
							min = MatrixGraph[i][j];
							indexI = i;
							indexJ = j;
						}
					}
				}
			}
		}

		cout << indexI << " - " << indexJ << " :  " << MatrixGraph[indexI][indexJ] << endl;
		selected[indexJ] = true;
		EdgeNumber++;
	}

}

struct Edge {
	int u, v, weight;
};

bool compareEdges(const Edge& edge1, const Edge& edge2) {
	return edge1.weight < edge2.weight;
}

int findParent(int vertex, vector<int>& parent) {
	if (parent[vertex] == -1)
		return vertex;
	return findParent(parent[vertex], parent);
}

void unionVertices(int u, int v, vector<int>& parent) {
	int srcParent = findParent(u, parent);
	int destParent = findParent(v, parent);
	parent[srcParent] = destParent;
}

void kruskalMinTree(int** MatrixGraph, int size) {
	vector<Edge> edges;
	vector<Edge> minSpanningTree;

	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			if (MatrixGraph[i][j] != 0) {
				Edge edge;
				edge.u = i;
				edge.v = j;
				edge.weight = MatrixGraph[i][j];
				edges.push_back(edge);
			}
		}
	}

	sort(edges.begin(), edges.end(), compareEdges);

	vector<int> parent(size, -1);

	for (const Edge& edge : edges) {
		int srcParent = findParent(edge.u, parent);
		int destParent = findParent(edge.v, parent);

		if (srcParent != destParent) {
			minSpanningTree.push_back(edge);
			unionVertices(srcParent, destParent, parent);
		}
	}

	cout << "Минимальное остовное дерево (ребро : вес):" << endl;
	for (const Edge& edge : minSpanningTree) {
		cout << edge.u << " - " << edge.v << " : " << edge.weight << endl;
	}
}

void main()
{
	setlocale(LC_ALL, "Rus");
	int ansver;
	int MatrixSize;

	cout << "";
	cin >> ansver;

	switch (ansver) {
	case 1: {
		cout << "Введите размерность матрицы: ";
		cin >> MatrixSize;
		cout << "\n";
		int** matrix1 = GettingMatrixInProgram();
		ShowMatrix(matrix1, MatrixSize);
		int** matrixPath = GenerateOrderVertexMatrix(matrix1, MatrixSize);
		FloydWarshellMatrix(matrix1, MatrixSize, matrixPath);
		ShowMatrix(matrix1, MatrixSize);
		break;
	}
	case 2: {
		cout << "Введите размерность матрицы: ";
		cin >> MatrixSize;
		cout << "\n";
		int** matrix2 = GettinMatrixInFile();
		ShowMatrix(matrix2, MatrixSize);
		break;
	}
	case 3: {
		cout << "Введите размерность матрицы: ";
		cin >> MatrixSize;
		cout << "\n";
		int** matrix3 = UserInputMatrix();
		ShowMatrix(matrix3, MatrixSize);
		break;
	}
	case 5: {
		cout << "Введите размерность матрицы: ";
		cin >> MatrixSize;
		cout << "\n";
		int** matrix5 = GettinMatrixInFile();
		ShowMatrix(matrix5, MatrixSize);
		cout << "Цикломатическое число: " << GetCycleNumber(matrix5, MatrixSize) << endl;
		int* minGraph = InitMinGraph(MatrixSize);
		//PrimeMinTreeGraph(matrix5, minGraph, MatrixSize);
		PrimeMinTree(matrix5, MatrixSize);
		ShowMatrix(matrix5, MatrixSize);
		break;
	}
	case 6: {
		cout << "Введите размерность матрицы: ";
		cin >> MatrixSize;
		cout << "\n";
		int** matrix6 = GettinMatrixInFile();
		kruskalMinTree(matrix6, MatrixSize);
		break;
	}
	}

}

