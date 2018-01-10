
/*
	UVa 10047 - The Monocycle

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10047_The_Monocycle.cpp
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

enum {dir_unknown = -1, dir_north, dir_south, dir_west, dir_east};
enum {clr_red, clr_black, clr_green, clr_white, clr_blue};
const int nr_dirs = dir_east - dir_north + 1, nr_colors = clr_blue - clr_red + 1;

struct vertex_distance
{
	int v_; // vertex
	int distance_; // distance
	int direction_, color_;
	size_t pqueue_pos_; // used internally by libpqueue

	vertex_distance() : v_(-1), distance_(-1), pqueue_pos_(-1) {}
	vertex_distance(int v, int distance, int direction, int color)
		: v_(v), distance_(distance), direction_(direction), color_(color), pqueue_pos_(-1) {}

	static int get_distance(void* vd);
	static void set_distance(void* vd, int d);
	static int compare_distance(int next, int current);
	static size_t get_position(void* vd);
	static void set_position(void *vd, size_t position);
};

int vertex_distance::get_distance(void* vd)
{
	return reinterpret_cast<vertex_distance*>(vd)->distance_;
}

void vertex_distance::set_distance(void* vd, int d)
{
	reinterpret_cast<vertex_distance*>(vd)->distance_ = d;
}

int vertex_distance::compare_distance(int next, int current)
{
	return current < next;
}

size_t vertex_distance::get_position(void* vd)
{
	return reinterpret_cast<vertex_distance*>(vd)->pqueue_pos_;
}

void vertex_distance::set_position(void *vd, size_t position)
{
	reinterpret_cast<vertex_distance*>(vd)->pqueue_pos_ = position;
}

bool relax_distance(int m, int n, const vector< vector<char> >& squares,
	int next_dir, int di, vector<vertex_distance>& distances, pqueue_t* queue)
{
	int i = di / (n * nr_dirs * nr_colors);
	int j = (di - i * (n * nr_dirs * nr_colors)) / (nr_dirs * nr_colors);
	switch (next_dir) {
	case dir_north:
		i--; break;
	case dir_south:
		i++; break;
	case dir_west:
		j--; break;
	case dir_east:
		j++; break;
	}
	if (i < 0 || i >= m || j < 0 || j >= n || squares[i][j] == '#')
		return false;
	int next_color = (distances[di].color_ + 1) % nr_colors;
	int k = i * (n * nr_dirs * nr_colors) + j * nr_dirs * nr_colors + next_dir * nr_colors + next_color;
	if (distances[k].pqueue_pos_ == -1) // an vertex_distance instance is not in the queue
		return false;
	const int ds[nr_dirs][nr_dirs] = {
		{1, 3, 2, 2}, // from north
		{3, 1, 2, 2}, // from south
		{2, 2, 1, 3}, // from east
		{2, 2, 3, 1} // from west
	};
	int d = distances[di].distance_ + ds[distances[di].direction_][next_dir];
	if (d < distances[k].distance_) {
		pqueue_change_priority(queue, d, &distances[k]);
		return true;
	}
	else
		return false;
}

int shortest_path(int m, int n, int start, int end, const vector< vector<char> >& squares)
{
	int nr_vertices = m * n * nr_dirs * nr_colors;
	vector<vertex_distance> distances(nr_vertices);
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			for (int d = 0; d < nr_dirs; d++)
				for (int c = 0; c < nr_colors; c++) {
					int l = i * (n * nr_dirs * nr_colors) + j * nr_dirs * nr_colors + d * nr_colors + c;
					if (i * n + j == start && d == dir_north && c == clr_green)
						distances[l] = vertex_distance(l, 0, d, c);
					else
						distances[l] = vertex_distance(l, numeric_limits<int>::max(), d, c);
				}
	// queue items (vertex_distance instances) are arranged in ascending order of their distances from the start vertex
	pqueue_t* queue = pqueue_init(distances.size(),
		vertex_distance::compare_distance, vertex_distance::get_distance, vertex_distance::set_distance,
		vertex_distance::get_position, vertex_distance::set_position);
	for (int i = 0; i < nr_vertices; i++)
		pqueue_insert(queue, &distances[i]);
	while (pqueue_size(queue)) {
		vertex_distance* vd = reinterpret_cast<vertex_distance*>(pqueue_pop(queue));
		vd->pqueue_pos_ = -1;
		int i = vd->v_ / (n * nr_dirs * nr_colors);
		int j = (vd->v_ - i * (n * nr_dirs * nr_colors)) / (nr_dirs * nr_colors);
		int d = vd->distance_;
		if (d == numeric_limits<int>::max())
			break;
#ifdef DEBUG
		cout << i << ' ' << j << ' ' << d << endl;
#endif
		if (i * n + j == end && vd->color_ == clr_green)
			return vd->distance_;
		relax_distance(m, n, squares, dir_north, vd->v_, distances, queue);
		relax_distance(m, n, squares, dir_south, vd->v_, distances, queue);
		relax_distance(m, n, squares, dir_west, vd->v_, distances, queue);
		relax_distance(m, n, squares, dir_east, vd->v_, distances, queue);
	}
	return -1;
}

int main()
{
	for (int c = 1; ; c++) {
		int m, n;
		cin >> m >> n;
		if (!m && !n)
			break;
		if (c > 1)
			cout << endl; // print a blank line between two successive test cases
		vector< vector<char> > squares(m, vector<char>(n));
		int s, t;
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++) {
				cin >> squares[i][j];
				if (squares[i][j] == 'S')
					s = i * n + j;
				else if (squares[i][j] == 'T')
					t = i * n + j;
			}
		int min_path = shortest_path(m, n, s, t, squares);
		cout << "Case #" << c << endl;
		if (min_path == -1)
			cout << "destination not reachable\n";
		else
			cout << "minimum time = " << min_path << " sec\n";
	}
	return 0;
}

