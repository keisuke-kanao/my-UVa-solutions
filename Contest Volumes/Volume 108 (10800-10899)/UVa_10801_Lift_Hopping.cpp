
/*
	UVa 10801 - Lift Hopping

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10801_Lift_Hopping.cpp
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
#include <string>
#include <sstream>
#include <vector>
#include <limits>
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
	int v; // destination vertex
	int weight; // waiting time or travelling time

	edge() : v(-1), weight(-1) {}
	edge(int _v, int _weight) : v(_v), weight(_weight) {}
};

struct vertex_distance
{
	int v; // vertex
	int distance; // distance
	size_t pqueue_pos; // used internally by libpqueue

	vertex_distance() : v(-1), distance(-1), pqueue_pos(-1) {}
	vertex_distance(int _v, int _distance) : v(_v), distance(_distance), pqueue_pos(-1) {}

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

bool shortest_path(int nr_vertices, int start, int end,
	const vector< vector<edge> >& edges, vector<vertex_distance>& distances, vector<int>& parent_vertices)
{
	for (int i = 0; i < nr_vertices; i++)
		distances[i] = vertex_distance(i, ((i != start) ? numeric_limits<int>::max() : 0));
	// queue items (vertex_distance instances) are arranged in ascending order of their distances from the start vertex
	pqueue_t* queue = pqueue_init(distances.size(),
		vertex_distance::compare_distance, vertex_distance::get_distance, vertex_distance::set_distance,
		vertex_distance::get_position, vertex_distance::set_position);
	for (int i = 0; i < nr_vertices; i++)
		pqueue_insert(queue, &distances[i]);
	bool successful = false;
	while (pqueue_size(queue)) {
		vertex_distance* vd = reinterpret_cast<vertex_distance*>(pqueue_pop(queue));
		vd->pqueue_pos = -1;
		int u = vd->v;
		if (u == end) {
			successful = true; break;
		}
		int d = distances[u].distance;
		if (d == numeric_limits<int>::max())
			break;
		for (size_t i = 0; i < edges[u].size(); i++) {
			const edge& e = edges[u][i];
			if (distances[e.v].pqueue_pos != -1 // an vertex_distance instance for t.route is still in queue
				&& d + e.weight < distances[e.v].distance) {
				parent_vertices[e.v] = u;
				pqueue_change_priority(queue, d + e.weight, &distances[e.v]);
			}
		}
	}
	return successful;
}

int main()
{
	const int nr_floors = 100, s_wait = 60;
	string line;
	istringstream iss;
	while (getline(cin, line)) {
		iss.str(line);
		int n, k;
		iss >> n >> k;
		iss.clear();
		getline(cin, line);
		iss.str(line);
		vector<int> speeds(n);
		for (int i = 0; i < n; i++)
			iss >> speeds[i];
		iss.clear();
		vector< vector<edge> > edges(nr_floors); // edges[i] is the vector of edges from the i-th vertex
		for (int i = 0; i < n; i++) {
			getline(cin, line);
			iss.str(line);
			vector<int> floors(nr_floors);
			int j = 0;
			while (iss >> floors[j])
				j++;
			for (int fi = 0; fi < j - 1; fi++) {
				int fli = floors[fi];
				for (int fj = fi + 1; fj < j; fj++) {
					int flj = floors[fj];
					int s = speeds[i] * abs(flj - fli) + s_wait;
					edges[fli].push_back(edge(flj, s));
					edges[flj].push_back(edge(fli, s));
				}
			}
			iss.clear();
		}
		vector<vertex_distance> distances(nr_floors);
		vector<int> parent_vertices(nr_floors);
		// apply Dijkstra's shortest path algorithm
		bool successful = shortest_path(nr_floors, 0, k, edges, distances, parent_vertices);
		if (successful)
			cout << ((k) ? distances[k].distance - s_wait : 0) << endl;
		else
			cout << "IMPOSSIBLE\n";
	}
	return 0;
}

/*

another sample input

3 30
100 100 1
0 2 4 5 6 7 8 21 22 23 24 25 26 30
1 2 19 11 12 13 14 15 16 30
1 10 30
2 99
100 1
0 1 98 99
1 98
3 1
100 10 100
0 1
0 1
0 1
2 5
1 1
0 3
4 5
4 89
7 2 4 8
3 34 45 56 77
4 23 34 89
0 99
3 99
5 99
12 90 34 56 22
0 4 7 3 6 8 98
4 10 20 23 46 50 69 88 99
0 3 12 45 50 77 88 99
0 20 46 77 98
0 50
2 99
10 40
1 2 3 4 99 0 12 
3 4 2 0 12 99
5 66
10 11 19 55 2
0 1 3 5 7 9 13 15 20 25 30 99
4 15 19 20 25 30 80
3 15 20
35 45 66 80 99
0 1 2 3 4 5 6

output

449
417
10
IMPOSSIBLE
1671
2826
990
1734

*/

