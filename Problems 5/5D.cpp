#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

const bool DEBUG = false;

struct Node
{
	string Key;
	vector<string> Values;
	Node *Next;
};

class List
{
	Node *Start;
public:
	List();
	void Insert(string K, string V);
	void DeleteAll(string K);
	void Delete(string K, string V);
	Node* Search(string K);
};

List::List()
{
	Start = new Node();
	Start->Key = "";
	Start->Next = nullptr;
}

void List::Insert(string K, string V)
{
	Node *NewNode = Search(K);
	if (Search(K) == nullptr)
	{
		NewNode = new Node;
		NewNode->Key = K;
		NewNode->Values.push_back(V);
		NewNode->Next = Start->Next;
		Start->Next = NewNode;
		if (DEBUG) cerr << "Insert " << K << " " << V << "\n";
	}
	else
	{
		if (DEBUG) cerr << "Replace " << K << " " << V << "\n";
		for (int i = 0; i < NewNode->Values.size(); ++i)
		{
			if (NewNode->Values[i] == V)
				return;
		}
		NewNode->Values.push_back(V);
	}
}

void List::DeleteAll(string K)
{
	Node *CurNode = Start;
	while (CurNode->Next != nullptr)
	{
		if (CurNode->Next->Key == K)
		{
			Node *NodeToDel = CurNode->Next;
			CurNode->Next = CurNode->Next->Next;
			delete NodeToDel;
			if (DEBUG) cerr << "DeleteAll " << K << "\n";
			return;
		}
		else
		{
			CurNode = CurNode->Next;
		}
	}
	if (DEBUG) cerr << "DeleteAll (unsuccessful) " << K << "\n";
}

void List::Delete(string K, string V)
{
	Node *CurNode = Start;
	while (CurNode->Next != nullptr)
	{
		if (CurNode->Next->Key == K)
		{
			for (int i = 0; i < CurNode->Next->Values.size(); ++i)
				if (CurNode->Next->Values[i] == V)
				{
					swap(CurNode->Next->Values[i], CurNode->Next->Values[CurNode->Next->Values.size() - 1]);
					CurNode->Next->Values.resize(CurNode->Next->Values.size() - 1);
				}
			if (DEBUG) cerr << "Delete " << K << " " << V << "\n";
			return;
		}
		else
		{
			CurNode = CurNode->Next;
		}
	}
	if (DEBUG) cerr << "Delete (unsuccessful) " << K << " " << V << "\n";
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

class MultiMap
{
	vector<List> Src;
	int H(string K);
public:
	MultiMap();
	void Insert(string K, string V);
	void Delete(string K, string V);
	void DeleteAll(string K);
	vector<string> Get(string K);
};

MultiMap::MultiMap()
{
	Src.resize(1000);
}

int MultiMap::H(string K)
{
	unsigned int res = 0, pow = 1, p = 31, s = Src.size();
	for (int i = 0; i < K.length(); ++i)
	{
		res += (K[i] - 'A') * pow;
		pow *= p;
	}
	return res % s;
}

void MultiMap::Insert(string K, string V)
{
	Src[H(K)].Insert(K, V);
}

void MultiMap::DeleteAll(string K)
{
	Src[H(K)].DeleteAll(K);
}

void MultiMap::Delete(string K, string V)
{
	Src[H(K)].Delete(K, V);
}

vector<string> MultiMap::Get(string K)
{
	Node *Res = Src[H(K)].Search(K);
	if (Res == nullptr)
		return {};
	else
		return Res->Values;
}

int main()
{
	ifstream fin("multimap.in");
	ofstream fout("multimap.out");
	MultiMap S;
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
			fin >> K >> V;
			S.Delete(K, V);
		}
		else if (Command == "deleteall")
		{
			fin >> K;
			S.DeleteAll(K);
		}
		else if (Command == "get")
		{
			fin >> K;
			vector<string> Res = S.Get(K);
			fout << Res.size();
			for (int i = 0; i < Res.size(); ++i)
				fout << " " << Res[i];
			fout << "\n";
		}
	}
	return 0;
}