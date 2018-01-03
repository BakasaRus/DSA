#include <vector>
#include <fstream>

using namespace std;

bool isHeap(vector<int> &heap)
{
	for (int i = 2; i < heap.size(); i++)
		if (heap[i] < heap[i / 2])
			return false;
	return true;
}

int main()
{
	ifstream fin("isheap.in");
	ofstream fout("isheap.out");
	int n;
	fin >> n;
	vector<int> heap(n + 1);
	for (int i = 1; i <= n; i++)
		fin >> heap[i];
	if (isHeap(heap))
		fout << "YES";
	else
		fout << "NO";
	return 0;
}