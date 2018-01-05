
/*
	UVa 10656 - Maximum Sum (II)

	To build using Visual Studio 2008:
		cl -EHsc UVa_10656_Maximum_Sum_II.cpp
*/

#include <iostream>
using namespace std;

const int n_max = 1000;
int numbers[n_max];

int main()
{
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		for (int i = 0; i < n; i++)
			cin >> numbers[i];
		bool printed = false;
		for (int i = 0; i < n; i++)
			if (numbers[i]) {
				if (printed)
					cout << ' ';
				else
					printed = true;
				cout << numbers[i];
			}
		if (!printed)
			cout << 0;
		cout << endl;
	}
	return 0;
}

