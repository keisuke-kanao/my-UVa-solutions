
/*
	UVa 941 - Permutations

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_941_Permutations.cpp
*/

#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

int main()
{
	const int nr_chars_max = 20;
	long long factorials[nr_chars_max];
		// factorials[i] is i!
	factorials[0] = factorials[1] = 1;
	for (int i = 2; i < nr_chars_max; i++)
		factorials[i] = factorials[i - 1] * i;

	int nr_samples;
	scanf("%d", &nr_samples);
	while (nr_samples--) {
		char S[nr_chars_max + 1];
		long long N;
		scanf("%s", S);
		scanf("%lld", &N);
		int length = strlen(S);
		sort(S, S + length);
		vector<char> s(S, S + length), t;
		for (int i = length - 1; i; i--) {
			int j = N / factorials[i];
			t.push_back(s[j]);
			s.erase(s.begin() + j);
			N %= factorials[i];
		}
		t.push_back(s[0]);
		t.push_back('\0');
		printf("%s\n", &t[0]);
	}
	return 0;
}

