
/*
	10.5.1 Freckles
	PC/UVa IDs: 111001/10034, Popularity: B, Success rate: average Level: 2

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10034_Freckles.cpp
*/

/*
	Generate an undirected graph where vertices are freckles and each edge is assigned a weight 
	that is the Euclidean distance of the two vertices adjacent to it.

	Calculate the minimum spanning tree of the graph applying Prim's algorithm, and along the way, 
	total the weight of all selected edges.

	This source code uses a priority queue implementation, pqueue, whose license 
	is described in the below comment.
*/

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

#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cfloat>
#include <cmath>
using namespace std;

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

struct edge {
	int v;
	double weight;
	edge(int _v, double _weight) : v(_v), weight(_weight) {}
};

struct vertex_distance
{
	int vertex; // vertex
	double distance; // distance
	size_t pqueue_pos; // used internally by libpqueue

	vertex_distance() : vertex(0), distance(0.0), pqueue_pos(-1) {}
	vertex_distance(int v, double d) : vertex(v), distance(d), pqueue_pos(-1) {}

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

double euclidean_distance(const pair<double, double>& p, const pair<double, double>& q)
{
	double dx = p.first - q.first, dy = p.second - q.second;
	return sqrt(dx * dx + dy * dy);
}

double mst_prim(const vector< vector<edge> >& graph, int start, /* vector<int>& parents, */ vector<vertex_distance>& distances)
{
	// queue items (vertex_distance instances) are arranged in ascending order of their distances from the start vertex
	pqueue_t* queue = pqueue_init(distances.size(),
		vertex_distance::compare_distance, vertex_distance::get_distance, vertex_distance::set_distance,
		vertex_distance::get_position, vertex_distance::set_position);
	for (int i = 0; i < distances.size(); i++)
		pqueue_insert(queue, &distances[i]);

	double mst_distance = 0.0;
	while (pqueue_size(queue)) {
		vertex_distance* vd = reinterpret_cast<vertex_distance*>(pqueue_pop(queue));
		vd->pqueue_pos = -1;
		int u = vd->vertex;
		mst_distance += distances[u].distance;
		for (int i = 0; i < graph[u].size(); i++) {
			const edge& e = graph[u][i];
			if (distances[e.v].pqueue_pos != -1 // a vertex_distance instance for v is still in queue
				&& e.weight < distances[e.v].distance) {
/*
				parents[e.v] = u;
*/
				pqueue_change_priority(queue, e.weight, &distances[e.v]);
			}
		}
	}
	pqueue_free(queue);
	return mst_distance;
}

int main(int /* argc */, char** /* argv */)
{
	int cases;
	cin >> cases;
	for (int c = 0; c < cases; c++) {
		int n;
		cin >> n;
		vector< pair<double, double> > freckles(n);
		for (int i = 0; i < n; i++) {
			double x, y;
			cin >> x >> y;
			freckles[i] = pair<double, double>(x, y);
		}
		vector< vector<edge> > graph(n);
		for (int i = 0; i < n; i++)
			for (int j = i + 1; j < n; j++) {
				double d = euclidean_distance(freckles[i], freckles[j]);
				graph[i].push_back(edge(j, d));
				graph[j].push_back(edge(i, d));
			}
/*
		vector<int> parents(n, -1);
		parents[0] = 0;
*/
		vector<vertex_distance> distances(n);
		for (int i = 0; i < n; i++)
			distances[i] = vertex_distance(i, ((i) ? DBL_MAX : 0.0));
		printf("%.2f\n", mst_prim(graph, 0, /* parents, */ distances));
		if (c < cases - 1)
			cout << endl; // print a blank line between the two consecutive cases
	}
	return 0;
}

