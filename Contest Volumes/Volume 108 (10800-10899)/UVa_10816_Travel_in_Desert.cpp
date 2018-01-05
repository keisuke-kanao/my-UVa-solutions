
/*
	UVa 10816 - Travel in Desert

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10816_Travel_in_Desert.cpp
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>
#include <cstdlib>
using namespace std;

/*
 * Copyright 2010 Volkan Yazici <volkan.yazici@gmail.com>
 * Copyright 2006-2010 The Apache Software Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 */

#ifdef  __cplusplus
extern "C" {
#endif

/** priority data type */
typedef double pqueue_pri_t;

/** callback functions to get/set/compare the priority of an element */
typedef pqueue_pri_t (*pqueue_get_pri_f)(void *a);
typedef void (*pqueue_set_pri_f)(void *a, pqueue_pri_t pri);
typedef int (*pqueue_cmp_pri_f)(pqueue_pri_t next, pqueue_pri_t curr);

/** callback functions to get/set the position of an element */
typedef size_t (*pqueue_get_pos_f)(void *a);
typedef void (*pqueue_set_pos_f)(void *a, size_t pos);

/** debug callback function to print a entry */
typedef void (*pqueue_print_entry_f)(FILE *out, void *a);

/** the priority queue handle */
typedef struct pqueue_t
{
    size_t size;
    size_t avail;
    size_t step;
    pqueue_cmp_pri_f cmppri;
    pqueue_get_pri_f getpri;
    pqueue_set_pri_f setpri;
    pqueue_get_pos_f getpos;
    pqueue_set_pos_f setpos;
    void **d;
} pqueue_t;

#define left(i)   ((i) << 1)
#define right(i)  (((i) << 1) + 1)
#define parent(i) ((i) >> 1)

pqueue_t *
pqueue_init(size_t n,
            pqueue_cmp_pri_f cmppri,
            pqueue_get_pri_f getpri,
            pqueue_set_pri_f setpri,
            pqueue_get_pos_f getpos,
            pqueue_set_pos_f setpos)
{
    pqueue_t *q;

    if (!(q = (pqueue_t *)malloc(sizeof(pqueue_t))))
        return NULL;

    /* Need to allocate n+1 elements since element 0 isn't used. */
    if (!(q->d = (void **)(malloc((n + 1) * sizeof(void *))))) {
        free(q);
        return NULL;
    }

    q->size = 1;
    q->avail = q->step = (n+1);  /* see comment above about n+1 */
    q->cmppri = cmppri;
    q->setpri = setpri;
    q->getpri = getpri;
    q->getpos = getpos;
    q->setpos = setpos;

    return q;
}

void
pqueue_free(pqueue_t *q)
{
    free(q->d);
    free(q);
}

size_t
pqueue_size(pqueue_t *q)
{
    /* queue element 0 exists but doesn't count since it isn't used. */
    return (q->size - 1);
}

static void
bubble_up(pqueue_t *q, size_t i)
{
    size_t parent_node;
    void *moving_node = q->d[i];
    pqueue_pri_t moving_pri = q->getpri(moving_node);

    for (parent_node = parent(i);
         ((i > 1) && q->cmppri(q->getpri(q->d[parent_node]), moving_pri));
         i = parent_node, parent_node = parent(i))
    {
        q->d[i] = q->d[parent_node];
        q->setpos(q->d[i], i);
    }

    q->d[i] = moving_node;
    q->setpos(moving_node, i);
}

static size_t
maxchild(pqueue_t *q, size_t i)
{
    size_t child_node = left(i);

    if (child_node >= q->size)
        return 0;

    if ((child_node+1) < q->size &&
        q->cmppri(q->getpri(q->d[child_node]), q->getpri(q->d[child_node+1])))
        child_node++; /* use right child instead of left */

    return child_node;
}

static void
percolate_down(pqueue_t *q, size_t i)
{
    size_t child_node;
    void *moving_node = q->d[i];
    pqueue_pri_t moving_pri = q->getpri(moving_node);

    while ((child_node = maxchild(q, i)) &&
           q->cmppri(moving_pri, q->getpri(q->d[child_node])))
    {
        q->d[i] = q->d[child_node];
        q->setpos(q->d[i], i);
        i = child_node;
    }

    q->d[i] = moving_node;
    q->setpos(moving_node, i);
}

int
pqueue_insert(pqueue_t *q, void *d)
{
    void *tmp;
    size_t i;
    size_t newsize;

    if (!q) return 1;

    /* allocate more memory if necessary */
    if (q->size >= q->avail) {
        newsize = q->size + q->step;
        if (!(tmp = realloc(q->d, sizeof(void *) * newsize)))
            return 1;
        q->d = (void **)tmp;
        q->avail = newsize;
    }

    /* insert item */
    i = q->size++;
    q->d[i] = d;
    bubble_up(q, i);

    return 0;
}

void
pqueue_change_priority(pqueue_t *q,
                       pqueue_pri_t new_pri,
                       void *d)
{
    size_t posn;
    pqueue_pri_t old_pri = q->getpri(d);

    q->setpri(d, new_pri);
    posn = q->getpos(d);
    if (q->cmppri(old_pri, new_pri))
        bubble_up(q, posn);
    else
        percolate_down(q, posn);
}

void *
pqueue_pop(pqueue_t *q)
{
    void *head;

    if (!q || q->size == 1)
        return NULL;

    head = q->d[1];
    q->d[1] = q->d[--q->size];
    percolate_down(q, 1);

    return head;
}

#ifdef  __cplusplus
}
#endif

