
/*
	UVa 12186 - Another Crisis

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12186_Another_Crisis.cpp
*/

/*
Applied dynamic programming.
Caluculated the number of workers who should file a petition to a boss 
by choosing the necessary number of subordinates by ascending order of their workers 
who, in turn, should file a petition to them.
Did this calculation recursively.
*/

#include <algorithm>
#include <vector>
#include <cstdio>
#include <cmath>
using namespace std;

const int N_max = 100000;
int N;
double T;
vector<int> subordinates[N_max + 1];
int nr_workers[N_max + 1];
	// nr_workds[i] is the number of workers who should file a petition to i-th boss

int file_petitions(int bi)
{
	int& nr = nr_workers[bi];
	if (nr != -1)
		return nr;
	const vector<int>& sbs = subordinates[bi];
	if (sbs.empty())
		return nr = 1;
	vector<int> nrs;
	for (size_t i = 0; i < sbs.size(); i++)
		nrs.push_back(file_petitions(sbs[i]));
	sort(nrs.begin(), nrs.end());
	nr = 0;
	for (size_t i = 0, min_nr = static_cast<size_t>(ceil(sbs.size() * T)); i < min_nr; i++)
		nr += nrs[i];
	return nr;
}

int main()
{
	while (true) {
		scanf("%d %lf", &N, &T);
		if (!N)
			break;
		T /= 100.0;
		for (int i = 0; i <= N; i++) {
			subordinates[i].clear();
			nr_workers[i] = -1;
		}
		for (int i = 1; i <= N; i++) {
			int Bi;
			scanf("%d", &Bi);
			subordinates[Bi].push_back(i);
		}
		printf("%d\n", file_petitions(0));
#ifdef DEBUG
		for (int i = 0; i <= N; i++)
			printf("%d:%d%c", i, nr_workers[i], ((i < N) ? ' ' : '\n'));
#endif
	}
	return 0;
}

