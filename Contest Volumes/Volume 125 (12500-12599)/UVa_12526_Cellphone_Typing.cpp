
/*
	UVa 12526 - Cellphone Typing

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12526_Cellphone_Typing.cpp
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int N_max = 100000, nr_chars_max = 80;
struct word {
	char s_[nr_chars_max + 1];

	bool operator<(const word& w) const {return strcmp(s_, w.s_) < 0;}
} words[N_max];

int typing(word& w, int i, int low, int high, int nr_typing)
{
	if (low == high || !w.s_[i])
		return nr_typing;
	char c = w.s_[i + 1];
	w.s_[i + 1] = '\0';
	int l = lower_bound(words + low, words + high, w) - words;
	w.s_[i]++;
	int h = lower_bound(words + low, words + high, w) - words;
	w.s_[i]--, w.s_[i + 1] = c;
	if (i && l == low && h == high)
		;
	else
		nr_typing++;
	return typing(w, i + 1, l, h, nr_typing);
}

int main()
{
	int N;
	while (scanf("%d", &N) != EOF) {
		for (int i = 0; i < N; i++)
			scanf("%s", words[i].s_);
		sort(words, words + N);
		int nr_typings = 0;
		for (int i = 0; i < N; i++) {
			word w;
			strcpy(w.s_, words[i].s_);
			int nr = typing(w, 0, 0, N, 0);
#ifdef DEBUG
			printf("%s: %d\n", w.s_, nr);
#endif
			nr_typings += nr;
		}
		printf("%.2lf\n", static_cast<double>(nr_typings) / N);
	}
	return 0;
}

