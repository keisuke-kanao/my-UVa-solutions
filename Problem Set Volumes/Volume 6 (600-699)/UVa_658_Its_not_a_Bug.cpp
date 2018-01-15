
/*
	UVa 658 - It's not a Bug, it's a Feature!

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_658_Its_not_a_Bug.cpp

	from ACM Western and Southwestern European Regionals 1998
		(https://cs05.informatik.uni-ulm.de/acm/Regionals/1998/)

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
#include <string>
#include <vector>
#include <cstdlib>
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

struct sequence
{
	int time_; // time that has been taken so far in seconds
	int bug_; // bit sets describing the bus
	size_t pqueue_pos_; // used internally by libpqueue

	sequence() : time_(-1), bug_(0), pqueue_pos_(-1) {}
	sequence(int time, int bug) : time_(time), bug_(bug), pqueue_pos_(-1) {}

	static int get_distance(void* vd);
	static void set_distance(void* vd, int d);
	static int compare_distance(int next, int current);
	static size_t get_position(void* vd);
	static void set_position(void *vd, size_t position);
};

int sequence::get_distance(void* vd)
{
	return reinterpret_cast<sequence*>(vd)->time_;
}

void sequence::set_distance(void* vd, int d)
{
	reinterpret_cast<sequence*>(vd)->time_ = d;
}

int sequence::compare_distance(int next, int current)
{
	return current < next;
}

size_t sequence::get_position(void* vd)
{
	return reinterpret_cast<sequence*>(vd)->pqueue_pos_;
}

void sequence::set_position(void *vd, size_t position)
{
	reinterpret_cast<sequence*>(vd)->pqueue_pos_ = position;
}

/*
	Starting with the state of "+++...+", apply Dijkstra's shortest path algorithm.
	For each state from the queue, see if any available patchs can be applied:
		For a bug of state '+', a patch of '0' or '+'
		For a bug of state '-', a patch of '0' or '-'
*/

struct patch {
	static int n_, mask_;
	int time_; // time in seconds it takes to apply the patch
	int before_present_; // bugs that have to be present before the patch can be applied
	int before_absent_; // bugs that have to be present before the patch can be applied
	int before_unaffected_; // bugs that doesn't matter whether it is present or not
	int after_present_; // bugs that are fixed by the patch
	int after_unaffected_;// bugs that are not affected by the patch

	static void set_mask(int n);
	patch() {}
	patch(int time, const string& before, const string& after);
	int apply(int bug) const;
};

int patch::n_ = 0, patch::mask_ = 0;

void patch::set_mask(int n)
{
	n_ = n; mask_ = (1 << n) - 1;
}

patch::patch(int time, const string& before, const string& after)
	: time_(time), before_present_(0), before_absent_(0), before_unaffected_(0), after_present_(0), after_unaffected_(0)
{
	for (int i = 0; i < n_; i++) {
		if (i) {
			before_present_ <<= 1; before_absent_ <<= 1; before_unaffected_ <<= 1;
			after_present_ <<= 1; after_unaffected_ <<= 1;
		}
		if (before[i] == '+')
			before_present_ |= 1;
		else if (before[i] == '-')
			before_absent_ |= 1;
		else
			before_unaffected_ |= 1;
		if (after[i] == '+')
			after_present_ |= 1;
		else if (after[i] == '0')
			after_unaffected_ |= 1;
	}
}

int patch::apply(int bug) const
{
	// see if the patch can be applied to bug, and if so, return the applied result
	int b = (bug & before_present_) | (~bug & before_absent_) | before_unaffected_;
	if (b != mask_)
		return -1;
	return after_present_ | (bug & after_unaffected_);
}

int shortest_path(int n, int m, const vector<patch>& patches)
{
	int nr_sequences = 1 << n;
	vector<sequence> sequences(nr_sequences);
		// sequences[i] is the sequence for the bug of i
	vector<bool> queued(nr_sequences, false);
		// queued[i] is true if bug of i has already been queued
	pqueue_t* queue = pqueue_init(nr_sequences, sequence::compare_distance, sequence::get_distance,
		sequence::set_distance, sequence::get_position, sequence::set_position);
	int start = patch::mask_;
	for (int i = 0; i < m; i++) {
		int bug = patches[i].apply(start);
		if (bug != -1) {
			sequences[bug] = sequence(patches[i].time_, bug);
			queued[bug] = true;
			pqueue_insert(queue, &sequences[bug]);
		}
	}
	int fixed_time = -1;
	while (pqueue_size(queue)) {
		sequence* s = reinterpret_cast<sequence*>(pqueue_pop(queue));
		s->pqueue_pos_ = -1;
		if (!s->bug_) {
			fixed_time = s->time_; break;
		}
		for (int i = 0; i < m; i++) {
			int bug = patches[i].apply(s->bug_);
			if (bug != -1) {
				int time = s->time_ + patches[i].time_;
				if (queued[bug]) {
					if (sequences[bug].pqueue_pos_ != -1 && sequences[bug].time_ > time)
						pqueue_change_priority(queue, time, &sequences[bug]);
				}
				else {
					sequences[bug] = sequence(time, bug);
					queued[bug] = true;
					pqueue_insert(queue, &sequences[bug]);
				}
			}
		}
	}
	pqueue_free(queue);
	return fixed_time;
}

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start;
#endif
	for (int pn = 1; ; pn++) {
		int n, m;
		cin >> n >> m;
#ifdef __ELAPSED_TIME__
		if (pn == 1)
			start = clock();
#endif
		if (!n && !m)
			break;
		patch::set_mask(n);
		vector<patch> patches(m);
		for (int i = 0; i < m; i++) {
			int time;
			string before, after;
			cin >> time >> before >> after;
			patches[i] = patch(time, before, after);
		}
		// apply Dijkstra's shortest path algorithm
		int fixed_time = shortest_path(n, m, patches);
		cout << "Product " << pn << endl;
		if (fixed_time != -1)
			cout << "Fastest sequence takes " << fixed_time << " seconds.\n";
		else
			cout << "Bugs cannot be fixed.\n";
		cout << endl;
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}

