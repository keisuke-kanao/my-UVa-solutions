
/*
	UVa 11723 - Numbering Roads

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11723_Numbering_Roads.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	for (int case_nr = 1; ; case_nr++) {
		int R, N;
		cin >> R >> N;
		if (!R && !N)
			break;
		int min_suffixes = (R + N - 1) / N - 1;
		cout << "Case " << case_nr << ": ";
		if (min_suffixes > 26)
			cout << "impossible\n";
		else
			cout << min_suffixes << endl;
	}
	return 0;
}