const int n_max = 100, e_max = 10000;

struct edge {
	int v_; // destination vertex
	double d_; // length
	double r_; // temparature

	edge() {}
	edge(int v, double d, double r) : v_(v), d_(d), r_(r) {}
};

bool bfs(int n, int s, int t, double r_max, const vector< vector<edge> >& edges, vector<bool>& visited)
{
	for (int i = 0; i < n; i++)
		visited[i] = false;
	queue<int> q;
	visited[s] = true;
	q.push(s);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		if (u == t)
			return true;
		const vector<edge>& e = edges[u];
		for (size_t i = 0, j = e.size(); i < j; i++) {
			int v = e[i].v_;
			if (!visited[v] && e[i].r_ <= r_max) {
				visited[v] = true;
				q.push(v);
			}
		}
	}
	return false;
}

struct vertex_distance
{
	int v; // vertex
	double distance; // distance
	size_t pqueue_pos; // used internally by libpqueue

	vertex_distance() : v(-1), distance(-1), pqueue_pos(-1) {}
	vertex_distance(int _v, int _distance) : v(_v), distance(_distance), pqueue_pos(-1) {}

	static double get_distance(void* vd);
	static void set_distance(void* vd, double d);
	static int compare_distance(double next, double current);
	static size_t get_position(void* vd);
	static void set_position(void *vd, size_t position);
};

double vertex_distance::get_distance(void* vd)
{
	return reinterpret_cast<vertex_distance*>(vd)->distance;
}

void vertex_distance::set_distance(void* vd, double d)
{
	reinterpret_cast<vertex_distance*>(vd)->distance = d;
}

int vertex_distance::compare_distance(double next, double current)
{
	return current < next;
}

size_t vertex_distance::get_position(void* vd)
{
	return reinterpret_cast<vertex_distance*>(vd)->pqueue_pos;
}

void vertex_distance::set_position(void *vd, size_t position)
{
	reinterpret_cast<vertex_distance*>(vd)->pqueue_pos = position;
}

double shortest_path(int n, int s, int t, double r_max,
	const vector< vector<edge> >& edges, vector<vertex_distance>& distances, vector<int>& parent_vertices)
{
	for (int i = 0; i < n; i++)
		distances[i] = vertex_distance(i, ((i != s) ? numeric_limits<int>::max() : 0.0));
	parent_vertices[s] = -1;
	// queue items (vertex_distance instances) are arranged in ascending order of their distances from the start vertex
	pqueue_t* queue = pqueue_init(distances.size(),
		vertex_distance::compare_distance, vertex_distance::get_distance, vertex_distance::set_distance,
		vertex_distance::get_position, vertex_distance::set_position);
	for (int i = 0; i < n; i++)
		pqueue_insert(queue, &distances[i]);
	bool successful = false;
	double d;
	while (pqueue_size(queue)) {
		vertex_distance* vd = reinterpret_cast<vertex_distance*>(pqueue_pop(queue));
		vd->pqueue_pos = -1;
		int u = vd->v;
		d = distances[u].distance;
		if (u == t)
			break;
		if (d == numeric_limits<int>::max())
			break;
		for (size_t i = 0; i < edges[u].size(); i++) {
			const edge& e = edges[u][i];
			if (distances[e.v_].pqueue_pos != -1 // an vertex_distance instance for t.route is still in queue
				&& e.r_ <= r_max
				&& d + e.d_ < distances[e.v_].distance) {
				parent_vertices[e.v_] = u;
				pqueue_change_priority(queue, d + e.d_, &distances[e.v_]);
			}
		}
	}
	return d;
}

void print_path(int e, const vector<int>& parent_vertices)
{
	if (parent_vertices[e] != -1) {
		print_path(parent_vertices[e], parent_vertices);
		cout << ' ';
	}
	cout << e;
}

int main()
{
	int n, e;
	while (cin >> n >> e) {
		vector< vector<edge> > edges(n + 1);
		vector<bool> visited(n + 1);
		vector<double> temparatures(e);
		int s, t;
		cin >> s >> t;
		for (int i = 0; i < e; i++) {
			int x, y;
			double r, d;
			cin >> x >> y >> r >> d;
			edges[x].push_back(edge(y, d, r));
			edges[y].push_back(edge(x, d, r));
			temparatures[i] = r;
		}
		sort(temparatures.begin(), temparatures.end());
		vector<vertex_distance> distances(n + 1);
		vector<int> parent_vertices(n + 1);
		double d, r;
		for (int i = 0; i < e; i++) {
			if (i && temparatures[i - 1] == temparatures[i])
				continue;
			r = temparatures[i];
			if (bfs(n + 1, s, t, r, edges, visited)) {
				// apply Dijkstra's shortest path algorithm
				d = shortest_path(n + 1, s, t, r, edges, distances, parent_vertices);
				break;
			}
		}
		print_path(t, parent_vertices);
		cout << endl;
		cout << fixed << setprecision(1) << d << ' ' << r << endl;
	}
	return 0;
}

