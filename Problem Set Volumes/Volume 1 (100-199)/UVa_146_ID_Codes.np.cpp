
/*
	UVa 146 - ID Codes

	To build using Visual Studio 20&08:
		cl -EHsc -O2 UVa_146_ID_Codes.np.cpp
*/

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
	while (true) {
		string code;
		cin >> code;
		if (code[0] == '#')
			break;
		if (next_permutation(code.begin(), code.end()))
			cout << code << endl;
		else
			cout << "No Successor\n";
	}
	return 0;
}

