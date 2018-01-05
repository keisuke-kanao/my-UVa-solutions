
/*
	UVa 10746 - Crime Wave - The Sequel

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10746_Crime_Wave-The_Sequel.cpp
*/

#include<queue>
#include <limits>
#include<cstdio>
#include<cstring>
using namespace std;

const double infinite = numeric_limits<double>::max();
const double eps = 1.0e-8 /* numeric_limits<float>::epsilon() */;
const int n_max = 20, m_max = 20;
const int nr_vertices_max = n_max + m_max + 2, nr_edges_max = 2 * (n_max * m_max + n_max + m_max);

struct edge { // an edge to v_
	int v_;
	int next_;
	int capacity_;
	double cost_;
} edges[nr_edges_max];

int nr_edges = 0;
int next_vertices[nr_edges_max];
int flows[nr_vertices_max], prev_vertices[nr_vertices_max], prev_edges[nr_vertices_max];
double distances[nr_vertices_max];
bool in_queue[nr_vertices_max];

void add_edge(int u, int v, int capacity, double cost)
{
	edges[nr_edges].v_ = v, edges[nr_edges].capacity_ = capacity, edges[nr_edges].cost_ = cost,
		edges[nr_edges].next_ = next_vertices[u], next_vertices[u] = nr_edges++;
	edges[nr_edges].v_ = u, edges[nr_edges].capacity_ = 0, edges[nr_edges].cost_ = -cost,
		edges[nr_edges].next_ = next_vertices[v],  next_vertices[v] = nr_edges++;
}

void spfa(int nr_vertices, int flow, int start)
{
    queue<int> q;
	for (int i = 0; i < nr_vertices; i++)
		distances[i] = infinite;
    memset(in_queue, 0, sizeof(in_queue));
    memset(flows, 0, sizeof(flows));
    flows[start] = flow, distances[start] = 0.0;
	in_queue[start] = true;
    q.push(start);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		double w = distances[u];
        in_queue[u] = false;
        for (int i = next_vertices[u]; i != -1 ; i = edges[i].next_) {
			int v = edges[i].v_;
		    if (edges[i].capacity_ && distances[u] + edges[i].cost_ < distances[v]) {
		        flows[v] = min(flows[u], edges[i].capacity_);
	    	    distances[v] = distances[u] + edges[i].cost_;
	        	prev_vertices[v] = u, prev_edges[v] = i;
				if (!in_queue[v]) {
					in_queue[v] = true;
					q.push(v);
				}
			}
		}
	}
}

double min_cost_max_flow(int n, int m, int start, int end)
{
	int flow = n;
	double cost = 0.0;
	while (flow) {
		spfa(n + m + 2, flow, start);
		int f = flows[end];
		flow -= f, cost += f * distances[end];
		for (int u = end; u != start; u = prev_vertices[u])
			edges[prev_edges[u]].capacity_ -= f, edges[prev_edges[u] ^ 1].capacity_ += f;
	}
	return cost;
}

int main()
{
	while (true) {
		int n, m;
		scanf("%d %d", &n, &m);
		if (!n)
			break;
		nr_edges = 0;
		memset(next_vertices, -1, sizeof(next_vertices));
		int nr_vertices = n + m + 2;
		// vertices are:
		// 0: source, 1 - m: cruiser vertices, (m + 1) - (m + n): bank vertices, (m + n + 1): sink
		// append the edges between cruiser vertices and bank vertices
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++) {
				double cost;
				scanf("%lf", &cost);
				add_edge(j + 1, m + i + 1, 1, cost);
			}
		// append the edges between the source and cruiser vertices
		for (int i = 0; i < m; i++)
			add_edge(0, i + 1, 1, 0.0);
		// append the edges between bank vertices and the sink
		for (int i = 0; i < n; i++)
			add_edge(m + i + 1, m + n + 1, 1, 0.0);
		double cost = min_cost_max_flow(n, m, 0, n + m + 1);
		printf("%.2f\n", cost / n + eps);
	}
	return 0;
}

