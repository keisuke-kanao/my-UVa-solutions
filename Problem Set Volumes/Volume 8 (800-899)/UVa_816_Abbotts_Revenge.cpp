
/*
	UVa 816 - Abbott's Revenge

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_816_Abbotts_Revenge.cpp
*/

#include <vector>
#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;

enum {north, south, east, west};
enum {left, forward_, right};
const int nr_rows = 9, nr_columns = 9, nr_nsew = west - north + 1, nr_lfr = right - left + 1,
	nr_name_chars_max = 20, nr_chars_max = 8;

bool exits[nr_rows + 1][nr_columns + 1][nr_nsew][nr_lfr];
	// path[r][c][f][t] is true if the path to (r, c) from f to can be exited
bool visited[nr_rows + 1][nr_columns + 1][nr_nsew][nr_lfr];

int symbol_values[] = {
	0, 0, 0, 0, east, forward_, 0, 0, 0, 0, 0, left, 0, north, 0, 0, 0, right, south, 0, 0, 0, west, 0, 0, 0
};

struct path {
	int r_, c_;
	vector<int> froms_; // vector of north, south, east or west

	path() {}
	path(const path& p) : r_(p.r_), c_(p.c_), froms_(p.froms_) {}
	path(int r, int c, const vector<int>& froms, int f) : r_(r), c_(c), froms_(froms) {froms_.push_back(f);}
};

const int next_dirs[nr_nsew][nr_lfr] = { // dirs[f][t] is the next direction from f to t
	{west, north, east},
	{east, south, west},
	{north, east, south},
	{south, west, north}
};

void next_path(int from, int &r, int& c)
{
	switch (from) {
	case north:
		r--; break;
	case south:
		r++; break;
	case east:
		c++; break;
	case west:
		c--; break;
	}
}

void print_paths(int sr, int sc, const vector<int>& froms)
{
	int r = sr, c = sc;
	size_t i, j;
	for (i = 0, j = froms.size(); i < j; i++) {
		if (!(i % 10))
			printf("  ");
		printf("(%d,%d)%c", r, c, (((i % 10) == 9) ? '\n' : ' '));
		next_path(froms[i], r, c);
	}
	if (!(i % 10))
		printf("  ");
	printf("(%d,%d)\n", r, c);
}

int main()
{
	while (true) {
		char name[nr_name_chars_max + 1];
		scanf("%s", name);
		if (!strcmp(name, "END"))
			break;
		memset(exits, 0, sizeof(exits));
		memset(visited, 0, sizeof(visited));
		int sr, sc, gr, gc, sd;
		char s[nr_chars_max];
		scanf("%d %d %s %d %d", &sr, &sc, s, &gr, &gc);
		sd = symbol_values[s[0] - 'A'];
		while (true) {
			int r, c;
			scanf("%d", &r);
			if (!r)
				break;
			scanf("%d", &c);
			while (true) {
				scanf("%s", s);
				if (s[0] == '*')
					break;
				int f = symbol_values[s[0] - 'A'];
				for (int i = 1; s[i]; i++)
					exits[r][c][f][symbol_values[s[i] - 'A']] = true;
			}
		}
		printf("%s\n", name);
		bool solution = false;
		queue<path> q;
		visited[sr][sc][sd][forward_] = true;
		q.push(path(sr, sc, vector<int>(), sd));
		while (!q.empty()) {
			path u = q.front(); q.pop();
			int from = u.froms_.back(), r = u.r_, c = u.c_;
#ifdef DEBUG
			printf("%d %d %d %d\n", r, c, u.froms_.back(), u.forms_.size());
#endif
			next_path(from, r, c);
			if (r == gr && c == gc) {
				solution = true;
				print_paths(sr, sc, u.froms_);
				break;
			}
			if (r >= 1 && r <= nr_rows && c >= 1 && c <= nr_columns)
				for (int to = left; to <= right; to++)
					if (exits[r][c][from][to] && !visited[r][c][from][to]) {
						visited[r][c][from][to] = true;
						q.push(path(r, c, u.froms_, next_dirs[from][to]));
					}
		}
		if (!solution)
			puts("  No Solution Possible");
	}
	return 0;
}

