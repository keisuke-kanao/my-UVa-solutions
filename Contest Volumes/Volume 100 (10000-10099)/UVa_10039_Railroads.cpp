
/*
	10.5.4 Railroads
	PC/UVa IDs: 111004/10039, Popularity: C, Success rate: average Level: 3

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10039_Railroads.cpp
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
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <climits>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
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

int get_city_number(const string& name, map<string, int>& cities, bool assign_if_not_found)
{
	map<string, int>::const_iterator i = cities.find(name);
	int n = -1;
	if (i == cities.end()) { // not registered yet
		if (assign_if_not_found) {
			n = cities.size(); // assign a number
			cities.insert(make_pair(name, n));
		}
	}
	else
		n = i->second;
	return n;
}

int minutes_from_midnight(int t)
{
	int hours = t / 100, minutes = t % 100;
	return hours * 60 + minutes;
}

void print_time(int t)
{
	cout << setw(2) << setfill('0') << t / 60 << setw(2) << t % 60;
}

struct vertex_comparator {
	const vector<int>& vertex_times;

	vertex_comparator(const vector<int>& _vertex_times) : vertex_times(_vertex_times) {}
	bool operator() (int i, int j) const {return vertex_times[i] < vertex_times[j];}
};

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

void shortest_path(int nr_vertices, int start,
	const vector< vector<edge> >& edges, vector<vertex_distance>& distances, vector<int>& parent_vertices)
{
	for (int i = 0; i < nr_vertices; i++)
		distances[i] = vertex_distance(i, ((i != start) ? INT_MAX : 0));
	// queue items (vertex_distance instances) are arranged in ascending order of their distances from the start vertex
	pqueue_t* queue = pqueue_init(distances.size(),
		vertex_distance::compare_distance, vertex_distance::get_distance, vertex_distance::set_distance,
		vertex_distance::get_position, vertex_distance::set_position);
	for (int i = 0; i < nr_vertices; i++)
		pqueue_insert(queue, &distances[i]);

	while (pqueue_size(queue)) {
		vertex_distance* vd = reinterpret_cast<vertex_distance*>(pqueue_pop(queue));
		vd->pqueue_pos = -1;
		int u = vd->v;
		int d = distances[u].distance;
		if (d == INT_MAX)
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
}

int get_departure_time(int start, int end, const vector<int>& vertex_times, const vector<int>& parent_vertices)
{
	for (int v = parent_vertices[end]; v != start; end = v, v = parent_vertices[end])
		;
	return vertex_times[end];
}

int main(int /* argc */, char** /* argv */)
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	int nr_scenarios;
	cin >> nr_scenarios;
	for (int s = 0; s < nr_scenarios; s++) {
		int nr_cities;
		cin >> nr_cities;
		map<string, int> cities; // key is a city's name, value is its number
		for (int i = 0; i < nr_cities; i++) {
			string city;
			cin >> city;
			get_city_number(city, cities, true);
		}

		int nr_descriptions;
		cin >> nr_descriptions;
		int nr_vertices = 0;
		vector<int> vertex_times;
		vector< vector<int> > vertices(nr_cities); // vertices[i] is the vector of vertices for the city of number i
		vector< vector<edge> > edges; // edges[i] is the vector of edges from the i-th vertex
		for (int i = 0; i < nr_descriptions; i++) {
			int nr_lines;
			cin >> nr_lines;
			int previous_time = -1;
			for (int j = 0; j < nr_lines; j++, nr_vertices++) {
				int time, city_nr;
				string city;
				cin >> time >> city;
				time = minutes_from_midnight(time);
				city_nr = get_city_number(city, cities, false);
				vertex_times.push_back(time);
				vertices[city_nr].push_back(nr_vertices);
				edges.push_back(vector<edge>()); // append a vector of edges for the (nr_vertices)-th vertex
				if (previous_time != -1)
					edges[nr_vertices - 1].push_back(edge(nr_vertices, time - previous_time));
						// append an edge between the two different cities
				previous_time = time;
			}
		}

		// For the vertices of each city, sort them in ascending order of time and then append the edges between them
		vertex_comparator vc(vertex_times);
		for (int i = 0; i < nr_cities; i++) {
			vector<int>& v = vertices[i];
			if (v.size() < 2)
				continue;
			sort(v.begin(), v.end(), vc);
			for (size_t j = 0; j < v.size() - 1; j++) {
				edges[v[j]].push_back(edge(v[j + 1], vertex_times[v[j + 1]] - vertex_times[v[j]]));
					// append an edge in the same city
				if (vertex_times[v[j]] == vertex_times[v[j + 1]])
					edges[v[j + 1]].push_back(edge(v[j], 0));
			}
		}

		int time;
		cin >> time;
		time = minutes_from_midnight(time);
		string start_city, destination_city;
		cin >> start_city >> destination_city;
		int start_city_nr = get_city_number(start_city, cities, false),
			destination_city_nr = get_city_number(destination_city, cities, false);
		pair<int, int> min_traveling_time(INT_MAX, INT_MAX);
			// first field is departure time, second field is arrival time
		if (start_city_nr != -1 && destination_city_nr != -1) {
			edges.push_back(vector<edge>()); // append a vector of edges for the pseudo vertex
			vector<int>& sv = vertices[start_city_nr];
			for (size_t i = 0; i < sv.size(); i++)
				if (time <= vertex_times[sv[i]])
					edges[nr_vertices].push_back(edge(sv[i], 0)); // append an edge to the vertex for the star city

			nr_vertices++;
			vector<vertex_distance> distances(nr_vertices);
			vector<int> parent_vertices(nr_vertices, -1);
			// apply Dijkstra's shortest path algorithm
			shortest_path(nr_vertices, nr_vertices - 1, edges, distances, parent_vertices);

			// For each vertex for the destination city, see if it can be reached, and 
			// if so, record the one that has the earliest arrival time.
			// If two or more vertices have the earliest arrival time, choose the one that has the latest departure time.
			vector<int>& dv = vertices[destination_city_nr];
			for (size_t i = 0; i < dv.size(); i++)
				if (distances[dv[i]].distance != INT_MAX) {
					pair<int, int> traveling_time =
						make_pair(get_departure_time(nr_vertices - 1, dv[i], vertex_times, parent_vertices), vertex_times[dv[i]]);
					if (traveling_time.second < min_traveling_time.second ||
						traveling_time.second == min_traveling_time.second && traveling_time.first > min_traveling_time.first)
						min_traveling_time = traveling_time;
				}
		}
		cout << "Scenario " << s + 1 << endl;
		if (min_traveling_time.first != INT_MAX) {
			cout << "Departure ";
			print_time(min_traveling_time.first);
			cout << ' ' << start_city << endl;
			cout << "Arrival   ";
			print_time(min_traveling_time.second);
			cout << ' ' << destination_city << endl;
		}
		else
			cout << "No connection\n";
		cout << endl; // print a blank line after each scenario
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}

