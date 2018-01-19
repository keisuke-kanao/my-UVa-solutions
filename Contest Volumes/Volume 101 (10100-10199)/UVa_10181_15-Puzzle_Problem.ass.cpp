
/*
	8.6.2 15-Puzzle Problem
	PC/UVa IDs: 110802/10181, Popularity: B, Success rate: average Level: 3

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10181_15-Puzzle_Problem.ass.cpp

	An accepted solution.
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
#include <sstream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <functional>
#include <cstdlib>
#ifdef DEBUG
#include <cassert>
#endif
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

/*
	unsigned long long state; // state of a puzzle

	Each state of a puzzle consists of the values stored in the 16 tiles.
	i-th tile (i >= 0) value is stored in the four consecutive bits located between bit (i * 4) and bit (i * 4 + 3).

	If the missing tile is at i-th tile, possible movements are:
		moving up is possible if i > 3.
		moving down is possible if i < 12.
		moving right is possible if (i % 4) < 3.
		movign left is possible if (i % 4) != 0.

	At each step, transfer to the at most four possible states the missing tile can move.

	Further Search is cancelled if it reaches either of the following condition:
		The puzzle gets solved.
		50 steps has passed.
*/

const int nr_tiles = 16; // number of tiles
const int g_score_max = 50; // number of max. steps
const unsigned long long goal = 0x0fedcba987654321ULL; // the state of a puzzle when solved

/*
	Solvability of the Tiles Game
		(http://www.cs.bham.ac.uk/~mdr/teaching/modules04/java2/TilesSolvability.html)

1. If the grid width is odd, then the number of inversions in a solvable situation is even.
2. If the grid width is even, and the blank is on an even row counting from the bottom (second-last, fourth-last etc), 
	then the number of inversions in a solvable situation is odd.
3. If the grid width is even, and the blank is on an odd row counting from the bottom (last, third-last, fifth-last etc) 
	then the number of inversions in a solvable situation is even.
*/
bool is_puzzle_solvable(int tiles[])
{
	int ibr, nr_inversions = 0;
	for (int i = 0; i < nr_tiles; i++) {
		if (!tiles[i])
			ibr = i / 4;
		else {
			for (int j = i + 1; j < nr_tiles; j++)
				if (tiles[j] && tiles[i] > tiles[j])
					nr_inversions++;
		}
	}
	return (ibr & 1) ? !(nr_inversions & 1) : (nr_inversions & 1);
}

/*
	Admissible heuristic from Wikipedia

	The Manhattan distance of a puzzle is defined as:
		h(n) = ƒ°distance(tile, the_correct_position) for all tiles

	The Manhattan distance is an admissible heuristic because every tile will have to be moved 
	at least the amount of spots in between itself and its correct position.
*/
int heuristic_cost_estimate(unsigned long long state)
{
	int heuristic_cost = 0;
	// for each tile, calcualate the Manhattan distance, i.e., 
	// the distance between the current number of the tile and the one that the tile should have
	for (int i = 0; i < nr_tiles; i++, state >>= 4) {
		int nr = static_cast<int>(state & 0xf) - 1;
		if (nr >= 0) // not the missing tile
			heuristic_cost += abs(nr / 4 - i / 4) + abs(nr % 4 - i % 4);
/*
		else
			heuristic_cost += (3 - i / 4) + (3 - i % 4);
*/
	}
	return 1.5 * heuristic_cost;
}

struct node
{
	size_t pqueue_pos_; // used internally by libpqueue
	int mi_; // index to the missing tile
	unsigned long long state_; // state of tiles
	int g_score_; // Cost from start along best known path.
	int h_score_; // heuristic_cost_estimate(start, goal)
	int f_score_; // Estimated total cost from start to goal through y.

	node() : pqueue_pos_(-1), mi_(-1), state_(-1), g_score_(-1), h_score_(-1), f_score_(-1) {}
	node(int mi, unsigned long long state, int g_score)
		: pqueue_pos_(-1), mi_(mi), state_(state), g_score_(g_score), h_score_(heuristic_cost_estimate(state)),
		f_score_(g_score_ + h_score_) {}

	static int get_distance(void* vd);
	static void set_distance(void* vd, int d);
	static int compare_distance(int next, int current);
	static size_t get_position(void* vd);
	static void set_position(void *vd, size_t position);
};

