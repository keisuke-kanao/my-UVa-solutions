
/*
	UVa 10954 - Add All

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10954_Add_All.cpp
*/

/*
	from UVa 10954 - Algorithmist (http://www.algorithmist.com/index.php/UVa_10954)

	Using a Priority Queue, you can greedily take the two smallest numbers, 
	add them and insert them back into the Priority Queue. 
	This is similar to the Huffman algorithm.
*/

#include <iostream>
#include <functional>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int numbers_max = 5000;
int numbers[numbers_max];

int main()
{
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		for (int i = 0; i < n; i++)
			cin >> numbers[i];
		priority_queue<int, vector<int>, greater<int> > pq(numbers, numbers + n);
		int cost = 0;
		while (!pq.empty()) {
			int i = pq.top(); pq.pop();
			if (pq.empty())
				break;
			int j = pq.top(); pq.pop();
			int k = i + j;
			cost += k;
			pq.push(k);
		}
		cout << cost << endl;
	}
	return 0;
}

