
/*
	UVa 11498 - Division of Nlogonia

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11498_Division_of_Nlogonia.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	while (true) {
		int k;
		cin >> k;
		if (!k)
			break;
		int n, m;
		cin >> n >> m;
		for (int i = 0; i < k; i++) {
			int x, y;
			cin >> x >> y;
			if (x == n || y == m)
				cout << "divisa\n";
			else if (x > n && y > m)
				cout << "NE\n";
			else if (x > n && y < m)
				cout << "SE\n";
			else if (x < n && y < m)
				cout << "SO\n";
			else
				cout << "NO\n";
		}
	}
	return 0;
}

