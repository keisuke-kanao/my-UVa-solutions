
/*
	UVa 10919 - Prerequisites?

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10919_Prerequisites.cpp
*/

#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
	const int k_max = 100;
	int courses[k_max];
	while (true) {
		int k;
		cin >> k;
		if (!k)
			break;
		int m;
		cin >> m;
		for (int i = 0; i < k; i++)
			cin >> courses[i];
		sort(courses, courses + k);
#ifdef DEBUG
		for (int i = 0; i < k; i++) {
			if (i)
				cout << ' ';
			cout << courses[i];
		}
		cout << endl;
#endif
		bool yes = true;
		for (int i = 0; i < m; i++) {
			int c, r;
			cin >> c >> r;
			while (c--) {
				int n;
				cin >> n;
				if (yes && r && binary_search(courses, courses + k, n))
					r--;
			}
			if (r)
				yes = false;
		}
		cout << ((yes) ? "yes\n" : "no\n");
	}
	return 0;
}

