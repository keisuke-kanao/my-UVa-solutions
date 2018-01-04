
/*
	UVa 11839 - Optical Reader

	To build using Visual Studio 2010:
		cl -EHsc -O2 UVa_11839_Optical_Reader.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	const int nr_alternatives = 5;
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		while (n--) {
			int value, selected = -1;
			for (int i = 0; i < nr_alternatives; i++) {
				cin >> value;
				if (value <= 127) {
					if (selected == -1)
						selected = i;
					else
						selected = nr_alternatives;
				}
			}
			if (selected == -1 || selected == nr_alternatives)
				cout << "*\n";
			else
				cout << static_cast<char>('A' + selected) << endl;
		}
	}
	return 0;
}

