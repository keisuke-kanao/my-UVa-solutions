
/*
	UVa 487 - Boggle Blitz

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_487_Boggle_Blitz.cpp
*/

#include <set>
#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;

const int n_max = 20, nr_dirs = 8;
const int dirs[nr_dirs][2] = {
	{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}
};
char table[n_max][n_max + 1];

struct word {
	int i_, j_;
	int length_;
	char s_[n_max * n_max + 1];
	word() : i_(-1), j_(-1), length_(0) {}
	word(int i, int j) : i_(i), j_(j), length_(0) {}
	word(const word& w) : i_(w.i_), j_(w.j_), length_(w.length_) {memcpy(s_, w.s_, w.length_);}
	word& operator=(const word& w) {i_ = w.i_; j_ = w.j_; length_ = w.length_; memcpy(s_, w.s_, w.length_); return *this;}

	void push_back(char c) {s_[length_++] = c;}

	bool operator<(const word& w) const { return (length_ != w.length_) ? length_ < w.length_ : strcmp(s_, w.s_) < 0;}
};

set<word> words;

void bfs(int n, int si, int sj)
{
	word sw(si, sj);
	sw.push_back(table[si][sj]);
	queue<word> wq;
	wq.push(sw);
	while (!wq.empty()) {
		word w = wq.front(); wq.pop();
		if (w.length_ >= 3) {
			word nw(w);
			nw.push_back('\0');
			words.insert(nw);
		}
		for (int k = 0; k < nr_dirs; k++) {
			int i = w.i_ + dirs[k][0], j = w.j_ + dirs[k][1];
			if (i >= 0 && i < n && j >= 0 && j < n && w.s_[w.length_ - 1] < table[i][j]) {
				word nw(w);
				nw.i_ = i; nw.j_ = j;
				nw.push_back(table[i][j]);
				wq.push(nw);
			}
		}
	}
}

int main()
{
	int nc;
	scanf("%d", &nc);
	while (nc--) {
		int n;
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%s", table[i]);
		words.clear();
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				bfs(n, i, j);
		for (set<word>::const_iterator i = words.begin(), e = words.end(); i != e; ++i)
			printf("%s\n", i->s_);
		if (nc)
			putchar('\n');
	}
	return 0;
}

