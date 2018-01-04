
/*
	UVa 446 - Kibbles "n" Bits "n" Bits "n" Bits

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_446_Kibbles.cpp
*/

#include <iostream>
using namespace std;

void print_binary(int n)
{
	cout << static_cast<char>('0');
	for (int b = 0x800; b; b >>=1)
		cout << ((n & b) ? static_cast<char>('1') : static_cast<char>('0'));
}

int main()
{
	int n;
	cin >> n;
	while (n--) {
		int i, j;
		char op;
		cin >> hex >> i >> op >> j;
		print_binary(i);
		cout << ' ' << op << ' ';
		print_binary(j);
		cout << " = ";
		if (op == '+')
			cout << dec << i + j << endl;
		else
			cout << dec << i - j << endl;
	}
	return 0;
}

