
/*
	UVa 10804 - Gopher Strategy

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10804_Gopher_Strategy.cpp
*/

#include <algorithm>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;

const int m_max = 50, n_max = 50;

pair<double, double> gophers[m_max], holes[n_max];
double distances[m_max][n_max], unique_distances[m_max * n_max];

double euclidean_distance(const pair<double, double>& p, const pair<double, double>& q)
{
	double dx = p.first - q.first, dy = p.second - q.second;
	return sqrt(dx * dx + dy * dy);
}

struct edge {
	int v_; // neighboring vertex
	int capacity_; // capacity of edge
	int flow_; // flow through edge
	int residual_; // residual capacity of edge

	edge(int v, int capacity, int residual) : v_(v), capacity_(capacity), flow_(0), residual_(residual) {}
};

struct vertex_state {
	bool discovered_;
	int parent_;

	vertex_state() : discovered_(false), parent_(-1) {}
};

void bfs(const vector< vector<edge> >& graph, int start, vector<vertex_state>& states)
{
	queue<int> q;
	states[start].discovered_ = true;
	q.push(start);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int i = 0; i < graph[u].size(); i++) {
			const edge& e = graph[u][i];
			if (e.residual_ > 0 && !states[e.v_].discovered_) {
				states[e.v_].discovered_ = true;
				states[e.v_].parent_ = u;
				q.push(e.v_);
			}
		}
	}
}

edge& find_edge(vector< vector<edge> >& graph, int u, int v)
{
	int i;
	for (i = 0; i < graph[u].size(); i++)
		if (graph[u][i].v_ == v)
			break;
	return graph[u][i];
}

int path_volume(vector< vector<edge> >& graph, int start, int end, const vector<vertex_state>& states)
{
	if (states[end].parent_ == -1)
		return 0;
	edge& e = find_edge(graph, states[end].parent_, end);
	if (start == states[end].parent_)
		return e.residual_;
	else
		return min(path_volume(graph, start, states[end].parent_, states), e.residual_);
}

void augment_path(vector< vector<edge> >& graph, int start, int end, const vector<vertex_state>& states, int volume)
{
	if (start == end)
		return;
	edge& e = find_edge(graph, states[end].parent_, end);
	if (e.flow_ < e.capacity_)
		e.flow_ += volume;
	if (e.residual_)
		e.residual_ -= volume;
	edge& r= find_edge(graph, end, states[end].parent_);
	if (r.flow_)
		r.flow_ -= volume;
	if (r.residual_ < r.capacity_)
		r.residual_ += volume;
	augment_path(graph, start, states[end].parent_, states, volume);
}

void netflow(vector< vector<edge> >& graph, int source, int sink)
{
	while (true) {
		vector<vertex_state> states(graph.size());
		bfs(graph, source, states);
		int volume = path_volume(graph, source, sink, states); // calculate the volume of augmenting path
		if (volume > 0)
			augment_path(graph, source, sink, states, volume);
		else
			break;
	}
}

int total_flow(const vector< vector<edge> >& graph, int source)
{
	int flow = 0;
	const vector<edge>& edges = graph[source];
	for (int i = 0, e = edges.size(); i < e; i++)
		flow += edges[i].flow_;
	return flow;
}

int get_gophers(vector< vector<edge> >& graph, int nr_gophers, int nr_holes, int source, int sink, double d)
{
	vector<edge>& gs =graph[source];
	for (int i = 0; i < nr_gophers; i++) {
		gs[i].capacity_ = gs[i].residual_ = 1, gs[i].flow_ = 0;
		vector<edge>& gg = graph[i];
		for (size_t j = 0; j < gg.size(); j++) {
			if (gg[j].v_ == source)
				gg[j].capacity_ = 1, gg[j].residual_ = gg[j].flow_ = 0;
			else {
				if (distances[i][gg[j].v_ - nr_gophers] <= d)
					gg[j].capacity_ = gg[j].residual_ = 1, gg[j].flow_ = 0;
				else
					gg[j].capacity_ = gg[j].residual_ = gg[j].flow_ = 0;
			}
		}
	}
	for (int i = nr_gophers; i < nr_gophers + nr_holes; i++) {
		vector<edge>& gh = graph[i];
		for (size_t j = 0; j < gh.size(); j++) {
			if (gh[j].v_ == sink)
				gh[j].capacity_ = gh[j].residual_ = 1, gh[j].flow_ = 0;
			else {
				if (distances[gh[j].v_][i - nr_gophers] <= d)
					gh[j].capacity_ = 1, gh[j].residual_ = gh[j].flow_ = 0;
				else
					gh[j].capacity_ = gh[j].residual_ = gh[j].flow_ = 0;
			}
		}
	}
	vector<edge>& gt = graph[sink];
	for (int i = 0; i < nr_holes; i++)
		gt[i].capacity_ = 1, gt[i].residual_ = gt[i].flow_ = 0;
	netflow(graph, source, sink); // apply Ford-Fulkerson's augmenting path algorithm
	int flow = total_flow(graph, source);
#ifdef DEBUG
	printf("%lf %d\n", d, flow);
#endif
	return flow;
}

int main()
{
	int N;
	scanf("%d", &N);
	for (int cn = 1; cn <= N; cn++) {
		int m, n, k;
		scanf("%d %d %d", &m, &n, &k);
		for (int i = 0; i < m; i++)
			scanf("%lf %lf", &gophers[i].first, &gophers[i].second);
		for (int i = 0; i < n; i++)
			scanf("%lf %lf", &holes[i].first, &holes[i].second);
		if (!m || m == k) {
			printf("Case #%d:\n%.3lf\n\n", cn, 0.0);
			continue;
		}
		if (n < m - k) {
			printf("Case #%d:\nToo bad.\n\n", cn);
			continue;
		}
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				distances[i][j] = unique_distances[i * m + j] = euclidean_distance(gophers[i], holes[j]);
		int nr_unique_distances = m * n;
		sort(unique_distances, unique_distances + nr_unique_distances);
		nr_unique_distances = unique(unique_distances, unique_distances + nr_unique_distances) - unique_distances;
		int nr_vertices = m + n + 2, source = m + n, sink = m + n + 1;
		// indices are:
		//	0 - (m - 1): gopher vertices, m - (m + n - 1): hole vertices,
		//	(m + n): source vertex, (m + n + 1): sink vertex
		vector< vector<edge> > graph(nr_vertices);
		for (int i = 0; i < m; i++) {
			// append the edges between the source and gopher vertices
			graph[source].push_back(edge(i, 0, 0));
			graph[i].push_back(edge(source, 0, 0));
			for (int j = 0; j < n; j++) {
				// append the edges between gopher vertices and hole vertices
				graph[i].push_back(edge(m + j, 0, 0));
				graph[m + j].push_back(edge(i, 0, 0));
			}
		}
		for (int i = m; i < m + n; i++) {
			// append the edges between hole vertices and the sink
			graph[i].push_back(edge(sink, 1, 1));
			graph[sink].push_back(edge(i, 1, 0));
		}
		int min_di = 0;
		for (int low = 0, high = nr_unique_distances; low < high; ) {
			int mid = (low + high) / 2;
			int result = get_gophers(graph, m, n, source, sink, unique_distances[mid]) - (m - k);
			if (result < 0)
				low = mid + 1;
			else
				min_di = high = mid;
		}
		printf("Case #%d:\n%.3lf\n\n", cn, unique_distances[min_di]);
	}
	return 0;
}

