
/*
	UVa 12992 - Huatuo's Medicine

	To build using Visual Studio 2015:
		cl -EHsc -O2 UVa_12992_Huatuos_Medicine.cpp
*/

#include <cstdio>

int main()
{
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int N;
		scanf("%d", &N);
		printf("Case #%d: %d\n", t, N * 2 - 1);
	}
	return 0;
}

