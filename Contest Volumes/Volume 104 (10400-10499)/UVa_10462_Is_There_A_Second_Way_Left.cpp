
/*
	UVa 10462 - Is There A Second Way Left?

	To build using Visucal Studio 2012:
		cl -EHsc -O2 UVa_10462_Is_There_A_Second_Way_Left.cpp
*/

/*
	Generate an undirected graph where vertices are schools and edges are connections between them.

	Calculate the minimum spanning tree of the graph applying Prim's algorithm, and along the way, 
	total the weight of all selected edges.

	Calculate the second best minimum spanning tree.

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
#include <vector>
#include <algorithm>
#include <limits>
#include <cstdio>
#include <cstdlib>
using namespace std;

#ifdef  __cplusplus
extern "C" {
#endif

/** priority data type */
typedef int pqueue_pri_t;

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
	int weight;
	edge(int _v, int _weight) : v(_v), weight(_weight) {}
};

struct vertex_distance
{
	int vertex; // vertex
	int distance; // distance
	size_t pqueue_pos; // used internally by libpqueue

	vertex_distance() : vertex(0), distance(0), pqueue_pos(-1) {}
	vertex_distance(int v, int d) : vertex(v), distance(d), pqueue_pos(-1) {}

	static int get_distance(void* vd);
	static void set_distance(void* vd, int d);
	static int compare_distance(int next, int current);
	static size_t get_position(void* vd);
	static void set_position(void *vd, size_t position);
};

int vertex_distance::get_distance(void* vd)
{
	return reinterpret_cast<vertex_distance*>(vd)->distance;
}

void vertex_distance::set_distance(void* vd, int d)
{
	reinterpret_cast<vertex_distance*>(vd)->distance = d;
}

int vertex_distance::compare_distance(int next, int current)
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

int mst_prim(int n, int start, const vector< vector<edge> >& graph, vector<const edge*>& mst)
{
	vector<vertex_distance> distances(n);
	for (int i = 0; i < n; i++) {
		mst[i] = NULL;
		distances[i] = vertex_distance(i, ((i != start) ? numeric_limits<int>::max() : 0));
	}
	// queue items (vertex_distance instances) are arranged in ascending order of their distances from the first vertex
	pqueue_t* queue = pqueue_init(distances.size(),
		vertex_distance::compare_distance, vertex_distance::get_distance, vertex_distance::set_distance,
		vertex_distance::get_position, vertex_distance::set_position);
	for (int i = 0; i < distances.size(); i++)
		pqueue_insert(queue, &distances[i]);

	int mst_distance = 0;
	while (pqueue_size(queue)) {
		vertex_distance* vd = reinterpret_cast<vertex_distance*>(pqueue_pop(queue));
		vd->pqueue_pos = -1;
		int u = vd->vertex;
		if (distances[u].distance == numeric_limits<int>::max()) {
			mst_distance = numeric_limits<int>::max();
			break;
		}
		mst_distance += distances[u].distance;
		for (int i = 0; i < graph[u].size(); i++) {
			const edge& e = graph[u][i];
			if (distances[e.v].pqueue_pos != -1 // a vertex_distance instance for v is still in queue
				&& e.weight < distances[e.v].distance) {
				mst[e.v] = &e;
				pqueue_change_priority(queue, e.weight, &distances[e.v]);
			}
		}
	}
	pqueue_free(queue);
	return mst_distance;
}

int second_best_mst_prim(int n, int start, const vector< vector<edge> >& graph, const edge* mst_e)
{
	vector<vertex_distance> distances(n);
	for (int i = 0; i < n; i++)
		distances[i] = vertex_distance(i, ((i != start) ? numeric_limits<int>::max() : 0));
	// queue items (vertex_distance instances) are arranged in ascending order of their distances from the start vertex
	pqueue_t* queue = pqueue_init(distances.size(),
		vertex_distance::compare_distance, vertex_distance::get_distance, vertex_distance::set_distance,
		vertex_distance::get_position, vertex_distance::set_position);
	for (int i = 0; i < distances.size(); i++)
		pqueue_insert(queue, &distances[i]);

	int mst_distance = 0;
	while (pqueue_size(queue)) {
		vertex_distance* vd = reinterpret_cast<vertex_distance*>(pqueue_pop(queue));
		vd->pqueue_pos = -1;
		int u = vd->vertex;
		if (distances[u].distance == numeric_limits<int>::max())
			return numeric_limits<int>::max(); // u is not in the tree
		mst_distance += distances[u].distance;
		for (int i = 0; i < graph[u].size(); i++) {
			if (&graph[u][i] == mst_e)
				continue;
			const edge& e = graph[u][i];
			if (distances[e.v].pqueue_pos != -1 // a vertex_distance instance for v is still in queue
				&& e.weight < distances[e.v].distance)
				pqueue_change_priority(queue, e.weight, &distances[e.v]);
		}
	}
	pqueue_free(queue);
	return mst_distance;
}

int main()
{
	int t;
	cin >> t;
	for (int cn = 1; cn <= t; cn++) {
		int v, e;
		cin >> v >> e;
		vector< vector<edge> > graph(v);
		for (int i = 0; i < e; i++) {
			int u, v, w;
			cin >> u >> v >> w;
			u--; v--;
			graph[u].push_back(edge(v, w));
			graph[v].push_back(edge(u, w));
		}
		int mst_distance, second_mst_distance = numeric_limits<int>::max();
		vector<const edge*> mst(v);
		if ((mst_distance = mst_prim(v, 0, graph, mst)) != numeric_limits<int>::max()) {
			for (int i = 1; i < v; i++)
				second_mst_distance = min(second_mst_distance, second_best_mst_prim(v, 0, graph, mst[i]));
		}
#ifdef DEBUG
		cout << mst_distance << ' ' << second_mst_distance << endl;
#endif
		cout << "Case #" << cn << " : ";
		if (mst_distance == numeric_limits<int>::max())
			cout << "No way\n";
		else if (second_mst_distance == numeric_limits<int>::max())
			cout << "No second way\n";
		else
			cout << second_mst_distance << endl;
	}
	return 0;
}

