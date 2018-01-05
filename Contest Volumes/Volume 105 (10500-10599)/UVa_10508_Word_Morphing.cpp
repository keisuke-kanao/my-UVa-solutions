
/*
	UVa 10508 - Word Morphing

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10508_Word_Morphing.cpp
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool is_adjacent_words(const string& s, const string& t, int length)
{
	int nr_diffs = 0;
	for (int i = 0; i < length; i++)
		if (s[i] != t[i])
			nr_diffs++;
	return nr_diffs == 1;
}

bool hamiltonian_path(int i, int n, int gi, const vector< vector<int> >& graph, vector<bool>& visited, vector<int>& parents)
{
	if (i == n)
		return (gi == n - 1) ? true : false;
	else {
		const vector<int>& g = graph[gi];
		for (int j = 0, je = g.size(); j < je; j++) {
			int k = g[j];
			if (!visited[k]) {
				visited[k] = true; parents[k] = gi;
				if (hamiltonian_path(i + 1, n, k, graph, visited, parents))
					return true;
				visited[k] = false;
			}
		}
		return false;
	}
}

void print_words(int i, const vector<int>& parents, const vector<string>& words)
{
	if (parents[i] != -1)
		print_words(parents[i], parents, words);
	cout << words[i] << endl;
}

int main()
{
	int nr_words, nr_letters;
	while (cin >> nr_words >> nr_letters) {
		vector<string> words(nr_words);
		cin >> words[0] >> words[nr_words - 1];
		for (int i = 1; i < nr_words - 1; i++)
			cin >> words[i];
		vector< vector<int> > graph(nr_words);
			// source vertex is 0, destination vertex is (nr_words - 1)
		for (int i = 0; i < nr_words - 1; i++)
			for (int j = i + 1; j < nr_words; j++)
				if (is_adjacent_words(words[i], words[j], nr_letters)) {
					graph[i].push_back(j);
					if (i && j < nr_words - 1)
						graph[j].push_back(i);
				}
		vector<bool> visited(nr_words, false);
		visited[0] = true;
		vector<int> parents(nr_words, -1);
		hamiltonian_path(0, nr_letters + 1, 0, graph, visited, parents);
		print_words(nr_words - 1, parents, words);
	}
	return 0;
}

