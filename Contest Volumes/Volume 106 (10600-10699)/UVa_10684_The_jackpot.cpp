
/*
	UVa 10684 - The jackpot

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10684_The_jackpot.cpp
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
		int s = 0, max_s = -1;
		for (int i = 0; i < n; i++) {
			int b;
			cin >> b;
			s += b;
			if (s < 0)
				s = 0;
			else if (s > max_s)
				max_s = s;
		}
		if (max_s <= 0)
			cout << "Losing streak.\n";
		else
			cout << "The maximum winning streak is " << max_s << ".\n";
	}
	return 0;
}

