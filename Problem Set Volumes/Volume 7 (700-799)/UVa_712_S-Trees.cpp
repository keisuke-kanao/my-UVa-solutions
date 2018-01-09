
/*
	UVa 712 - S-Trees

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_712_S-Trees.cpp

	from ACM Mid-Central European Regional Contest 1999 Problem B
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_EU_MCRC/1999/index.html)

	The ACM ICPC Problem Set Archive
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive.html)
*/

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int calculate_vva(int depth, const int* ordering, int nr_values, const int* values, const int* vva)
{
	if (!depth)
		return *values;
	else {
		int i = *ordering++;
		int value = *(vva + i);
		return (value) ?
			calculate_vva(depth - 1, ordering, nr_values / 2, values + nr_values / 2, vva) :
			calculate_vva(depth - 1, ordering, nr_values / 2, values, vva);
	}
}

int main()
{
	for (int nr = 1; ; nr++) {
		int depth;
		cin >> depth;
		if (!depth)
			break;
		vector<int> ordering(depth);
			// ordering[i] is the zero-based index of whose variable is to be evaluated in (i + 1)-th order
		for (int i = 0; i < depth; i++) {
			char x;
			int j;
			cin >> x >> j;
			ordering[i] = j - 1;
		}
		int nr_values = static_cast<int>(pow(2.0, static_cast<double>(depth)));
		vector<int> values(nr_values, 0); // terminal node values
		for (int i = 0; i < nr_values; i++) {
			char c;
			cin >> c;
			if (c == '1')
				values[i] = 1;
		}
		int nr_vvas; // number of Variable Values Assignments
		cin >> nr_vvas;
		vector<int> results(nr_vvas);
		for (int i = 0; i < nr_vvas; i++) {
			vector<int> vva(depth, 0);
			for (int j = 0; j < depth; j++) {
				char c;
				cin >> c;
				if (c == '1')
					vva[j] = 1;
			}
			results[i] = calculate_vva(depth, &ordering[0], nr_values, &values[0], &vva[0]);
		}
		cout << "S-Tree #" << nr << ":\n";
		for (int i = 0; i < nr_vvas; i++)
			cout << results[i];
		cout << endl << endl;
	}
	return 0;
}

