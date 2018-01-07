
/*
	UVa 465 - Overflow

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_465_Overflow.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <limits>
using namespace std;

int main()
{
	string line;
	while (getline(cin, line)) {
		istringstream iss(line);
		double i, j;
		char op;
		iss >> i >> op >> j;
		double result = (op == '+') ?  i + j : i * j;
		cout << line << endl;
		if (i > numeric_limits<int>::max())
			cout << "first number too big\n";
		if (j > numeric_limits<int>::max())
			cout << "second number too big\n";
		if (result > numeric_limits<int>::max())
			cout << "result too big\n";
	}
	return 0;
}

