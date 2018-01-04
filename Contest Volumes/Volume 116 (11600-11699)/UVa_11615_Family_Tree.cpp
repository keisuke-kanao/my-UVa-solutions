
/*
	UVa 11615 - Family Tree

	To build using Visual Studio 2015:
		cl -EHsc -O2 UVa_11615_Family_Tree.cpp
*/

#include <algorithm>
#include <cstdio>
#include <cmath> // C++11
using namespace std;

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		int N;
		double A, B;
		scanf("%d %lf %lf", &N, &A, &B);
		int n = (1 << N) - 1;
		int m = static_cast<int>(max(log2(A), log2(B)));
		n -= (1 << (N - m)) - 2;
		printf("%d\n", n);
	}
	return 0;
}

