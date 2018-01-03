#include <vector>
#include <fstream>
#include <string>

using namespace std;

class Heap
{
	vector<int> source;
	int size;
	void buildMaxHeap();
	void maxHeapify(int index);
public:
	int left(int index);
	int right(int index);
	int parent(int index);
	Heap(vector<int> source_);
	vector<int> sort();
	string to_string()
	{
		string res = "";
		for (int i = 1; i < source.size(); i++)
			res += std::to_string(source[i]) + " ";
		return res;
	}
};

Heap::Heap(vector<int> source_)
{
	// Помещаем нулевой элемент для корректного поиска родителей и детей в массиве
	// Также нулевой элемент будет символизировать отсутствие левого/правого ребёнка при запросе
	source.push_back(0);
	for (int i = 0; i < source_.size(); i++)
		source.push_back(source_[i]);
	size = source.size();
	buildMaxHeap();
}

void Heap::buildMaxHeap()
{
	for (int i = (size - 1) / 2; i >= 1; i--)
		maxHeapify(i);
}

void Heap::maxHeapify(int index)
{
	int l = left(index);
	int r = right(index);
	int largest = index;
	if (l && source[l] > source[index])
		largest = l;
	if (r && source[r] > source[largest])
		largest = r;
	if (largest != index)
	{
		swap(source[index], source[largest]);
		maxHeapify(largest);
	}
}

int Heap::left(int index)
{
	return (2 * index > size - 1) ? 0 : 2 * index;
}

int Heap::right(int index)
{
	return (2 * index + 1 > size - 1) ? 0 : 2 * index + 1;
}

int Heap::parent(int index)
{
	return index / 2;
}

vector<int> Heap::sort()
{
	for (int i = source.size() - 1; i > 1; i--)
	{
		swap(source[i], source[1]);
		size--;
		maxHeapify(1);
	}
	vector<int> res(source);
	size = source.size();
	buildMaxHeap();
	return res;
}

int main()
{
	ifstream fin("sort.in");
	ofstream fout("sort.out");
	int n;
	fin >> n;
	vector<int> s(n);
	for (int i = 0; i < n; i++)
		fin >> s[i];
	Heap h(s);
	vector<int> r = h.sort();
	for (int i = 1; i < r.size(); i++)
		fout << r[i] << " ";
}