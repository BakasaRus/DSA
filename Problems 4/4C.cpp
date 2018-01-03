#include <fstream>
#include <string>
#include <vector>

using namespace std;

const bool DEBUG = false;

struct Node
{
	int key;
	Node *p, *l, *r;
};

class BST
{
	Node *root = nullptr;

public:
	void insert(int x);
	void remove(int x);
	Node* search(int x);
	bool exists(int x);
	Node* next(int x);
	Node* prev(int x);
	Node* min(Node* r);
	Node* max(Node* r);
	void InorderWalk(Node* r, vector<int> &Keys);
	bool isCorrect();
};

void BST::insert(int x)
{
	if (exists(x)) return;
	Node *newNode = new Node;
	newNode->key = x;
	newNode->p = newNode->l = newNode->r = nullptr;
	Node *curPos = root;
	while (curPos != nullptr)
	{
		newNode->p = curPos;
		if (newNode->key < curPos->key)
			curPos = curPos->l;
		else
			curPos = curPos->r;
	}
	if (newNode->p == nullptr)
		root = newNode;
	else if (newNode->key < newNode->p->key)
		newNode->p->l = newNode;
	else
		newNode->p->r = newNode;
}

void BST::remove(int x)
{
	Node *delNode = search(x);
	if (delNode == nullptr)
		return;
	Node *y, *u;
	if (delNode->l == nullptr || delNode->r == nullptr)
		y = delNode;
	else
		y = next(x);
	if (y->l != nullptr)
		u = y->l;
	else
		u = y->r;
	if (u != nullptr)
		u->p = y->p;
	if (y->p == nullptr)
		root = u;
	else if (y == y->p->l)
		y->p->l = u;
	else
		y->p->r = u;
	if (y != delNode)
		delNode->key = y->key;
	delete y;
}

Node* BST::search(int x)
{
	Node *curNode = root;
	while (curNode != nullptr && x != curNode->key)
		if (x < curNode->key)
			curNode = curNode->l;
		else
			curNode = curNode->r;
	return curNode;
}

bool BST::exists(int x)
{
	return search(x) != nullptr;
}

Node* BST::next(int x)
{
	Node *curNode = root, *sucNode = nullptr;
	while (curNode != nullptr)
		if (curNode->key > x)
		{
			sucNode = curNode;
			curNode = curNode->l;
		}
		else
			curNode = curNode->r;
	return sucNode;
}

Node* BST::prev(int x)
{
	Node *curNode = root, *prevNode = nullptr;
	while (curNode != nullptr)
		if (curNode->key < x)
		{
			prevNode = curNode;
			curNode = curNode->r;
		}
		else
			curNode = curNode->l;
	return prevNode;
}

void BST::InorderWalk(Node* r, vector<int> &Keys)
{
	if (r != nullptr)
	{
		InorderWalk(r->l, Keys);
		Keys.push_back(r->key);
		InorderWalk(r->r, Keys);
	}
}

bool BST::isCorrect()
{
	vector<int> keys;
	InorderWalk(root, keys);
	for (int i = 1; i < keys.size(); ++i)
		if (keys[i - 1] >= keys[i])
			return false;
	return true;
}

Node* BST::min(Node* r)
{
	while (r->l != nullptr)
		r = r->l;
	return r;
}

Node* BST::max(Node* r)
{
	while (r->r != nullptr)
		r = r->r;
	return r;
}

int main()
{
	ifstream fin("bstsimple.in");
	ofstream fout("bstsimple.out");
	BST tree;
	string command;
	int value;
	while (fin >> command >> value)
	{
		if (command == "insert")
		{
			tree.insert(value);
			if (DEBUG) fout << (tree.isCorrect() ? "correct" : "incorrect") << endl;
		}
		if (command == "delete")
		{
			tree.remove(value);
			if (DEBUG) fout << (tree.isCorrect() ? "correct" : "incorrect") << endl;
		}
		if (command == "exists")
			if (tree.search(value))
				fout << "true\n";
			else
				fout << "false\n";
		if (command == "next")
		{
			Node *res = tree.next(value);
			if (res == nullptr)
				fout << "none\n";
			else
				fout << res->key << "\n";
		}
		if (command == "prev")
		{
			Node *res = tree.prev(value);
			if (res == nullptr)
				fout << "none\n";
			else
				fout << res->key << "\n";
		}
	}
	return 0;
}