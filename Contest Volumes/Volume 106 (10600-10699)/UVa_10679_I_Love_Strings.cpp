
/*
	UVa 10679 - I Love Strings!!

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10679_I_Love_Strings.cpp

	An accepted solution.
*/

/*
	This solution is originated from 
		http://www.prefield.com/algorithm/string/aho_corasick.html
	where the Aho Corasick algorithm is implemented.
*/

#include <algorithm>
#include <vector>
#include <queue>
#include <cstdio>
#include <cstring>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

const int nr_text_chars_max = 100000, nr_queries_max = 1000, nr_pattern_chars_max = 1000;
char S[nr_text_chars_max + 1];
char T[nr_queries_max][nr_pattern_chars_max + 1];

struct PMA { // pattern matching automaton
	enum {nr_nexts_ = 128};
	PMA* nexts_[nr_nexts_]; // nexts_[0] is for failure
	vector<int> matched_;
	PMA() {memset(nexts_, 0, sizeof(nexts_));}
};

int nr_pmas;
vector<PMA*> pmas(nr_text_chars_max);

PMA* new_PMA()
{
	PMA* pma = new PMA();
	if (nr_pmas >= pmas.size())
		pmas.push_back(pma);
	else
		pmas[nr_pmas] = pma;
	nr_pmas++;
	return pma;
}

void delete_PMAs()
{
	for (int i = 0; i < nr_pmas; i++)
		delete pmas[i];
	nr_pmas = 0;
}

PMA* build_PMA(const char patterns[nr_queries_max][nr_pattern_chars_max + 1], int nr_patterns)
{
	PMA* root = new_PMA();
	root->nexts_[0] = root;
	for (int i = 0; i < nr_patterns; i++) { // make trie
		PMA* current = root;
		for (int j = 0; patterns[i][j]; j++) {
			char c = patterns[i][j];
			if (!current->nexts_[c])
				current->nexts_[c] = new_PMA();
			current = current->nexts_[c];
		}
		current->matched_.push_back(i);
	}

	// make failure link using bfs
	queue<PMA*> q;
	for (int i = 1; i < PMA::nr_nexts_; i++){
		if (root->nexts_[i]) {
			root->nexts_[i]->nexts_[0] = root;
			q.push(root->nexts_[i]);
		}
		else
			root->nexts_[i] = root;
	}
	while (!q.empty()) {
		PMA* current = q.front(); q.pop();
		for (int i = 1; i < PMA::nr_nexts_; i++) {
			if(current->nexts_[i]) {
				PMA* next = current->nexts_[0];
				while (!next->nexts_[i])
					next = next->nexts_[0];
				current->nexts_[i]->nexts_[0] = next->nexts_[i];
				q.push(current->nexts_[i]);
			}
		}
	}
	return root;
}

void match(PMA* pma, const char* s, vector<bool>& results)
{
	for (int i = 0; s[i]; i++) {
		char c = s[i];
		while (!pma->nexts_[c])
			pma = pma->nexts_[0];
		pma = pma->nexts_[c];
		for (int j = 0; j < pma->matched_.size(); j++)
			results[pma->matched_[j]] = true;
	}
}

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	int t;
	scanf("%d\n", &t);
	while (t--) {
		gets(S);
		int q;
		scanf("%d\n", &q);
		for (int i = 0; i < q; i++)
			gets(T[i]);
		PMA* root = build_PMA(T, q);
		vector<bool> results(q, false);
		match(root, S, results);
		for (int i = 0; i < q; i++)
#ifdef DEBUG
			if (results[i])
				printf("y %s\n", T[i]);
			else
				puts("n");
#else
			puts((results[i]) ? "y" : "n");
#endif
		delete_PMAs();
	}
#ifdef __ELAPSED_TIME__
	fprintf(stderr, "elapsed time = %.5lf sec.\n", static_cast<double>(clock() - start) / CLOCKS_PER_SEC);
#endif
	return 0;
}

