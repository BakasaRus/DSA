#include <vector>
#include <string>
#include <map>
#include <fstream>

using namespace std;

struct Node
{
	int value, line;
};

class Heap
{
	vector<Node> source;
	int size;
	void minHeapify(int index);
public:
	Heap();
	int left(int index);
	int right(int index);
	int parent(int index);
	void insert(int value, int line);
	int extractMin();
	void decreaseKey(int line, int value);
};

Heap::Heap()
{
	source.resize(1000000);
	size = 0;
}

void Heap::insert(int value, int line)
{
	size++;
	source[size].value = LONG_MAX;
	source[size].line = line;
	decreaseKey(line, value);
}

void Heap::decreaseKey(int line, int value)
{
	int pos = 0;
	for (int i = 1; i <= size; ++i)
		if (source[i].line == line)
		{
			pos = i;
			break;
		}
	if (pos == 0)
		return;
	if (source[pos].value < value)
		return;
	source[pos].value = value;
	while (pos > 1 && source[parent(pos)].value > source[pos].value)
	{
		swap(source[pos], source[parent(pos)]);
		pos = parent(pos);
	}
}

int Heap::extractMin()
{
	if (size < 1)
		return LONG_MAX;
	int min = source[1].value;
	source[1] = source[size];
	size--;
	minHeapify(1);
	return min;
}

void Heap::minHeapify(int index)
{
	int l = left(index);
	int r = right(index);
	int smallest = index;
	if (l && source[l].value < source[smallest].value)
		smallest = l;
	if (r && source[r].value < source[smallest].value)
		smallest = r;
	if (smallest != index)
	{
		swap(source[index], source[smallest]);
		minHeapify(smallest);
	}
}

int Heap::left(int index)
{
	return (2 * index > size) ? 0 : 2 * index;
}

int Heap::right(int index)
{
	return (2 * index + 1 > size) ? 0 : 2 * index + 1;
}

int Heap::parent(int index)
{
	return index / 2;
}

int main()
{
	ifstream fin("priorityqueue.in");
	ofstream fout("priorityqueue.out");
	Heap pq;
	string command;
	int i = 1;
	while (fin >> command)
	{
		if (command == "push")
		{
			int x;
			fin >> x;
			pq.insert(x, i);
		}
		if (command == "extract-min")
		{
			int x = pq.extractMin();
			if (x == LONG_MAX)
				fout << "*" << "\n";
			else
				fout << x << "\n";
		}
		if (command == "decrease-key")
		{
			int x, y;
			fin >> x >> y;
			pq.decreaseKey(x, y);
		}
		++i;
	}
	return 0;
}