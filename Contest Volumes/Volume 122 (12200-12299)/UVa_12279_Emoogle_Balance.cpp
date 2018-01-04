
/*
	UVa 12279 - Emoogle Balance

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_12279_Emoogle_Balance.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	for (int case_nr = 1; ; case_nr++) {
		int n;
		cin >> n;
		if (!n)
			break;
		int eb = 0;
		while (n--) {
			int i;
			cin >> i;
			if (i)
				eb++;
			else
				eb--;
		}
		cout << "Case " << case_nr << ": " << eb << endl;
	}
	return 0;
}

