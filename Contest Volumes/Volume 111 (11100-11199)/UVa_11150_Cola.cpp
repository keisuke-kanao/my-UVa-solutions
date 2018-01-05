
/*
	UVa 11150 - Cola

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11150_Cola.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	int n;
	while (cin >> n) {
		int nr_bottles = n;
		while (true) {
			int i = n / 3, j = n % 3;
			nr_bottles += i;
			n = i + j;
			if (!i) {
				if (j < 2)
					break;
				else
					n++;
			}
		}
		cout << nr_bottles << endl;
	}
	return 0;
}

