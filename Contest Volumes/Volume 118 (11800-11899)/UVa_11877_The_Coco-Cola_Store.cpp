
/*
	UVa 11877 - The Coco-Cola Store


	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11877_The_Coco-Cola_Store.cpp

	This problem is similar to 11150 - Cola.
*/

#include <iostream>
using namespace std;

int main()
{
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		int nr_bottles = 0;
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

