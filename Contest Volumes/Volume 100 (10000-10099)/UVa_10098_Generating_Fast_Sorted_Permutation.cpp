
/*
	UVa 10098 - Generating Fast, Sorted Permutation

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10098_Generating_Fast_Sorted_Permutation.cpp
*/

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
	int n;
	cin >> n;
	while (n--) {
		string s;
		cin >> s;
		sort(s.begin(), s.end());
		do
			cout << s << endl;
		while (next_permutation(s.begin(), s.end()));
		cout << endl;
	}
	return 0;
}

