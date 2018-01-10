
/*
	UVa 146 - ID Codes

	To build using Visual Studio 20&08:
		cl -EHsc -O2 UVa_146_ID_Codes.cpp
*/

/*
	For a code of length n:
		c(0)c(1)c(2)...c(i)...c(n - 1)
	Let its succesor be:
		s(0)s(1)s(2)...s(i)...s(n - 1)
	Then
		c(j) == s (j) for 0 <= j < i
		s(i) > min{c(i), c(i + 1), ... c(n - 1)}
		s(i + 1) <= s(i + 2) <= ... <= s(n - 1)
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	while (true) {
		string code;
		cin >> code;
		if (code[0] == '#')
			break;
		int i = code.length() - 1;
		for ( ; i; i--)
			if (code[i - 1] < code[i])
				break;
		if (!i)
			cout << "No Successor\n";
		else {
			// code[i - 1] = min{code[i], code[i + 1], ..., code[code.length() - 1]
			// find the second smallest character from code[i], code[i + 1], ..., code[code.length() - 1]
			int second_smallest = - 1;
			char c = 'z' + 1;
			for (int j = i; j < code.length(); j++)
				if (code[j] > code[i - 1] && code[j] < c) {
					second_smallest = j; c = code[j];
				}
			if (second_smallest != -1)
				swap(code[i - 1], code[second_smallest]);
			sort(code.begin() + i, code.end());
			cout << code << endl;
		}
	}
	return 0;
}