int node::get_distance(void* vd)
{
	return reinterpret_cast<node*>(vd)->f_score_;
}

void node::set_distance(void* vd, int d)
{
	reinterpret_cast<node*>(vd)->f_score_ = d;
}

int node::compare_distance(int next, int current)
{
	return current < next;
}

size_t node::get_position(void* vd)
{
	return reinterpret_cast<node*>(vd)->pqueue_pos_;
}

void node::set_position(void *vd, size_t position)
{
	reinterpret_cast<node*>(vd)->pqueue_pos_ = position;
}

unsigned long long exchange_tile(int i, int j, unsigned long long state)
{
	const unsigned long long mask = 0xfULL;
	unsigned long long nr_i = (state & mask << (i * 4)) >> (i * 4);
	unsigned long long nr_j = (state & mask << (j * 4)) >> (j * 4);
	state &= ~(mask << (i * 4)); state &= ~(mask << (j * 4));
	state |= nr_i << (j * 4); state |= nr_j << (i * 4);
	return state;
}

/*
	A* serarch algorithm from Wikipedia
		(http://en.wikipedia.org/wiki/A*_search_algorithm)

	Note that this is a case where the closed set can be omitted, so the algorithm iis adapted 
	so that new nodes are added to the open set only if they have a lower value than at any previous iteration.
*/

void add_or_update_node(int mi, int ti, unsigned long long current,
	int g_score, map<unsigned long long, unsigned long long>& came_from,
	pqueue_t* open_set, map<unsigned long long, node*>& in_open_set, map<unsigned long long, node*>& removed_from_open_set)
{
	node* pn = NULL;
	int tentative_g_score = g_score + 1; // tentative_g_score := g_score[current] + dist_between(current, neighbor)
	unsigned long long neighbor = exchange_tile(mi, ti, current); // move the missing tile

	map<unsigned long long, node*>::iterator i;
	if ((i = removed_from_open_set.find(neighbor)) != removed_from_open_set.end()) {
		// if neighbor has ever been in openset, but currenty it's not in openset
		pn = i->second;
		if (tentative_g_score < pn->g_score_) {
			// neighbor is added only if it has a lesser g_score than it has ever have at any previous iterations
			pn->g_score_ = tentative_g_score; // g_score[neighbor] := tentative_g_score
			pn->f_score_ = pn->g_score_ + pn->h_score_; // f_score[neighbor] := g_score[neighbor] + h_score[neighbor]
			pqueue_insert(open_set, pn); // add neighbor to openset again
			in_open_set.insert(make_pair(neighbor, pn));
			removed_from_open_set.erase(i);
			came_from[neighbor] = current; // came_from[neighbor] := current
		}
	}
	else if ((i = in_open_set.find(neighbor)) == in_open_set.end()) {
		// else if neighbor has never been in openset
		pn = new node(ti, neighbor, tentative_g_score);
			// g_score[neighbor] := tentative_g_score
			// h_score[neighbor] := heuristic_cost_estimate(neighbor, goal)
			// f_score[neighbor] := g_score[neighbor] + h_score[neighbor]
		pqueue_insert(open_set, pn); // add neighbor to openset
		in_open_set.insert(make_pair(neighbor, pn));
		came_from[neighbor] = current; // came_from[neighbor] := current
	}
	else { // neighbor is currently in openset
		pn = i->second;
		if (tentative_g_score < pn->g_score_) {
			pn->g_score_ = tentative_g_score; // g_score[neighbor] := tentative_g_score
			pn->f_score_ = pn->g_score_ + pn->h_score_; // f_score[neighbor] := g_score[neighbor] + h_score[neighbor]
			pqueue_change_priority(open_set, pn->f_score_, pn);
			came_from[neighbor] = current; // came_from[neighbor] := current
		}
	}
}

void free_nodes(const map<unsigned long long, node*>& nodes)
{
	for (map<unsigned long long, node*>::const_iterator i = nodes.begin(), e = nodes.end(); i != e; ++i)
		delete i->second;
}

