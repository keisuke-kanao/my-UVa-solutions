
/*
	UVa 10696 - f91

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10696_f91.cpp
*/

#include <iostream>
using namespace std;

int f91(int N)
{
	if (N > 100)
		return N - 10;
	else
		return f91(f91(N + 11));
}

int main()
{
	while (true) {
		int N;
		cin >> N;
		if (!N)
			break;
		cout << "f91(" << N << ") = " << f91(N) << endl;
	}
	return 0;
}

