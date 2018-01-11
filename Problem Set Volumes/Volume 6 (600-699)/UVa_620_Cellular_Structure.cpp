
/*
	UVa 620 - Cellular Structure

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_620_Cellular_Structure.cpp
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

/*
	Let s[i, j, k] be the i-th stage of growth of an organism for the string of cells[j, k], then:
	s[i, j, k] = MUTAGENIC if cells[j] == 'B' and cells[k] == 'A' and
					s[i - 1, j + 1, k - 1] is a valid stage.
				 FULLY-GROWN if cells[k - 1] = 'A' and cells[k] == 'B' and
					s[i - 1, j, k - 2] is a valid stage.
				 SIMPLE if j == k and cells[j] == 'A'.
				 MUTANT otherwise.
*/

enum {SIMPLE, FULLY_GROWN, MUTAGENIC, MUTANT};

map<string, int> cache;

int find_stage(const string& cells, int i, int j)
{
	string c = cells.substr(i, j - i + 1);
	map<string, int>::iterator ci = cache.find(c);
	if (ci != cache.end())
		return ci->second;
	int stage = MUTANT;
	if (j - i > 1) {
		if (cells[j - 1] == 'A' && cells[j] == 'B')
			stage = (find_stage(cells, i, j - 2) == MUTANT) ? MUTANT : FULLY_GROWN;
		else if (cells[i] == 'B' && cells[j] == 'A')
			stage = (find_stage(cells, i + 1, j - 1) == MUTANT) ? MUTANT : MUTAGENIC;
	}
	else if (i == j)
		stage = (cells[i] == 'A') ? SIMPLE : MUTANT;
	cache.insert(make_pair(c, stage));
	return stage;
}

int main()
{
	const char* stages[] = {"SIMPLE", "FULLY-GROWN", "MUTAGENIC", "MUTANT"};
	int n;
	cin >> n;
	string cells;
	getline(cin, cells); // skip '\n'
	while (n--) {
		string cells;
		getline(cin, cells);
		int stage = (cells.empty()) ? MUTANT : find_stage(cells, 0, cells.length() - 1);
		cout << stages[stage] << endl;
	}
	return 0;
}

