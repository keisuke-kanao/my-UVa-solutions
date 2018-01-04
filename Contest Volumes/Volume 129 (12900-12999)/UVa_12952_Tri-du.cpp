
/*
	UVa 12952 - Tri-du

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12952_Tri-du.cpp
*/

#include <algorithm>
#include <cstdio>
using namespace std;

int main()
{
	int A, B;
	while (scanf("%d %d", &A, &B) != EOF)
		printf("%d\n", max(A, B));
	return 0;
}

