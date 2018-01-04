
/*
	UVa 12136 - Schedule of a Married Man

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12136_Schedule_of_a_Married_Man.cpp
*/

#include <cstdio>

int minutes(int h, int m)
{
	return h * 60 + m;
}

int main()
{
	const int minutes_of_day = 1440;
	int N;
	scanf("%d", &N);
	for (int cn = 1; cn <= N; cn++) {
		int sh, sm, eh, em;
		scanf("%d:%d %d:%d", &sh, &sm, &eh, &em);
		int s = minutes(sh, sm), e = minutes(eh, em);
		scanf("%d:%d %d:%d", &sh, &sm, &eh, &em);
		int ms = minutes(sh, sm), me = minutes(eh, em);
		printf("Case %d: ", cn);
		if (ms >= s && ms <= e || me >= s && me <= e || ms <= s && me >= e)
			puts("Mrs Meeting");
		else
			puts("Hits Meeting");
	}
	return 0;
}

