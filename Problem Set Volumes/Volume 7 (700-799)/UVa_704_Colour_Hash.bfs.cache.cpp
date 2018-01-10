
/*
	UVa 704 - Colour Hash

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_704_Colour_Hash.bfs.cache.cpp

	An accepted solution.
*/

#include <iostream>
#include <map>
#include <deque>
#include <queue>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

enum rotation { // rotations
	unknown = 0,
	left_clockwise = 1, // left wheel clockwise
	right_clockwise = 2, // right wheel clockwise
	left_counterclockwise = 3, // left wheel counterclockwise
	right_counterclockwise = 4, // right wheel counterclockwise
};

typedef pair<unsigned long long, unsigned long long> wheels;
/*
	wheels.first consists of left wheel numbers and wheels.second consists of right wheel numbers.
	i-th (i >= 0) number occupies between (47 - i * 4)-th and (44 - i * 4)-th bits of wheels.first/wheels.second.
	The final condition of wheels are represented as wheels(0x034305650121, 0x078709a90121).
*/

const size_t numbers_per_wheel = 12; // count of numbers (triangle/separator) per wheel
const size_t max_movements = 16; // max. number of movements
const wheels wheels_solved(0x034305650121, 0x078709a90121); // the final condition of wheels

map< wheels, deque<char> > latter_half_cache;
	// key is a state, value is the sequence of movements that leads to the final state

wheels rotate_wheel(rotation r, const wheels& w)
{
	const unsigned long long mask_8_bits = 0xff, mask_12_bits = 0xfff;
	unsigned long long left = w.first, right = w.second;
	unsigned long long b;
	switch (r) {
	case left_clockwise: // left wheel clockwise
		b = left & mask_8_bits; left >>= 8; left |= b << 40;
		right &= ~mask_12_bits; right |= left & mask_12_bits;
		break;
	case right_clockwise: // right wheel clockwise
		b = (right & mask_8_bits << 40) >> 40; right &= ~(mask_8_bits << 40); right <<= 8; right |= b;
		left &= ~mask_12_bits; left |= right & mask_12_bits;
		break;
	case left_counterclockwise: // left wheel counterclockwise
		b = (left & mask_8_bits << 40) >> 40; left &= ~(mask_8_bits << 40); left <<= 8; left |= b;
		right &= ~mask_12_bits; right |= left & mask_12_bits;
		break;
	case right_counterclockwise: // right wheel counterclockwise
		b = right & mask_8_bits; right >>= 8; right |= b << 40;
		left &= ~mask_12_bits; left |= right & mask_12_bits;
		break;
	}
	return wheels(left, right);
}

bool rotate_wheel_and_cache(rotation r, const wheels& w, const deque<char>& m, queue<wheels>& q)
{
	wheels nw = rotate_wheel(r, w);
	if (latter_half_cache.find(nw) != latter_half_cache.end())
		return false;
	rotation nr;
	switch (r) {
	case left_clockwise:
		nr = left_counterclockwise; break;
	case right_clockwise:
		nr = right_counterclockwise; break;
	case left_counterclockwise:
		nr = left_clockwise; break;
	case right_counterclockwise:
		nr = right_clockwise; break;
	}
	deque<char> nm(m);
	nm.push_front(nr);
	latter_half_cache.insert(make_pair(nw, nm));
	q.push(nw);
	return true;
}

void generate_state_cache()
{
/*
	Starting from the final state (configuration), 
	do a BFS (Breadth First Search) and cache the states that can be reached in 8 steps (movements) or less.
*/
	latter_half_cache.insert(make_pair(wheels_solved, deque<char>()));
	queue<wheels> q;
	q.push(wheels_solved);
	while (!q.empty()) {
		wheels w = q.front(); q.pop();
		deque<char> m = latter_half_cache[w];
		if (m.size() < max_movements / 2) {
			for (int r = left_clockwise; r <= right_counterclockwise; r++)
				rotate_wheel_and_cache(static_cast<rotation>(r), w, m, q);
		}
	}
#ifdef DEBUG
	cerr << "number of latter_half_cache entries = " << latter_half_cache.size() << endl;
#endif
}

bool rotate_wheel_and_cache(rotation r, const wheels& w, const deque<char>& m, queue<wheels>& q,
	map< wheels, deque<char> >& cache)
{
	wheels nw = rotate_wheel(r, w);
	if (cache.find(nw) != cache.end())
		return false;
	deque<char> nm(m);
	nm.push_back(r);
	cache.insert(make_pair(nw, nm));
	q.push(nw);
	return true;
}

bool solve_state(const wheels& w, deque<char>& mv)
{
	bool solved = false;
	map< wheels, deque<char> > cache;
	cache.insert(make_pair(w, deque<char>()));
	queue<wheels> q;
	q.push(w);
	map< wheels, deque<char> >::const_iterator lhce = latter_half_cache.end();
	while (!q.empty()) {
		wheels w = q.front(); q.pop();
		deque<char>& m = cache[w];
		map< wheels, deque<char> >::const_iterator lhci = latter_half_cache.find(w);
		if (lhci != lhce) {
			solved = true;
			mv = m;
			mv.insert(mv.end(), lhci->second.begin(), lhci->second.end());
			break;
		}
		else if (m.size() < max_movements / 2) {
			for (int r = left_clockwise; r <= right_counterclockwise; r++)
				rotate_wheel_and_cache(static_cast<rotation>(r), w, m, q, cache);
		}
	}
	return solved;
}

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	generate_state_cache();
	int n;
	cin >> n;
	while (n--) {
		int nr;
		wheels w(0, 0);
		for (size_t i = 0; i < numbers_per_wheel; i++) {
			cin >> nr;
			w.first <<= 4; w.first |= nr;
		}
		for (size_t i = 0; i < numbers_per_wheel; i++) {
			cin >> nr;
			w.second <<= 4; w.second |= nr;
		}
		deque<char> mv;
		if (solve_state(w, mv)) {
			if (mv.empty())
				cout << "PUZZLE ALREADY SOLVED\n";
			else {
				for (deque<char>::const_iterator i = mv.begin(), e = mv.end(); i != e; ++i)
					cout << static_cast<int>(*i);
				cout << endl;
			}
		}
		else
			cout << "NO SOLUTION WAS FOUND IN 16 STEPS\n";
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}

