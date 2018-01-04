
/*
	UVa 12626 - I love Pizza

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12626_I_love_Pizza.cpp
*/

#include <algorithm>
#include <utility>
#include <cstdio>
#include <cstring>
using namespace std;

int main()
{
	int n;
	scanf("%d", &n);
	const int nr_chars_max = 600;
	char s[nr_chars_max + 1];
	const int nr_letters = 'Z' - 'A' + 1;
	int counts[nr_letters];
	const pair<char, int> ingredients[] = {
		make_pair('M', 1), make_pair('A', 3), make_pair('R', 2), make_pair('G', 1), make_pair('I', 1), make_pair('T', 1)
	};
	while (n--) {
		scanf("%s", s);
		memset(counts, 0, sizeof(counts));
		for (const char* p = s; *p; p++)
			counts[*p - 'A']++;
		int count = counts[ingredients[0].first - 'A'] / ingredients[0].second;
		for (size_t i = 1; i < sizeof(ingredients) / sizeof(ingredients[0]); i++)
			count = min(count, counts[ingredients[i].first - 'A'] / ingredients[i].second);
		printf("%d\n", count);
	}
	return 0;
}

