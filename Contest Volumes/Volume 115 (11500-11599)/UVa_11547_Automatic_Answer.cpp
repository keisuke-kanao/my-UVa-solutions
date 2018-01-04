
/*
	UVa 11547 - Automatic Answer

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11547_Automatic_Answer.cpp
*/

#include <iostream>
#include <cstdlib>
using namespace std;

int main()
{
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
//		cout << abs((((((((n * 567) / 9) + 7492) * 235) / 47) - 498) / 10) % 10) << endl;
		cout << abs((((((n * 63) + 7492) * 5) - 498) / 10) % 10) << endl;
	}
}

