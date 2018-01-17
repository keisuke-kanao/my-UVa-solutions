
/*
	2.8.6 Erdos Numbers
	PC/UVa IDs: 110206/10044, Popularity: B, Success rate: low Level: 2

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10044_Erdos_Numbers.cpp
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
using namespace std;

const string erdos_p = "Erdos, P.";

string trim_string(const char* p, const char* q)
{
	while (p < q && *p == ' ')
		p++;
	while (p < q && *q == ' ')
		q--;
	return string(p, q - p + 1);
}

void extract_authors(const char* s, vector<string>& authors)
{
	string author;
	for (const char *p = s, *last_name = s, *initials = NULL; ; p++)
		if (*p == ',' || *p == ':' || *p == '\0') {
			bool author_extracted = initials || *p == ':' || *p == '\0';
			if (initials) {
				author += ", "; author += trim_string(initials, p - 1);
				last_name = p + 1; initials = NULL;
			}
			else {
				author = trim_string(last_name, p - 1);
				last_name = NULL; initials = p + 1;
			}
			if (author_extracted) {
				if (!author.empty())
					authors.push_back(author);
				author.clear();
			}
			if (*p == ':' || *p == '\0')
				break;
		}
}

#ifdef DEBUG
void print_authors(const set<string>& authors)
{
	for (set<string>::const_iterator i = authors.begin(); i != authors.end(); i++)
		cout << *i << endl;
}
#endif

string get_name(const char* s)
{
	string name;
	for (const char *p = s, *last_name = s, *initials = NULL; ; p++)
		if (*p == ',' || *p == '\0') {
			if (initials) {
				name += ", "; name += trim_string(initials, p - 1);
			}
			else {
				name = trim_string(last_name, p - 1);
				last_name = NULL; initials = p + 1;
			}
			if (*p == '\0')
				break;
		}
	return name;
}

void register_authors(const vector<string>& authors, map<string, int>& author_indices, vector<int>& indices)
{
	for (vector<string>::const_iterator i = authors.begin(); i != authors.end(); i++) {
		map<string, int>::const_iterator j = author_indices.find(*i);
		int index;
		if (j == author_indices.end()) { // not registered yet
			index = author_indices.size(); // assign an index
			author_indices.insert(make_pair(*i, index));
		}
		else
			index = j->second;
		indices.push_back(index);
	}
}

void construct_adjacency_list(const vector< vector<int> >& coauthor_indices, vector< vector<int> >& adjacency_list)
{
	for (int i = 0; i < coauthor_indices.size(); i++) {
		const vector<int>& indices = coauthor_indices[i];
		for (int j = 0; j < indices.size() - 1; j++)
			for (int k = j + 1;  k < indices.size(); k++) {
				int indices_j = indices[j], indices_k = indices[k];
				adjacency_list[indices_j].push_back(indices_k);
				adjacency_list[indices_k].push_back(indices_j);
					// Note that each adjacency list for an author index may have duplicated author indices.
			}
	}
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

int get_path_length(int target, const vector<int>& paths)
{
	int length = 0;
	for (int previous_state = paths[target]; previous_state != -1; previous_state = paths[previous_state], length++)
		;
	return length;
}

int main(int /* argc */, char** /* argv */)
{
	// read the line containig the number of scenarios
	int scenarios;
	if (!(cin >> scenarios))
		return 0;
	for (int s = 0; s < scenarios; s++) {
		string line;
		// read a line containing P and N
		int p, n;
		cin >> p >> n;
		getline(cin, line); // read and discard the rest of the line
		map<string, int> author_indices; // key is author name, value is index to the adjacency list
		author_indices.insert(make_pair(erdos_p, 0));
		vector< vector<int> > coauthor_indices;
		for (int i = 0; i < p; i++) {
			// read a paper database line and extract the authors
			getline(cin, line);
			vector<string> authors;
			extract_authors(line.c_str(), authors);
#ifdef DEBUG
			print_authors(authors);
#endif
			vector<int> indices;
			// convert the vector of authors to the vector of author indices
			register_authors(authors, author_indices, indices);
			coauthor_indices.push_back(indices);
		}
		// construct the adjacency list
		int nr_authors = author_indices.size();
		vector< vector<int> > adjacency_list(nr_authors);
		construct_adjacency_list(coauthor_indices, adjacency_list);
		vector<string> names; // set of names
		for (int i = 0; i < n; i++) { // read the names whose Erdos number should be searched
			getline(cin, line);
			names.push_back(get_name(line.c_str()));
		}
		cout << "Scenario " << s + 1 << endl;
		for (vector<string>::const_iterator i = names.begin(); i != names.end(); i++) {
			int erdos_n = -1;
			map<string, int>::const_iterator j = author_indices.find(*i);
			if (j != author_indices.end()) {
				vector<int> paths(nr_authors, -1);
				if (search_path(j->second, 0, adjacency_list, paths))
					erdos_n = get_path_length(0, paths);
			}
			cout << *i;
			if (erdos_n != -1)
				cout << ' ' << erdos_n << endl;
			else
				cout << " infinity\n";
		}
	}
	return 0;
}

