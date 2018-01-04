
/*
	UVa 12709 - Falling Ants

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12709_Falling_Ants.cpp
*/

#include <cstdio>

int main()
{
	while (true) {
		int T;
		scanf("%d", &T);
		if (!T)
			break;
		int H_max = 0, v_max = 0;
		while (T--) {
			int L, W, H;
			scanf("%d %d %d", &L, &W, &H);
			int v = L * W * H;
			if (H > H_max || H == H_max && v > v_max) {
				H_max = H; v_max = v;
			}
		}
		printf("%d\n", v_max);
	}
	return 0;
}

