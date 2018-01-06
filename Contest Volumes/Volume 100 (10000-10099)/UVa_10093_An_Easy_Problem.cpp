
/*
	UVa 10093 - An Easy Problem!

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_10093_An_Easy_Problem.cpp
*/

/*
	An N-based number R is divisible by (N-1) if and only if the sum of its digits is divisible by (N-1).
*/

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

bool is_divisible(const string& R, int N)
{
	int sum = 0;
	for (const char* p = R.c_str(); *p; p++) {
		char c = *p;
		int n = -1;
		if (isdigit(c))
			n = c - '0';
		else if (isupper(c))
			n = c - 'A' + 10;
		else if (islower(c))
			n = c - 'a' + 36;
		if (n != -1) {
			if (n >= N)
				return false;
			sum += n;
			sum %= N - 1;
		}
	}
	return !sum;
}

int main()
{
	string R;
	while (cin >> R) {
		const int N_min = 2, N_max = 62;
		int N;
		for (N = N_min; N <= N_max; N++)
			if (is_divisible(R, N))
				break;
		if (N <= N_max)
			cout << N << endl;
		else
			cout << "such number is impossible!\n";
	}
	return 0;
}

