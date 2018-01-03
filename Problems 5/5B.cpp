#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

const bool DEBUG = false;

struct Node
{
	string Key, Value;
	Node *Next;
};

class List
{
	Node *Start;
public:
	List();
	void Insert(string K, string V);
	void Delete(string K);
	Node* Search(string K);
};

List::List()
{
	Start = new Node();
	Start->Value = Start->Key = "";
	Start->Next = nullptr;
}

void List::Insert(string K, string V)
{
	Node *NewNode = Search(K);
	if (Search(K) == nullptr)
	{
		NewNode = new Node;
		NewNode->Key = K;
		NewNode->Value = V;
		NewNode->Next = Start->Next;
		Start->Next = NewNode;
		if (DEBUG) cerr << "Insert " << K << " " << V << "\n";
	}
	else
	{
		NewNode->Value = V;
		if (DEBUG) cerr << "Replace " << K << " " << V << "\n";
	}
}

void List::Delete(string K)
{
	Node *CurNode = Start;
	while (CurNode->Next != nullptr)
	{
		if (CurNode->Next->Key == K)
		{
			Node *NodeToDel = CurNode->Next;
			CurNode->Next = CurNode->Next->Next;
			delete NodeToDel;
			if (DEBUG) cerr << "Delete " << K << "\n";
			return;
		}
		else
		{
			CurNode = CurNode->Next;
		}
	}
	if (DEBUG) cerr << "Delete (unsuccessful) " << K << "\n";
}

Node* List::Search(string K)
{
	Node *CurNode = Start;
	while (CurNode->Next != nullptr)
	{
		if (CurNode->Next->Key == K)
		{
			if (DEBUG) cerr << "Search " << K << "\n";
			return CurNode->Next;
		}
		else
		{
			CurNode = CurNode->Next;
		}
	}
	if (DEBUG) cerr << "Search (unsuccessful) " << K << "\n";
	return nullptr;
}

class Map
{
	vector<List> Src;
	int H(string K);
public:
	Map();
	void Insert(string K, string V);
	void Delete(string K);
	string Search(string K);
};

Map::Map()
{
	Src.resize(1000);
}

int Map::H(string K)
{
	unsigned int res = 0, pow = 1, p = 31, s = Src.size();
	for (int i = 0; i < K.length(); ++i)
	{
		res += (K[i] - 'A') * pow;
		pow *= p;
	}
	return res % s;
}

void Map::Insert(string K, string V)
{
	Src[H(K)].Insert(K, V);
}

string Map::Search(string K)
{
	Node *Res = Src[H(K)].Search(K);
	if (Res == nullptr)
		return "none";
	else
		return Res->Value;
}

void Map::Delete(string K)
{
	Src[H(K)].Delete(K);
}

int main()
{
	ifstream fin("map.in");
	ofstream fout("map.out");
	Map S;
	string Command;
	while (fin >> Command)
	{
		string K, V;
		if (Command == "put")
		{
			fin >> K >> V;
			S.Insert(K, V);
		}
		else if (Command == "delete")
		{
			fin >> K;
			S.Delete(K);
		}
		else if (Command == "get")
		{
			fin >> K;
			fout << S.Search(K) << "\n";
		}
	}
	return 0;
}