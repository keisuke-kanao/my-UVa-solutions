
/*
	UVa 10879 - Code Refactoring

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10879_Code_Refactoring.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	int nr_cases;
	cin >> nr_cases;
	for (int c = 1; c <= nr_cases; c++) {
		int k;
		cin >> k;
		cout << "Case #" << c << ": " << k << " = ";
		for (int i = 2, j = 0; ; i++)
			if (!(k % i)) {
				cout << i << " * " << k / i;
				if (j) {
					cout << endl;
					break;
				}
				else {
					cout << " = ";
					j++;
				}
			}
	}
	return 0;
}

