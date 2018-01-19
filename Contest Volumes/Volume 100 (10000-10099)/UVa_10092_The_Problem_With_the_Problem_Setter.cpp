
/*
	10.5.8 The Problem With the Problem Setter
	PC/UVa IDs: 111008/10092, Popularity: C, Success rate: average Level: 3

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10092_The_Problem_With_the_Problem_Setter.cpp
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
#ifndef ONLINE_JUDGE
#include <cassert>
#endif
using namespace std;

struct edge {
	int w; // neighboring vertex
	int weight;
	edge(int _w, int _weight) : w(_w), weight(_weight) {}
};

void append_pair_of_edges(vector< vector<edge> >& graph, int v, int w, int weight)
{
	graph[v].push_back(edge(w, weight));
	graph[w].push_back(edge(v, 0));
}

inline bool is_active_vertex(int v, int s, int t, const vector<int>& excesses)
{
	return v != s && v != t && excesses[v] > 0;
}

inline int get_residual_capacity(const vector< vector<int> >& capacities, const vector< vector<int> >& flows, int v, int w)
{
	return capacities[v][w] - flows[v][w];
}

void push_flow(const vector< vector<int> >& capacities, vector< vector<int> >& flows, vector<int>& excesses,
	int v, int w)
{
	int flow = min(excesses[v], get_residual_capacity(capacities, flows, v, w));
	flows[v][w] += flow; excesses[w] += flow;
	flows[w][v] -= flow; excesses[v] -= flow;
}

int push_relabel_ll(const vector< vector<edge> >& graph, vector< vector<int> >& flows, int s, int t)
// push-relabel with largest label maximum flow algorithm in O(V^2 * sqrt(E)) (Goldberg and Tarjan)
{
	int n = graph.size(); // number of vertices
	vector< vector<int> > capacities(n, vector<int>(n, 0)); // capacities[u][v] is capacity of edge[u][v]
	vector<int> excesses(n, 0);
	vector<int> distance_labelings(n, 0);
	vector< queue<int> > B(n * 2); // B[i] is the set of active vertices with label i
	int b = 0; // index to B[i] where B[b] has the largest label
/*
	During the initialization, when the arcs going out of the source are saturated 
	(i.e., arg (v, w) such that uf(v, w) = 0), the resulting active vertices are placed in B[0], and b is set to 0.
*/
	for (int v = 0; v < n; v++) // set capacities
		for (vector<edge>::const_iterator e = graph[v].begin(); e != graph[v].end(); e++)
			capacities[v][e->w] += e->weight;
	for (vector<edge>::const_iterator e = graph[s].begin(); e != graph[s].end(); e++) { // set initial preflow and excess
		int w = e->w, c = capacities[s][w];
		flows[s][w] = c; flows[w][s] = -c;
		excesses[w] = c; excesses[s] += -c;
		B[0].push(w);
	}
	distance_labelings[s] = n;
	while (b >= 0) {
		if (B[b].empty()) {
			b--;
			continue;
		}
		int v = B[b].front(); B[b].pop();
		int old_label = distance_labelings[v];

		// discharge(v)
		if (is_active_vertex(v, s, t, excesses)) {
			vector<edge>::const_iterator e = graph[v].begin();
			do {
				int w = e->w; // {v, w} is the current edge of v
				if (get_residual_capacity(capacities, flows, v, w) > 0 && 
					distance_labelings[v] == distance_labelings[w] + 1) { // (v, w) is admissible
					push_flow(capacities, flows, excesses, v, w); // push(v, w)
					if (is_active_vertex(w, s, t, excesses))
						B[distance_labelings[w]].push(w); // add each vertex w made active by the discharge to B[d(w)]
				}
				else
					e++;
			} while (excesses[v] > 0 && e != graph[v].end());
			// note that discharge(v) either relabels v or gets rid of all excess at v, but not both
			if (excesses[v] > 0) {
				// relabel(v)
				int d = INT_MAX - 1;
				for (vector<edge>::const_iterator e = graph[v].begin(); e != graph[v].end(); e++) {
					int w = e->w;
					if (get_residual_capacity(capacities, flows, v, w) > 0)
						d = min(d, distance_labelings[w]);
				}
				distance_labelings[v] = d + 1;
			}
			// discharge(v) stops when the excess at v is reduced to zero or v is relabeled
		}

		if (old_label != distance_labelings[v]) { // discharge(v) relabeled v
			// v is the active vertex with the largest distance label
			b = distance_labelings[v];
			B[b].push(v);
		}
/*
		else { // discharge(v) got rid of all excess at v (i.e., ef(v) = 0)
			// the excess at v has been moved to vertices with distance labels of b - 1
			if (B[b].empty())
				b--;
		}
*/
	}
	return excesses[t];
}

int main(int /* argc */, char** /* argv */)
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	while (true) {
		int nr_categories, nr_problems;
		cin >> nr_categories >> nr_problems;
		if (!nr_categories && !nr_problems)
			break;
		int nr_vertices = nr_categories + nr_problems + 2;
		vector< vector<edge> > graph(nr_vertices);
		// indices are:
		//	0 - (nr_categories - 1): category vertices, nr_categories - (nr_categories + nr_problems - 1): problem vertices,
		//	(nr_categories + nr_problems): source vertex, (nr_categories + nr_problems + 1): sink vertex
		int source = nr_categories + nr_problems, sink = nr_categories + nr_problems + 1;
		int sum_of_problems = 0;
#ifndef ONLINE_JUDGE
		vector<int> problems(nr_categories); // problems[i] is the number of problems to be included in category i
		vector<int> categories(nr_problems); // categories[i] is the number of categories in which problem i can be included
#endif
		for (int i = 0; i < nr_categories; i++) {
			int capacity;
			cin >> capacity;
#ifndef ONLINE_JUDGE
			problems[i] = capacity;
#endif
			sum_of_problems += capacity;
			// append the edges between the source vertex and the category vertex
			append_pair_of_edges(graph, source, i, capacity);
		}
		for (int i = nr_categories; i < nr_categories + nr_problems; i++) {
			int nc;
			cin >> nc;
			for (int j = 0; j < nc; j++) { // append the edges between the category vertices and the problem vertex
				int k;
				cin >> k;
				append_pair_of_edges(graph, k - 1, i, 1);
			}
#ifndef ONLINE_JUDGE
			categories[i - nr_categories] = nc;
#endif
			// append the edges between the problem vertex and the sink vertex
			append_pair_of_edges(graph, i, sink, 1);
		}
		vector< vector<int> > flows(nr_vertices, vector<int>(nr_vertices, 0)); // flows[v][w] is flow from v to w
		if (push_relabel_ll(graph, flows, source, sink) == sum_of_problems) {
			cout << 1 << endl;
			for (int i = 0; i < nr_categories; i++) {
				bool printed = false;
				for (int j = nr_categories; j < nr_categories + nr_problems; j++)
					if (flows[i][j]) {
						if (printed)
							cout << ' ';
						printed = true;
						cout << j - nr_categories + 1;
#ifndef ONLINE_JUDGE
						assert(problems[i]-- > 0);
						assert(categories[j - nr_categories]-- > 0);
#endif
					}
				cout << endl;
#ifndef ONLINE_JUDGE
				assert(problems[i] == 0);
#endif
			}
		}
			else
			cout << 0 << endl;
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}