int a_star_seach(int mi, unsigned long long current, map<unsigned long long, unsigned long long>& came_from)
{
	const int nr_initial_nodes = 1048576;
	pqueue_t* open_set = pqueue_init(nr_initial_nodes,
		node::compare_distance, node::get_distance, node::set_distance, node::get_position, node::set_position);
		// The set of tentative nodes to be evaluated, initially containing the start node.
	map<unsigned long long, node*> in_open_set;
		// key is a state, value is the node instance that is in openset
	map<unsigned long long, node*> removed_from_open_set;
		// key is a state, value is the node instance that has ever been in openset but it's currenty removed form it
	node* pn = new node(mi, current, 0); // start node
	pqueue_insert(open_set, pn);
	in_open_set.insert(make_pair(current, pn));
	came_from[current] = -1;
	int shortest_g_score = -1;
	while (pqueue_size(open_set)) { // while openset is not empty
		pn = reinterpret_cast<node*>(pqueue_pop(open_set)); // the node in openset having the lowest f_score_ value
			// remove current from openset
		int mi = pn->mi_;
		unsigned long long current = pn->state_;
		int g_score = pn->g_score_;
		in_open_set.erase(current);
		removed_from_open_set.insert(make_pair(current, pn));
		if (current == goal) {
			// if current = goal, return reconstruct_path(came_from, came_from[goal])
			shortest_g_score = g_score;
			break;
		}
		if (g_score < g_score_max) {
	        // for each neighbor in neighbor_nodes(current)
			if (mi < 12) // move the missing tile down
				add_or_update_node(mi, mi + 4, current, g_score, came_from, open_set, in_open_set, removed_from_open_set);
			if (mi > 3) // move the missing tile up
				add_or_update_node(mi, mi - 4, current, g_score, came_from, open_set, in_open_set, removed_from_open_set);
			if ((mi % 4) < 3) // move the missing tile right
				add_or_update_node(mi, mi + 1, current, g_score, came_from, open_set, in_open_set, removed_from_open_set);
			if (mi % 4) // move the missing tile left
				add_or_update_node(mi, mi - 1, current, g_score, came_from, open_set, in_open_set, removed_from_open_set);
		}
	}
	pqueue_free(open_set);
	free_nodes(in_open_set);
	free_nodes(removed_from_open_set);
	return shortest_g_score;
}

void print_steps(unsigned long long ps, unsigned long long cs, map<unsigned long long, unsigned long long>& states,
	ostringstream& oss)
{
	if (ps == -1)
		return;
	print_steps(states[ps], ps, states, oss);
	int phi = -1, chi = -1;
	for (int i = 0; phi == -1 || chi == -1; i++, ps >>= 4, cs >>= 4) {
		if (!(ps & 0xf))
			phi = i;
		if (!(cs & 0xf))
			chi = i;
	}
	int ud = chi / 4 - phi / 4;
	if (ud > 0)
		oss << 'D';
	else if (ud < 0)
		oss << 'U';
	else if (chi % 4 - phi % 4 > 0)
		oss << 'R';
	else
		oss << 'L';
}

#ifdef DEBUG
void follow_steps(int mi, unsigned long long state, const string& s)
{
	for (int i = 0; i < s.length(); i++) {
		int nmi;
		switch (s[i]) {
		case 'U':
			assert(mi > 3); nmi = mi - 4; break;
		case 'D':
			assert(mi < 12); nmi = mi + 4; break;
		case 'L':
			assert(mi % 4); nmi = mi - 1; break;
		case 'R':
			assert((mi % 4) < 3); nmi = mi + 1; break;
		}
		state = exchange_tile(mi, nmi, state);
		mi = nmi;
	}
	assert(state == goal);
}
#endif

int main()
{
	int n;
	cin >> n;
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	while (n--) {
		int tiles[nr_tiles];
		unsigned long long current = 0; // puzzle state
		int mi; // index of the missing tile
		for (int i = 0; i < nr_tiles; i++) {
			unsigned long long nr;
			cin >> nr;
			tiles[i] = nr;
			current |= nr << (i * 4);
			if (!nr)
				mi = i;
		}
		int shortest_g_score = -1;
		map<unsigned long long, unsigned long long> came_from; // The map of navigated nodes.
		if (is_puzzle_solvable(tiles))
			shortest_g_score = a_star_seach(mi, current, came_from);
		if (shortest_g_score != -1) {
#ifdef DEBUG
			cout << "number of steps = " << shortest_g_score << endl;
#endif
			ostringstream oss;
			print_steps(came_from[goal], goal, came_from, oss);
			cout << oss.str() << endl;
#ifdef DEBUG
			follow_steps(mi, current, oss.str());
#endif
		}
		else
			cout << "This puzzle is not solvable.\n";
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}

