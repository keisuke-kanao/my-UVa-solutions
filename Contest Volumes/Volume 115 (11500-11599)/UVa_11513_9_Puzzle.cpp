
/*
	UVa 11513 - 9 Puzzle

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11513_9_Puzzle.cpp

	This is an accepted solution.
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
	int next_;
	int move_;
	int s_;
} paths[nr_paths_max];

int compare_path(const void* i, const void* j)
{
	const path *pi = reinterpret_cast<const path*>(i), *pj = reinterpret_cast<const path*>(j);
	return strcmp(pi->squares_, pj->squares_);
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
	// starting from the original configuration, mark the reachables configurations 
	// by moving in the reverse directions
	path p;
	strcpy(p.squares_, original_configuration);
	paths[0].next_ = 0, paths[0].s_ = 0;
	for (int i = 1; i < nr_paths_max; i++)
		paths[i].next_ = -1;
	queue<int> q;
	q.push(0);
	while (!q.empty()) {
		int pi = q.front();
		q.pop();
#ifdef DEBUG
//		printf("%d: %s %d\n", pi, paths[pi].squares_, paths[pi].next_);
#endif
		int ns = paths[pi].s_ + 1;
		for (int i = 0; i < nr_moves; i++) {
			int j;
			char c;
			path np;
			strcpy(np.squares_, paths[pi].squares_);
			if (i < m_v1) { // horizontal left moves
				j = i * 3;
				c = np.squares_[j], np.squares_[j] = np.squares_[j + 1],
					np.squares_[j + 1] = np.squares_[j + 2], np.squares_[j + 2] = c;
			}
			else { // vertical down moves
				j = i - m_v1;
				c = np.squares_[6 + j], np.squares_[6 + j] = np.squares_[3 + j],
					np.squares_[3 + j] = np.squares_[j], np.squares_[j] = c;
			}
			int npi = reinterpret_cast<path*>(bsearch (&np, paths, nr_paths_max, sizeof(path), compare_path)) - paths;
			if (paths[npi].next_ == -1) {
#ifdef DEBUG
//				printf("  %d: %s\n", npi, paths[npi].squares_);
#endif
				paths[npi].next_ = pi, paths[npi].move_ = i, paths[npi].s_ = ns;
				q.push(npi);
			}
		}
	}
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
		int pi = reinterpret_cast<path*>(bsearch (&p, paths, nr_paths_max, sizeof(path), compare_path)) - paths;
		if (paths[pi].next_ != -1) {
			printf(((pi) ? "%d " : "%d"), paths[pi].s_);
			for ( ; pi; pi = paths[pi].next_)
				printf("%s", moves[paths[pi].move_]);
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

