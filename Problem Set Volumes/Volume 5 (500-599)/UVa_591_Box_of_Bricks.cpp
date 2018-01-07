
/*
	UVa 591 - Box of Bricks

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_591_Box_of_Bricks.cpp
*/

#include <iostream>
#include <vector>
using namespace std;

int main()
{
	for (int s = 1; ; s++) {
		int n;
		cin >> n;
		if (!n)
			break;
		vector<int> heights(n);
		int sum = 0;
		for (int i = 0; i < n; i++) {
			cin >> heights[i];
			sum += heights[i];
		}
		int average = sum / n;
		int nr_to_move = 0;
		for (int i = 0; i < n; i++)
			if (heights[i] > average)
				nr_to_move += heights[i] - average;
		cout << "Set #" << s << endl;
		cout << "The minimum number of moves is " << nr_to_move << ".\n\n";
	}
	return 0;
}

