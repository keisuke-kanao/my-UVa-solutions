
/*
	UVa 11942 - Lumberjack Sequencing

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11942_Lumberjack_Sequencing.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	int n;
	cin >> n;
	cout << "Lumberjacks:\n";
	while (n--) {
		const int nr_lumberjacks = 10;
		int beards[nr_lumberjacks];
		for (int i = 0; i < nr_lumberjacks; i++)
			cin >> beards[i];
		bool ordered = true, ascending_order = beards[0] < beards[1];
		for (int i = 1; i < nr_lumberjacks - 1; i++)
			if (ascending_order && beards[i] > beards[i + 1] ||
				!ascending_order && beards[i] < beards[i + 1]) {
				ordered = false; break;
			}
		cout << ((ordered) ? "Ordered\n" : "Unordered\n");
	}
}

