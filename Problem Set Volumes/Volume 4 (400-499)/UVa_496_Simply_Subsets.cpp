
/*
	UVa 496 - Simply Subsets

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_496_Simply_Subsets.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <set>
using namespace std;

int main()
{
	string line;
	istringstream iss;
	while (getline(cin, line)) {
		iss.str(line);
		size_t nr_a = 0, nr_b = 0, nr_common = 0;
		set<int> s;
		int n;
		while (iss >> n) {
			nr_a++;
			s.insert(n);
		}
		iss.clear();
		getline(cin, line);
		iss.str(line);
		while (iss >> n) {
			nr_b++;
			if (s.find(n) != s.end())
				nr_common++;
		}
		iss.clear();
		if (!nr_common) {
			if (nr_a) {
				if (nr_b)
					cout << "A and B are disjoint\n";
				else
					cout << "B is a proper subset of A\n";
			}
			else if (nr_b)
				cout << "A is a proper subset of B\n";
			else
				cout << "A equals B\n";
		}
		else if (nr_common < nr_a) {
			if (nr_common < nr_b)
				cout << "I'm confused!\n";
			else
				cout << "B is a proper subset of A\n";
		}
		else {
			if (nr_common < nr_b)
				cout << "A is a proper subset of B\n";
			else
				cout << "A equals B\n";
		}
	}
	return 0;
}

