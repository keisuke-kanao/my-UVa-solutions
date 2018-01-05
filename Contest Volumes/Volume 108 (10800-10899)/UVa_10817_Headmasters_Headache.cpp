
/*
	UVa 10817 - Headmaster's Headache

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10817_Headmasters_Headache.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#ifdef DEBUG
#include <cstdio>
#endif
using namespace std;

const int N_max = 100, S_max = 8;
const int pow3s[S_max + 1] = {1, 3, 9, 27, 81, 243, 729, 2187, 6561};

void read_input(int& c, vector<int>& subjects)
{
	string line;
	getline(cin, line);
	istringstream iss(line);
	iss >> c;
	int s;
	while (iss >> s)
		subjects[s - 1]++;
}

int get_index(int s, const vector<int>& subjects)
{
	int index = 0;
	for (int i = 0; i < s; i++)
		index += ((subjects[i] > 2) ? 2 : subjects[i]) * pow3s[i];
	return index;
}

void get_subjects(int index, int s, vector<int>& subjects)
{
	int i;
	for (i = 0; i < s && index; i++, index /= 3)
		subjects[i] = index % 3;
	for ( ; i < s; i++)
		subjects[i] = 0;
}

#ifdef DEBUG
void print_cost(int s, const vector<int>& subjects, int cost)
{
	putchar('[');
	for (int i = 0; i < s; i++) {
		if (i)
			putchar(' ');
		printf("%d", subjects[i]);
	}
	printf("]:%d ", cost);
}
#endif

int main()
{
	while (true) {
		string line;
		getline(cin, line);
		istringstream iss(line);
		int S, m, n;
		iss >> S >> m >> n;
		iss.clear();
		if (!S)
			break;
		int icost = 0;
		vector<int> isubjects(S, 0);
		while (m--) {
			int c;
			read_input(c, isubjects);
			icost += c;
		}
#ifdef DEBUG
		printf("%3d ", 0);
		print_cost(S, isubjects, icost);
		putchar('\n');
#endif
		int s = pow3s[S];
		vector< vector<int> > costs(n + 1, vector<int>(s, -1));
		costs[0][get_index(S, isubjects)] = icost;
		for (int i = 1; i <= n; i++) {
			int c;
			vector<int> subjects(S, 0), psubjects(S);
			read_input(c, subjects);
			for (int j = 0; j < s; j++)
				if (costs[i - 1][j] != -1) {
					if (costs[i][j] == -1)
						costs[i][j] = costs[i - 1][j];
					else
						costs[i][j] = min(costs[i][j], costs[i - 1][j]);
					get_subjects(j, S, psubjects);
					bool employ = false;
					for (int k = 0; k < S; k++)
						if (subjects[k] && psubjects[k] < 2) {
							employ = true;
							psubjects[k]++;
						}
					if (employ) {
						int k = get_index(S, psubjects);
						if (costs[i][k] == -1)
							costs[i][k] = costs[i - 1][j] + c;
						else
							costs[i][k] = min(costs[i][k], costs[i - 1][j] + c);
					}
				}
#ifdef DEBUG
			printf("%3d ", i);
			for (int j = 0; j < s; j++) {
				if (costs[i][j] != -1) {
					get_subjects(j, S, subjects);
					print_cost(S, subjects, costs[i][j]);
				}
			}
			putchar('\n');
#endif
		}
		cout << costs[n][s - 1] << endl;
	}
	return 0;
}

