
/*
	UVa 157 - Route Finding

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_157_Route_Finding.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <limits>
#include <cstdio>
using namespace std;

const int infinite = numeric_limits<int>::max();
const int nr_letters = 'z' - 'a' + 1, n_max = nr_letters * nr_letters;

struct edge {
	int v_;
	int w_;
	edge(int v, int w) : v_(v), w_(w) {}
};

vector<edge> edges[n_max];
bool visited[n_max];
int distances[n_max], parents[n_max];

struct distance_comparator {
	bool operator() (int i, int j) const
	{
		return (distances[i] != distances[j]) ? distances[i] < distances[j] : i < j;
	}
};

int dijkstra_shortest_path(int n, int start, int end)
{
	for (int i = 0; i < n; i++)
		visited[i] = false, distances[i] = infinite;
	set<int, distance_comparator> pq; // priority queue
	distances[start] = 0, parents[start] = -1;
	pq.insert(start);
	while(!pq.empty()) {
		int u = *pq.begin();
		pq.erase(pq.begin());
		visited[u] = true;
		if (u == end)
			break;
		int d = distances[u], pw = (u != start) ? d - distances[parents[u]] : -1;
		const vector<edge>& es = edges[u];
		for (size_t i = 0, j = es.size(); i < j; i++) {
			int v = es[i].v_, w = es[i].w_;
			if (w == 3 && (pw == 3 || pw == 0)) // pass through several connections
				w = 0;
			if (!visited[v] && distances[v] > d + w) {
				pq.erase(v); // remove v if it has already been in the queue
				distances[v] = d + w, parents[v] = u;
				pq.insert(v);
			}
		}
	}
	return distances[end];
}

map<pair<char, char>, int> vertices;
map< int, pair<char, char> > stations;

int get_vertex(char cr, char cs)
{
	pair<map<pair<char, char>, int>::iterator, bool> result = vertices.insert(make_pair(make_pair(cr, cs), static_cast<int>(vertices.size())));
	if (result.second)
		stations.insert(make_pair(result.first->second, make_pair(cr, cs)));
	return result.first->second;
}

void print_path(int u, int w, char& cr)
{
	pair<int, int> s = stations[u];
	if (parents[u] == -1) {
		cr = s.first;
		printf("%c%c", cr, s.second);
	}
	else {
		print_path(parents[u], distances[u] - distances[parents[u]], cr);
		if (w) {
			if (s.first != cr) {
				cr = s.first;
				printf("=%c%c", cr, s.second);
			}
			else
				putchar(s.second);
		}
	}
}

int main()
{
	string s;
	getline(cin, s);
	istringstream iss(s);
	int nr_routes;
	iss >> nr_routes;
	vertices.clear();
	while (nr_routes--) {
		getline(cin, s);
		const char* p = s.c_str();
		char cr = *p++;
		int u = get_vertex(cr, *++p), su = u, v;
		for (p++; *p; p++) {
			if (*p == '=') { // ...hc=Bg=Cc=Abd...
				int ccr = *++p;
				v = get_vertex(ccr, *++p);
				if (v != su)
					edges[u].push_back(edge(v, 3)), edges[v].push_back(edge(u, 3));
				else
					edges[u].push_back(edge(v, 1)), edges[v].push_back(edge(u, 1));
			}
			else {
				v = get_vertex(cr, *p);
				edges[u].push_back(edge(v, 1)), edges[v].push_back(edge(u, 1));
				u = v;
			}
		}
	}
	int n = static_cast<int>(vertices.size());
	while (getline(cin, s) && s[0] != '#') {
		int start = get_vertex(s[0], s[1]), end = get_vertex(s[2], s[3]);
		int d = dijkstra_shortest_path(n, start, end);
		printf("%3d: ", d);
		char cr;
		print_path(end, -1, cr);
		putchar('\n');
	}
	return 0;
}

/*

Sample input

4
A:fgmpnxzabjd=Dbf
D:b=Adac=Ccf
B:acd=Azefg=Cbh
C:bac
AgAa
AbBh
BhDf
#

Sample output

  5: Agfdjba
  9: Abaz=Bdefgh
 10: Bhg=Cbac=Dcf


1
A:fgmpnxzabjdf
AaAa
#

0: Aa


4
A:a=Ba=Ca
B:ab
C:ab
D:ab=Cb
AaCa
AaAa
AaCb
AaDb
BbCb
#

3: Aa=Ca 
0: Aa 
4: Aa=Cab 
7: Aa=Cab=Db 
5: Bba=Cab


5
A:ab=Bbcdefghijk
B:abc=Ajdef=Cb
C:ab
D:cd=Eg
E:fg=Bf
AaAk
AcAk
AbBb
BaDd
#

  9: Aab=Bbc=Ajk
  8: Acdefghijk
  3: Ab=Bb
  8: Babcdef=Dd


3
A:a=Cabcdefg=Bb
B:a=Cbb=Ag
C:a=Aab=Ca
BbAa
#

  8: Bba=Cba=Aa

*/

