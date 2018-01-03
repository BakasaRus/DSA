#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

const bool DEBUG = false;

struct Node
{
	int Value;
	Node *Next;
};

class List
{
	Node *Start;
public:
	List();
	void Insert(int x);
	void Delete(int x);
	bool Search(int x);
	void Print();
};

List::List()
{
	Start = new Node();
	Start->Value = LONG_MAX;
	Start->Next = nullptr;
}

void List::Insert(int x)
{
	Node *NewNode = new Node;
	NewNode->Value = x;
	NewNode->Next = Start->Next;
	Start->Next = NewNode;
	if (DEBUG) cerr << "Insert " << x << "\n";
}

void List::Delete(int x)
{
	Node *CurNode = Start;
	while (CurNode->Next != nullptr)
	{
		if (CurNode->Next->Value == x)
		{
			Node *NodeToDel = CurNode->Next;
			CurNode->Next = CurNode->Next->Next;
			delete NodeToDel;
			if (DEBUG) cerr << "Delete " << x << "\n";
			return;
		}
		else
		{
			CurNode = CurNode->Next;
		}
	}
	if (DEBUG) cerr << "Delete (unsuccessful) " << x << "\n";
}

bool List::Search(int x)
{
	Node *CurNode = Start;
	while (CurNode->Next != nullptr)
	{
		if (CurNode->Next->Value == x)
		{
			if (DEBUG) cerr << "Search " << x << "\n";
			return true;
		}
		else
		{
			CurNode = CurNode->Next;
		}
	}
	if (DEBUG) cerr << "Search (unsuccessful) " << x << "\n";
	return false;
}

void List::Print()
{
	Node *CurNode = Start->Next;
	do
	{
		cerr << CurNode->Value << " ";
		CurNode = CurNode->Next;
	} while (CurNode != Start);
	cerr << "\n";
}

class Set
{
	vector<List> Src;
	int H(int x);
public:
	Set();
	void Insert(int x);
	bool Search(int x);
	void Delete(int x);
};

Set::Set()
{
	Src.resize(100000);
}

int Set::H(int x)
{
	int res = x % (int)Src.size();
	if (res < 0) res += Src.size();
	return res;
}

void Set::Insert(int x)
{
	if (!Search(x)) Src[H(x)].Insert(x);
}

bool Set::Search(int x)
{
	return Src[H(x)].Search(x);
}

void Set::Delete(int x)
{
	Src[H(x)].Delete(x);
}

int main()
{
	ifstream fin("set.in");
	ofstream fout("set.out");
	Set S;
	string Command;
	while (fin >> Command)
	{
		int x;
		if (Command == "insert")
		{
			fin >> x;
			S.Insert(x);
		}
		else if (Command == "delete")
		{
			fin >> x;
			S.Delete(x);
		}
		else if (Command == "exists")
		{
			fin >> x;
			if (S.Search(x))
				fout << "true\n";
			else
				fout << "false\n";
		}
	}
	return 0;
}