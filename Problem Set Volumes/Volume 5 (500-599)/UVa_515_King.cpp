
/*
	UVa 515 - King

	To build using Visucal Studio 2008:
		cl -EHsc UVa_515_King.cpp

	from ACM Central European Regionals 1997
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_EU_CERC/1997/index.html)
*/

#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

/*
from UVa 515 - Algorithmist:
	(http://www.algorithmist.com/index.php/UVa_515)

First of all, simplify the constraints.
Consider a function S(k) = ƒ°x(i) (i = 1 to k), S(0) = 0.
With this function, the constraints can be rewritten as: [S(s(i) + n(i)) - S(s(i) - 1)]R(i)k(i).

Furthermore, it's clear that the sequence (x(1), x(2), ..., x(n)) exists 
if and only if a sequence of integers (S(1), S(2), ..., S(n)), satisfying the constraints in the above form exists.

The next step is to get rid of the strict inequalities. A contraint a < b is equivalent to a <= b - 1 in integers.
Similarly, a > b is the same thing as , a >= b + 1 or alternatively -a <= -b - 1.

We are left with a system of equations of the form: S(a(i)) - S(b(i)) <= c(i)
 where all a(i), b(i), c(i) are integers, and 0 <= a(i), b(i) <= n.

A system like this one is known as a system of difference constraints. 
In order to solve it, first construct a constraint graph, 
  whose vertices are labelled with numbers from 0 to n, 
  and each constraint corresponds to an edge from vertex b(i) to vertex a(i) of weight c(i). 
Also, the graph has a special vertex s, and edges of weight 0 from s to every other vertex.

It is known that a system of difference constrains has a solution in integers, 
if and only if the corresponding constraint graph has no negative cycles, and all c(i) are integers.
*/

struct edge {
	int u_; // source vertex
	int v_; // destination vertex
	int weight_;

	edge() : u_(-1), v_(-1), weight_(-1) {}
	edge(int u, int v, int weight) : u_(u), v_(v), weight_(weight) {}
};

bool bellman_ford(int n, int source, const vector<edge>& edges)
{
	// initialize the graph
	vector<int> distances(n, numeric_limits<int>::max());
	distances[source] = 0;
	// relax the edges repeatedly
	for (int i = 0; i < n - 1; i++)
		for (size_t j = 0, je = edges.size(); j < je; j++) {
			const edge& e = edges[j];
			if (distances[e.u_] + e.weight_ < distances[e.v_])
				distances[e.v_] = distances[e.u_] + e.weight_;
		}
	// check for negative-weight cycles
	for (size_t i = 0, ie = edges.size(); i < ie; i++) {
		const edge& e = edges[i];
		if (distances[e.u_] + e.weight_ < distances[e.v_])
			return true; // the graph contains a negative-weight cycle
	}
	return false;
}

int main()
{
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		int m;
		cin >> m;
		vector<edge> edges(n + m + 1);
		int i;
		for (i = 0; i < n + 1; i++)
			edges[i] = edge(n + 1, i, 0); // edges from specical vertex (n + 1) to any other vertex
		for ( ; i < n + m + 1; i++) {
			int j, k, c;
			string op;
			cin >> j >> k >> op >> c;
			k += j; j--;
			if (op == "gt") {
				swap(j, k);
				c++; c = -c;
			}
			else
				c--;
			edges[i] = edge(j, k, c);
		}
		// Bellman-Ford's shortest path algorithm should start from the special vertex (n + 1)
		cout << ((bellman_ford(n + 2, n + 1, edges)) ? "successful conspiracy\n" : "lamentable kingdom\n");
	}
	return 0;
}

