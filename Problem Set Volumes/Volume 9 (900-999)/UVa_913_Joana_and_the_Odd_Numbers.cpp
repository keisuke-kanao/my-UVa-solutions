
/*
	UVa 913 - Joana and the Odd Numbers

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_913_Joana_and_the_Odd_Numbers.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	int N;
	while (cin >> N) {
		long long i = (N + 1) / 2;
		cout << 6 * i * i - 9 << endl;
	}
	return 0;
}

