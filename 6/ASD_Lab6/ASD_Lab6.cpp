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

void storeCodes(struct Node* root, string str)
{
	if (root == NULL)
		return;
	if (root->data != '@')
		codes[root->data] = str;
	storeCodes(root->left, str + "0");
	storeCodes(root->right, str + "1");
}

priority_queue<Node*, vector<Node*>, compare> minHeap;

void HuffmanCodes()
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


int main()
{
	setlocale(LC_ALL, "Russian");

	string str = "Коломейчук Арсений Алексеевич";
	string encodedString, decodedString;
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
	return 0;
}
