
/*
	UVa 501 - Black Box

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_501_Black_Box.cpp

	from Northeastern European Regional 1996 Problem B
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_EU_NERC/1996/index.html)
*/

#include <iostream>
#include <vector>
#include <queue>
#include <functional>
using namespace std;

/*
Use two heap data structures, one is maximum heap (heap1) and the other is minimum heap (heap2). 
At the step i, we have to find the number with order statistic i in the final sorted array. 
So, we keep first i-1 numbers in heap1, other numbers in heap2. Minimum from heap2 will be the answer.
*/

int main()
{
	int K;
	cin >> K;
	while (K--) {
		int M, N;
		cin >> M >> N;
		vector<int> A(M), u(N);
		for (int m = 0; m < M; m++)
			cin >> A[m];
		for (int n = 0; n < N; n++)
			cin >> u[n];
		int i = 0;
		priority_queue< int, vector<int>, less<int> > max_heap; // for 0 - (i - 1)-th numbers in descending order
		priority_queue< int, vector<int>, greater<int> > min_heap; // for i-th or greater numbers in ascending order

		for (int m = 0, n = 0; m < M; m++) {
			if (!min_heap.empty() && A[m] > max_heap.top())
				min_heap.push(A[m]);
			else
				max_heap.push(A[m]);
			for ( ; n < N && max_heap.size() + min_heap.size() == u[n]; n++) {
				while (max_heap.size() != i) {
					if (max_heap.size() < i) {
						max_heap.push(min_heap.top());
						min_heap.pop();
					}
					else {
						min_heap.push(max_heap.top());
						max_heap.pop();
					}
				}
				cout << min_heap.top() << endl;
				i++;
			}
		}
		if (K)
			cout << endl;
	}
	return 0;
}

