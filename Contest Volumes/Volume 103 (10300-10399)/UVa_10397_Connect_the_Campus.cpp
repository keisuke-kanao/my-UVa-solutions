
/*
	UVa 10397 - Connect the Campus

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10397_Connect_the_Campus.cpp
*/

/*
	Generate an undirected graph where vertices are buildings and each edge is assigned a weight 
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
#include <utility>
#include <limits>
#include <cstdio>
#include <cstdlib>
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

const int nr_buildings_max = 750;
pair<int, int> buildings[nr_buildings_max];
bool cables[nr_buildings_max][nr_buildings_max];
	// cables[i][j] isi true if building i and j are connected by the cable
double matrix[nr_buildings_max][nr_buildings_max];
vertex_distance distances[nr_buildings_max];


double euclidean_distance(const pair<int, int>& p, const pair<int, int>& q)
{
	double dx = static_cast<double>(p.first - q.first), dy = static_cast<double>(p.second - q.second);
	return sqrt(dx * dx + dy * dy);
}

double mst_prim(int n)
{
	// queue items (vertex_distance instances) are arranged in ascending order of their distances from the first vertex
	pqueue_t* queue = pqueue_init(n,
		vertex_distance::compare_distance, vertex_distance::get_distance, vertex_distance::set_distance,
		vertex_distance::get_position, vertex_distance::set_position);
	for (int i = 0; i < n; i++)
		pqueue_insert(queue, &distances[i]);
	double mst_distance = 0.0;
	while (pqueue_size(queue)) {
		vertex_distance* vd = reinterpret_cast<vertex_distance*>(pqueue_pop(queue));
		vd->pqueue_pos = -1;
		int u = vd->vertex;
		mst_distance += distances[u].distance;
		for (int v = 0; v < n; v++)
			if (v != u && distances[v].pqueue_pos != -1 // a vertex_distance instance for v is still in queue
				&& matrix[u][v] < distances[v].distance) {
				pqueue_change_priority(queue, matrix[u][v], &distances[v]);
			}
	}
	pqueue_free(queue);
	return mst_distance;
}

int main()
{
	int n;
	while (cin >> n) {
		for (int i = 0; i < n; i++)
			cin >> buildings[i].first >> buildings[i].second;
		for (int i = 0; i < n; i++)
			for (int j = i + 1; j < n; j++)
				cables[i][j] = cables[j][i] = false;
		int m;
		cin >> m;
		for (int i = 0; i < m; i++) {
			int j, k;
			cin >> j >> k;
			j--; k--;
			cables[j][k] = cables[k][j] = true;
		}
		for (int i = 0; i < n; i++)
			for (int j = i + 1; j < n; j++)
				matrix[i][j] = matrix[j][i] = (cables[i][j]) ? 0.0 : euclidean_distance(buildings[i], buildings[j]);
		for (int i = 0; i < n; i++)
			distances[i] = vertex_distance(i, ((i) ? numeric_limits<double>::max() : 0.0));
		printf("%.2f\n", mst_prim(n));
	}
	return 0;
}

