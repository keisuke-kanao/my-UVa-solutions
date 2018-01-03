
/*
	UVa 1394 - And Then There Was One

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1394_And_Then_There_Was_One.cpp

	This is Josephus problem (http://en.wikipedia.org/wiki/Josephus_problem).
*/

/*
#include <stdio.h>

int main () {
	int n, k, m;
	while (scanf("%d%d%d", &n, &k, &m) == 3 && n + k + m) {
		int ans = 0;
		for (int i = 2; i <n; i++)
			ans = (ans + k) % i;
		printf("%d\n", (ans + m) % n + 1);
	}
	return 0;
}
*/

#include <vector>
#include <cstdio>
using namespace std;

int main()
{
	while (true) {
		int n, k, m;
		scanf("%d %d %d", &n, &k, &m);
		if (!n)
			break;
		vector<int> numbers(n - 1);
		for (int i = 1, j = 0; i <= n; i++)
			if (i != m)
				numbers[j++] = i;
		n--, k--;
		for (int i = m - 1; n; n--) {
#ifdef DEBUG
			printf("n:%d i:%d ", n, i);
			for (int j = 0; j < n; j++)
				printf("%d%c", numbers[j], ((j < n - 1) ? ' ' : '\n'));
#endif
			i = (i + k) % n;
			numbers.erase(numbers.begin() + i);
		}
		printf("%d\n", numbers[0]);
	}
	return 0;
}


