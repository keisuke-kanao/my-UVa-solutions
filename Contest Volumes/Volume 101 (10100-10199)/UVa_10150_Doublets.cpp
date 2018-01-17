
/*
	3.8.7 Doublets
	PC/UVa IDs: 110307/10150, Popularity: C, Success rate: average Level: 3

	To build using Visucal Studio 2008:
		cl -EHsc -DONLINE_JUDGE UVa_10150_Doublets.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <queue>
#include <cstring>
using namespace std;

bool is_doublet(const string& s, const string& t)
{
#ifdef ONLINE_JUDGE
	if (s.length() != t.length())
		return false;
	for (int i = 0; i < s.length(); i++)
		if (s[i] != t[i])
			return !strcmp(s.c_str() + i + 1, t.c_str() + i + 1);
	return false;
#else
	int s_length = s.length(), t_length = t.length();
	for (int i = 0; i < s_length; i++) {
		if (i < t_length) {
			if (s[i] != t[i]) {
				const char* ps = s.c_str() + i, *pt = t.c_str() + i;
				return !strcmp(ps + 1, pt + 1) || !strcmp(ps + 1, pt) || !strcmp(ps, pt + 1);
			}
		}
		else
			return i == s_length - 1; // see if s differs in only its last character
	}
	return false;
#endif
}

enum vertex_state {initialized = -1, discovered, processed};

bool search_path(int initial, int target, const vector< vector<int> >& adjacency_list, vector<int>& paths)
{
	// do a breadth-first search
	vector<vertex_state> vs(adjacency_list.size(), initialized);
	if (initial == target)
		return true;
	queue<int> vq; // vertex queue
	vs[initial] = discovered;
	vq.push(initial);
	while (!vq.empty()) {
		int v = vq.front(); vq.pop();
		vs[v] = processed;
		for (int i = 0; i < adjacency_list[v].size(); i++) {
			int j = adjacency_list[v][i];
			if (vs[j] == initialized) {
				vs[j] = discovered;
				paths[j] = v;
				if (j == target)
					return true;
				else
					vq.push(j);
			}
		}
	}
	return false;
}

void print_path(const vector<string>& words, int target, const vector<int>& paths)
{
	int previous = paths[target];
	if (previous != -1)
		print_path(words, previous, paths);
	cout << words[target] << endl;
}

int main(int /* argc */, char** /* argv */)
{
	string line;
	map<string, int> word_indices; // key is a word, value is its index to the vector of words
	vector<string> words;
	for (int i = 0; ;  ) {
		getline(cin, line);
		if (line.empty())
			break;
		if (word_indices.find(line) == word_indices.end()) {
			word_indices.insert(make_pair(line, i));
			i++;
			words.push_back(line);
		}
	}
	int nr_words = words.size();
	vector< vector<int> > adjacency_list(nr_words);
	for (int i = 0; i < nr_words - 1; i++)
		for (int j = i + 1; j < nr_words; j++)
			if (is_doublet(words[i], words[j])) {
				adjacency_list[i].push_back(j); adjacency_list[j].push_back(i);
			}
	bool more_than_one_cases = false;
	while (getline(cin, line)) {
		istringstream iss(line);
		string s_initial, s_target;
		iss >> s_initial >> s_target;
		if (more_than_one_cases)
			cout << endl;
		int initial = -1, target = -1;
		map<string, int>::iterator i;
		if ((i = word_indices.find(s_initial)) != word_indices.end())
			initial = i->second;
		if ((i = word_indices.find(s_target)) != word_indices.end())
			target = i->second;
		bool solution_found = false;
		if (initial != -1 && target != -1) {
			vector<int> paths(nr_words, -1);
			if (solution_found = search_path(initial, target, adjacency_list, paths))
				print_path(words, target, paths);
		}
		if (!solution_found)
			cout << "No solution.\n";
		more_than_one_cases = true;
	}
	return 0;
}

