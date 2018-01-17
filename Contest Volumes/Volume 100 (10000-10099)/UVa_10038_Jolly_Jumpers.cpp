
/*
	2.8.1 Jolly Jumpers
	PC/UVa IDs: 110201/10038, Popularity: A, Success rate: average Level: 1

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10038_Jolly_Jumpers.cpp
*/

#include <iostream>
#include <queue>
using namespace std;

int main(int /* argc */, char** /* argv */)
{
	int n;
	while (cin >> n) {
		int i;
		cin >> i;
		if (n == 1) // the definition implies that any sequence of a single integer is a jolly jumper
			cout << "Jolly\n";
		else {
			int m = n; // save n
			priority_queue<int> queue;
			while (--m) {
				// read two consecutive numbers, calculate the difference, and enter it to the priority queue
				int j = i, k;
				cin >> i;
				if ((k = i - j) < 0)
					k = -k;
				queue.push(k);
			}
			while (--n) {
				// dequeue the differences from the queue and see if they are between 1 and (n - 1)
				if (queue.top() != n)
					break;
				queue.pop();
			}
			cout << ((n) ? "Not jolly\n" : "Jolly\n");
		}
	}
}

