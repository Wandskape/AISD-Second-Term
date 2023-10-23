#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include <string>
#include <queue>
using namespace std;

map<char, string> codes;// код Хаффмана
map<char, int> freq;// частота вхождения символа в строку

vector<bool> code;
map<char, vector<bool>> table;

struct Node {
	char data;// символ
	int freq;// частота его вхождения
	Node* left, * right;

	Node(char data, int freq)
	{
		left = right = NULL;
		this->data = data;
		this->freq = freq;
	}
};


struct compare {
	bool operator()(Node* l, Node* r) { return (l->freq > r->freq); }
};

void storeCodes(struct Node* root, string str)//генерация кодов
{
	if (root == NULL)
		return;
	if (root->data != '@')
		codes[root->data] = str;
	storeCodes(root->left, str + "0");
	storeCodes(root->right, str + "1");
}

priority_queue<Node*, vector<Node*>, compare> minHeap;

void HuffmanCodes()//генерация дерева
{
	struct Node* left, * right, * top;
	for (map<char, int>::iterator itr = freq.begin(); itr != freq.end(); itr++)
		minHeap.push(new Node(itr->first, itr->second));

	while (minHeap.size() != 1) {
		left = minHeap.top();
		minHeap.pop();
		right = minHeap.top();
		minHeap.pop();
		top = new Node('@', left->freq + right->freq);
		top->left = left;
		top->right = right;
		minHeap.push(top);
	}
	storeCodes(minHeap.top(), "");
}

void calcFreq(string str)
{
	for (int i = 0; i < str.size(); i++)
		freq[str[i]]++;

	cout << "Частота вхождения символов:\n";
	for (map<char, int>::iterator itr = freq.begin(); itr != freq.end(); ++itr)
	{
		cout << "Символ: " << itr->first << " - " << "Частота: " << itr->second << endl;
	}
}

void calcFreqFile()
{
	string bufferString;
	ifstream input("input.txt");
	while (getline(input, bufferString)) {
		for (int i = 0; i < bufferString.size(); i++)
			freq[bufferString[i]]++;
	}
	input.close();
	
	cout << "Частота вхождения символов:\n";
	for (map<char, int>::iterator itr = freq.begin(); itr != freq.end(); ++itr)
	{
		cout << "Символ: " << itr->first << " - " << "Частота: " << itr->second << endl;
	}
}

string decodeString(struct Node* root, string s)
{
	string ans = "";
	struct Node* curr = root;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '0')
			curr = curr->left;
		else
			curr = curr->right;

		if (curr->left == NULL && curr->right == NULL) {
			ans += curr->data;
			curr = root;
		}
	}
	return ans + '\0';
}

void CodingFile() {
	string bufferString;
	string codingString;
	ifstream input("input.txt");
	ofstream output;
	output.open("output.txt");
	while (getline(input, bufferString)) {
		for (auto i : bufferString)
			codingString += codes[i];
		output << codingString << "\n";
		codingString = "";
	}
	input.close();
	output.close();
	cout << "\nФайл закодирован!\n" << endl;
}

void decodeFile(struct Node* root)
{
	string bufferString;
	string encodingString;
	ifstream input("output.txt");
	ofstream output;
	output.open("encoding.txt");
	string ans = "";
	struct Node* curr = root;

	while (getline(input, bufferString)) {
		for (int i = 0; i < bufferString.size(); i++) {
			if (bufferString[i] == '0')
				curr = curr->left;
			if (bufferString[i] == '1')
				curr = curr->right;
			if (curr->left == NULL && curr->right == NULL) {
				encodingString += curr->data;
				curr = root;
			}
			if (bufferString[i] == '\n')
				break;
		}
		output << encodingString << "\n";
		encodingString = "";
	}
	input.close();
	output.close();
	cout << "\nФайл раскодирован!\n" << endl;
}

void BinaryCoding() {
	calcFreqFile();
	ifstream f("input.txt", ios::out | ios::binary);

	f.clear(); f.seekg(0); // перемещаем указатель снова в начало файла

	ofstream g("coding.txt", ios::out | ios::binary);

	int count = 0; char buf = 0;
	while (!f.eof())
	{
		char c = f.get();
		vector<bool> x = table[c];
		for (int n = 0; n < 2; n++)//x.size()
		{
			buf = buf | x[n] << (7 - count);
			count++;
			if (count == 8) { count = 0;   g << buf; buf = 0; }
		}
	}

	f.close();
	g.close();
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int answer;
	cin >> answer;
	switch (answer)
	{
		case 1: {
			string str = "Коломейчук Арсений Алексеевич";
			string encodedString, decodedString;
			//cout << "Введите строку которую хотите закодировать: ";
			//getline(cin,str);
			calcFreq(str);
			HuffmanCodes();
			cout << "\nТаблица символов и кодов:\n";
			for (map<char, string>::iterator itr = codes.begin(); itr != codes.end(); itr++)
				cout << "Символ: " << itr->first << " - " << "Код: " << itr->second << endl;

			for (auto i : str)
				encodedString += codes[i];

			cout << "\nЗакодированная строка:\n" << encodedString << endl;

			decodedString = decodeString(minHeap.top(), encodedString);
			cout << "\nРаскодированная строка:\n" << decodedString << endl;
			break;
		}
		case 2: {
			calcFreqFile();
			HuffmanCodes();
			cout << "\nТаблица символов и кодов:\n";
			for (map<char, string>::iterator itr = codes.begin(); itr != codes.end(); itr++)
				cout << "Символ: " << itr->first << " - " << "Код: " << itr->second << endl;
			CodingFile();
			decodeFile(minHeap.top());
			break;
		}
		case 3: {
			calcFreqFile();
			HuffmanCodes();
			cout << "\nТаблица символов и кодов:\n";
			for (map<char, string>::iterator itr = codes.begin(); itr != codes.end(); itr++)
				cout << "Символ: " << itr->first << " - " << "Код: " << itr->second << endl;
			BinaryCoding();
			//decodeFile(minHeap.top());
			break;
		}

	default:
		break;
	}
}
