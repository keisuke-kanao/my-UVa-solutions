
/*
	UVa 122 - Trees on the level

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_122_Trees_on_the_level.cpp

	from Duke Internet Programming Contest 1993
		(http://contest.mff.cuni.cz/old/archive/duke1993/)
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
using namespace std;

const int nr_nodes_max = 16384;
int nodes[nr_nodes_max + 1];
bool visited_nodes[nr_nodes_max + 1];

void traverse_tree(int ni)
{
	if (nodes[ni] != -1) {
		visited_nodes[ni] = true;
		ni *= 2;
		if (ni <= nr_nodes_max)
			traverse_tree(ni);
		if (ni + 1 <= nr_nodes_max)
			traverse_tree(ni + 1);
	}
}

bool is_completed_tree(int ni_max)
{
	memset(visited_nodes, 0, sizeof(visited_nodes));
	traverse_tree(1);
	for (int i = 1; i <= ni_max; i++)
		if (nodes[i] != -1 && !visited_nodes[i])
			return false;
	return true;
}

int main()
{
	string s;
	while (cin >> s) {
		if (s == "()") {
			cout << "not complete\n";
			continue;
		}

		bool not_completed = false;
		int ni_max = 0;
		memset(nodes, -1, sizeof(nodes));
		do {
			int n;
			const char* ps = s.c_str();
			ps++;
			if (*ps == ',')
				not_completed = true;
			else {
				char* p;
				n = static_cast<int>(strtol(ps, &p, 0));
				int ni = 1;
				for (p++; *p != ')'; p++) {
					ni *= 2;
					if (*p == 'R')
						ni++;
				}
				if (nodes[ni] == -1) {
					nodes[ni] = n;
					if (ni > ni_max)
						ni_max = ni;
				}
				else
					not_completed = true;
			}
			cin >> s;
		} while (s != "()");
		if (!not_completed)
			not_completed = !is_completed_tree(ni_max);
		if (not_completed)
			cout << "not complete\n";
		else {
			bool printed = false;
			for (int i = 1; i <= ni_max; i++)
				if (nodes[i] != -1) {
					if (printed)
						cout << ' ';
					else
						printed = true;
					cout << nodes[i];
				}
			cout << endl;
		}
	}
	return 0;
}

