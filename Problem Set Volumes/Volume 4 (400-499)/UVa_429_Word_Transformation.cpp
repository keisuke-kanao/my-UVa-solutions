
/*
	UVa 429 - Word Transformation

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_429_Word_Transformation.cpp
*/

#include <queue>
#include <utility>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

const int nr_words_max = 200, nr_chars_max = 10;

struct word {
	int length_;
	char s_[nr_chars_max + 1];
} words[nr_words_max + 1];

struct edge {
	int ne_;
	int e_[nr_words_max];
} edges[nr_words_max];

int compare_word(const void* i, const void* j)
{
	return strcmp(reinterpret_cast<const word*>(i)->s_, reinterpret_cast<const word*>(j)->s_);
}

bool is_transformable(const word &i, const word& j)
{
	if (i.length_ != j.length_)
		return false;
	else {
		int n = 0;
		for (int k = 0; k < i.length_; k++)
			if (i.s_[k] != j.s_[k])
				if (++n > 1)
					return false;
		return n == 1;
	}
}

bool visited[nr_words_max];

int bfs(int n, int s, int d)
{
	if (s == d)
		return 0;
	for (int i = 0; i < n; i++)
		visited[i] = false;
	queue< pair<int, int> > q;
	visited[s] = true;
	q.push(make_pair(s, 1));
	while (!q.empty()) {
		pair<int, int> i = q.front(); q.pop();
		const edge& e = edges[i.first];
		for (int j = 0; j < e.ne_; j++) {
			int k = e.e_[j];
			if (k == d)
				return i.second;
			else if (!visited[k]) {
				visited[k] = true;
				q.push(make_pair(k, i.second + 1));
			}
		}
	}
	return -1;
}

int main()
{
	int t;
	scanf("%d", &t);
	getchar();
	getchar(); // skip a blank line
	while (t--) {
		int n = 0;
		while (true) {
			gets(words[n].s_);
			if (words[n].s_[0] == '*')
				break;
			words[n].length_ = strlen(words[n].s_);
			n++;
		}
		qsort(words, n, sizeof(word), compare_word);
		for (int i = 0; i < n; i++)
			edges[i].ne_ = 0;
		for (int i = 0; i < n - 1; i++)
			for (int j = i + 1; j < n; j++)
				if (is_transformable(words[i], words[j])) {
					edges[i].e_[edges[i].ne_++] = j;
					edges[j].e_[edges[j].ne_++] = i;
				}
		char line[2 * (nr_chars_max + 1)];
		while (gets(line) && strlen(line)) {
			word sw, dw;
			sscanf(line, "%s %s", sw.s_, dw.s_);
			int si = reinterpret_cast<word*>(bsearch(&sw, words, n, sizeof(word), compare_word)) - words;
			int di = reinterpret_cast<word*>(bsearch(&dw, words, n, sizeof(word), compare_word)) - words;
			printf("%s %s %d\n", sw.s_, dw.s_, bfs(n, si, di));
		}
		if (t)
			putchar('\n');
	}
	return 0;
}

