
/*
	UVa 11053 - Flavius Josephus Reloaded

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11053_Flavius_Josephus_Reloaded.cpp
*/

#include <map>
#include <cstdio>
using namespace std;

int main()
{
	while (true) {
		int N;
		scanf("%d", &N);
		if (!N)
			break;
		long long a;
		int b;
		scanf("%lld %d", &a, &b);
		map<int, int> soldiers;
		soldiers[0] = 0;
		int died;
		for (int i = 0, j = 1; ; j++) {
			i = static_cast<int>((a * i % N * i % N + b) % N);
#ifdef DEBUG
			printf("%d: %d\n", i, j);
#endif
			pair<map<int, int>::iterator, bool> result = soldiers.insert(make_pair(i, j));
			if (!result.second) {
				died = result.first->second;
				break;
			}
		}
		N--;
		for (map<int, int>::const_iterator i = soldiers.begin(); i != soldiers.end(); ++i)
			if (i->second > died)
				N--;
		printf("%d\n", N);
	}
	return 0;
}

