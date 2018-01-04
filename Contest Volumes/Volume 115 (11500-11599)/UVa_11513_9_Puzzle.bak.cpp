
/*
	UVa 11513 - 9 Puzzle

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11513_9_Puzzle.cpp

	This solution was never submitted, but if it were, it would probably be verdicted as TLE.
*/

#include <algorithm>
#include <queue>
#include <cstdio>
#include <cstring>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

const int nr_squares = 9;
const int nr_paths_max = 362880; // 9!

enum {m_h1, m_h2, m_h3, m_v1, m_v2, m_v3};
const int nr_moves = m_v3 - m_h1 + 1;
const char* original_configuration = "123456789";
const char *moves[] = {"H1", "H2", "H3", "V1", "V2", "V3"};

struct path {
	char squares_[nr_squares];
	int prev_;
	int move_;
} paths[nr_paths_max];

int compare_path(const void* i, const void* j)
{
	const path *pi = reinterpret_cast<const path*>(i), *pj = reinterpret_cast<const path*>(j);
	return strcmp(pi->squares_, pj->squares_);
}

void print_moves(int pi)
{
	if (paths[pi].prev_ != pi) {
		print_moves(paths[pi].prev_);
		printf("%s", moves[paths[pi].move_]);
	}
}

bool bfs(int end, const path* pp)
{
	int pi = reinterpret_cast<path*>(bsearch (pp, paths, nr_paths_max, sizeof(path), compare_path)) - paths;
	if (paths[pi].prev_ == nr_paths_max)
		return false;
	queue<int> q;
	paths[pi].prev_ = pi; // mark as start
	q.push(pi);
	while (!q.empty()) {
		pi = q.front();
		q.pop();
#ifdef DEBUG
//		printf("%d: %s %d\n", pi, paths[pi].squares_, paths[pi].prev_);
#endif
		if (pi == end) // reached the original configuration
			break;
		for (int i = 0; i < nr_moves; i++) {
			int j;
			char c;
			path np;
			strcpy(np.squares_, paths[pi].squares_);
			if (i < m_v1) { // horizontal right moves
				j = i * 3;
				c = np.squares_[j + 2], np.squares_[j + 2] = np.squares_[j + 1],
					np.squares_[j + 1] = np.squares_[j], np.squares_[j] = c;
			}
			else { // vertical up moves
				j = i - m_v1;
				c = np.squares_[j], np.squares_[j] = np.squares_[3 + j],
					np.squares_[3 + j] = np.squares_[6 + j], np.squares_[6 + j] = c;
			}
			int npi = reinterpret_cast<path*>(bsearch (&np, paths, nr_paths_max, sizeof(path), compare_path)) - paths;
			if (paths[npi].prev_ == -1) {
#ifdef DEBUG
//				printf("  %d: %s\n", npi, paths[npi].squares_);
#endif
				paths[npi].prev_ = pi, paths[npi].move_ = i;
				q.push(npi);
			}
		}
	}
	return true;
}

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	char s[nr_squares + 1];
	strcpy(s, original_configuration);
	int nr_paths = 0;
	do {
		strcpy(paths[nr_paths].squares_, s);
		nr_paths++;
	} while (next_permutation(s, s + nr_squares));
#ifdef DEBUG
	printf("%d\n", nr_paths);
#endif
	path p;
	strcpy(p.squares_, original_configuration);
	for (int i = 0; i < nr_paths_max; i++)
		paths[i].prev_ = -1;
	bfs(nr_paths, &p);
#ifdef DEBUG
	int nr_unreachables = 0;
#endif
	for (int i = 0; i < nr_paths_max; i++)
		if (paths[i].prev_ == -1) {
#ifdef DEBUG
			nr_unreachables++;
			printf("%s\n", paths[i].squares_);
#endif
			paths[i].prev_ = nr_paths_max;
		}
#ifdef DEBUG
	printf("%d\n", nr_unreachables);
#endif
	while (true) {
		int n, i = 0;
		scanf("%d", &n);
		if (!n)
			break;
		p.squares_[i++] = n + '0';
		for ( ; i < nr_squares; i++) {
			scanf("%d", &n);
			p.squares_[i] = n + '0';
		}
		for (int i = 0; i < nr_paths_max; i++)
			if (paths[i].prev_ < nr_paths_max)
				paths[i].prev_ = -1;
		if (bfs(0, &p)) {
			int s = 0;
			for (int i = 0, prev = paths[0].prev_; i != prev; i = prev, prev = paths[prev].prev_)
				s++;
			printf("%d ", s);
			print_moves(0);
			putchar('\n');
		}
		else
			puts("Not solvable");
	}
#ifdef __ELAPSED_TIME__
	fprintf(stderr, "elapsed time = %lf sec.\n", static_cast<double>(clock() - start) / CLOCKS_PER_SEC);
#endif
	return 0;
}

/*

Sample Input

2 3 1
4 5 6
7 8 9
7 3 9
2 5 1
4 8 6
1 2 3
4 5 6
7 9 8
0

Sample Output

1 H1
3 V1V3H1
Not solvable

*/

