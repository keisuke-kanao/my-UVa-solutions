
/*
	UVa 10812 - Beat the Spread!

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10812_Beat_the_Spread.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	int n;
	cin >> n;
	while (n--) {
		int s, d;
		cin >> s >> d;
		int i = s - d, j = s + d;
		if (i >= 0 && !(i & 1) && !(j & 1))
			cout << j / 2 << ' ' << i / 2 << endl;
		else
			cout << "impossible\n";
	}
	return 0;
}

