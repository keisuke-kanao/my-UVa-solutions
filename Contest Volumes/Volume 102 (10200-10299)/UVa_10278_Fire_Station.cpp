
/*
	10.5.3 Fire Station
	PC/UVa IDs: 111003/10278, Popularity: B, Success rate: low Level: 2

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10278_Fire_Station.cpp
*/

/*
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
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <utility>
#include <cstdio>
#include <cstdlib>
#include <climits>
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

struct road {
	int is; // intersection
	int length;
	road(int _is, int _length) : is(_is), length(_length) {}
};

struct is_distance
{
	int is; // intersection
	int distance; // distance
	size_t pqueue_pos; // used internally by libpqueue

	is_distance() : is(0), distance(0), pqueue_pos(-1) {}
	is_distance(int i, int d) : is(i), distance(d), pqueue_pos(-1) {}

	static int get_distance(void* vd);
	static void set_distance(void* vd, int d);
	static int compare_distance(int next, int current);
	static size_t get_position(void* vd);
	static void set_position(void *vd, size_t position);
};

int is_distance::get_distance(void* vd)
{
	return reinterpret_cast<is_distance*>(vd)->distance;
}

void is_distance::set_distance(void* vd, int d)
{
	reinterpret_cast<is_distance*>(vd)->distance = d;
}

int is_distance::compare_distance(int next, int current)
{
	return current < next;
}

size_t is_distance::get_position(void* vd)
{
	return reinterpret_cast<is_distance*>(vd)->pqueue_pos;
}

void is_distance::set_position(void *vd, size_t position)
{
	reinterpret_cast<is_distance*>(vd)->pqueue_pos = position;
}

pair<int, int> find_farthest_intersection(int nr_intersections, int start, vector< vector<road> >& roads)
{
	vector<is_distance> distances(nr_intersections);
		for (int i = 0; i < nr_intersections; i++)
			distances[i] = is_distance(i, ((i != start) ? INT_MAX : 0));
	// queue items (is_distance instances) are arranged in ascending order of their distances from the start vertex
	pqueue_t* queue = pqueue_init(distances.size(),
		is_distance::compare_distance, is_distance::get_distance, is_distance::set_distance,
		is_distance::get_position, is_distance::set_position);
	for (int i = 0; i < distances.size(); i++)
		pqueue_insert(queue, &distances[i]);

	while (pqueue_size(queue)) {
		is_distance* isd = reinterpret_cast<is_distance*>(pqueue_pop(queue));
		isd->pqueue_pos = -1;
		int u = isd->is;
		int d = distances[u].distance;
		if (d == INT_MAX)
			break;
		for (int i = 0; i < roads[u].size(); i++) {
			const road& r = roads[u][i];
			if (distances[r.is].pqueue_pos != -1 // an is_distance instance for v is still in queue
				&& d + r.length < distances[r.is].distance)
				pqueue_change_priority(queue, d + r.length, &distances[r.is]);
		}
	}
	pqueue_free(queue);
	pair<int, int> farthest_intersection(0, -1); // first field is the distance, second field is the intersection
	// find the intersection that is farthest from start
	for (int i = 0; i < nr_intersections; i++)
		if (distances[i].distance > farthest_intersection.first)
			farthest_intersection = make_pair(distances[i].distance, i);
	return farthest_intersection;
}

int main(int /* argc */, char** /* argv */)
{
	string line;
	istringstream iss;
	// read the number of cases
	getline(cin, line);
	iss.str(line);
	int nr_cases; // number of cases
	iss >> nr_cases;
	iss.clear();
	if (nr_cases)
		getline(cin, line); // skip a blank line
	for (int c = 0; c < nr_cases; c++) {
		getline(cin, line);
		iss.str(line);
		int nr_fire_stations, nr_intersections;
		iss >> nr_fire_stations >> nr_intersections;
		iss.clear();
		set<int> fire_stations;
			// should be set<int> instead of vector<int>, since there may be more than one fire station per intersection
		for (int i = 0; i < nr_fire_stations; i++) { // read the intersections at which fire station are located
			getline(cin, line);
			iss.str(line);
			int f;
			iss >> f;
			iss.clear();
			fire_stations.insert(f);
		}
		vector< vector<road> > roads(nr_intersections + 1); // adjacency list
		// The intersection 0 is a pseudo node connected to every fire station with a distance equal to 0.
		for (set<int>::const_iterator i = fire_stations.begin(); i != fire_stations.end(); i++) {
			roads[0].push_back(road(*i, 0));
			roads[*i].push_back(road(0, 0));
		}
		string line;
		while (getline(cin, line) && !line.empty()) { // read the road segments
			iss.str(line);
			int u, v, l;
			iss >> u >> v >> l;
			iss.clear();
			roads[u].push_back(road(v, l));
			roads[v].push_back(road(u, l));
		}
		// for each of the intersections where there are no fire stations, 
		// put the fire station temporarily, apply Dijkstra's shortest path algorithm, and 
		// record the the intersection that is farthest from the station and its distance
		pair<int, int> farthest_intersection(INT_MAX, 1); // first field is the distance, second field is the intersection
		for (int i = 1; i <= nr_intersections; i++) {
			if (fire_stations.find(i) != fire_stations.end())
				continue;
			roads[0].push_back(road(i, 0));
			roads[i].push_back(road(0, 0));
			pair<int, int> fi = find_farthest_intersection(nr_intersections + 1, 0, roads);
			roads[0].pop_back();
			roads[i].pop_back();
			if (fi.first < farthest_intersection.first)
				farthest_intersection = make_pair(fi.first, i);
		}
		cout << farthest_intersection.second << endl;
		if (c < nr_cases - 1)
			cout << endl; // separate the output of each two consecutive cases by a blank line
	}
	return 0;
}

