
/*
	UVa 10085 - The Most Distant State

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10085_The_Most_Distant_State.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <deque>
#include <queue>
#include <map>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

/*
	Each square is indexed as follows:
		+--+---+---+
		| 0|  1|  2|
		+--+---+---+
		| 3|  4|  5|
		+--+---+---+
		| 6|  7|  8|
		+--+---+---+

	A state is represented by a long long variable in which 
	the number of the i-th square is stored in bit (i * 4) - bit (i * 4 + 3).
*/

const int nr_rows = 3, nr_columns = 3, nr_squares = 9;

long long swap_space(int si, int row, int column, long long state)
{
	if (row < 0 || row >= nr_rows || column < 0 || column >= nr_columns)
		return -1;
	else {
		int nsi = row * nr_rows + column; // index to the square in which the space is to be moved
		// swap si-th space with nsi-th number
		long long mask = static_cast<long long>(0x0f) << (si * 4),
			nmask = static_cast<long long>(0x0f) << (nsi * 4);
		long long ni = (state & nmask) >> (nsi * 4);
		state &= ~(mask | nmask);
		state |= ni << (si * 4);
		return state;
	}
}

int get_space_index(long long state) // get the index to a square in which the space is
{
	int i;
	for (i = 0; i < nr_squares; i++, state >>= 4)
		if (!(state & 0x0f))
			break;
	return i;
}

void trace_back_moves(long long state, map<long long, long long>& states, deque<char>& moves)
{
	int si = get_space_index(state);
	int row = si / nr_rows, column = si % nr_rows;
	while (true) {
		long long pstate = states[state];
		if (pstate == -1)
			break;
		int psi = get_space_index(pstate);
		int prow = psi / nr_rows, pcolumn = psi % nr_rows;
		char dir;
		if (prow == row - 1)
			dir = 'D';
		else if (prow == row + 1)
			dir = 'U';
		else if (pcolumn == column - 1)
			dir = 'R';
		else
			dir = 'L';
		moves.push_front(dir);
		state = pstate; row = prow; column = pcolumn;
	}
}

long long bfs(int si /* index to space square */, long long state, deque<char>& moves) // Breadth-First-Search
{
	const int nr_dirs = 4;
	const int idirs[nr_dirs][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

	queue<pair<int, long long> > q;
	map<long long, long long> states;
		// key is a state, value is its prevous state
	states.insert(make_pair(state, -1));
	q.push(make_pair(si, state));
	while (!q.empty()) {
		si = q.front().first;
		state = q.front().second;
		q.pop();
		int row = si / nr_rows, column = si % nr_rows;
		for (int i = 0; i < nr_dirs; i++) {
			long long nstate = swap_space(si, row + idirs[i][0], column + idirs[i][1], state);
			if (nstate == -1)
				continue;
			pair<map<long long, long long>::iterator, bool> result = states.insert(make_pair(nstate, state));
			if (result.second) { // s has newly been inserted
				int nsi = (row + idirs[i][0]) * nr_rows + (column + idirs[i][1]);
				q.push(make_pair(nsi, nstate));
			}
		}
	}
#ifdef DEBUG
	cout << "number of states = " << states.size() << endl;
#endif
	trace_back_moves(state, states, moves);
	return state;
}

int main()
{
	string line;
	getline(cin, line);
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	istringstream iss(line);
	int nr_cases;
	iss >> nr_cases;
	iss.clear();
	getline(cin, line); // skip a blank line
	for (int c = 1; c <= nr_cases; c++) {
		long long state = 0;
		int si;
		for (int i = 0; i < nr_rows; i++) {
			getline(cin, line);
			iss.str(line);
			for (int j = 0; j < nr_columns; j++) {
				int k;
				iss >> k;
				int l = i * nr_rows + j;
				state |= static_cast<long long>(k) << (l * 4);
				if (!k)
					si = l;
			}
			iss.clear();
		}
		getline(cin, line); // skip a blank line
		deque<char> moves;
		state = bfs(si, state, moves);
		cout << "Puzzle #" << c << endl;
		for (int i = 0; i < nr_squares; i++, state >>= 4) {
			int j = static_cast<int>(state & 0x0f);
			cout << j << (((i % 3) == 2) ? '\n' : ' ');
		}
		for (deque<char>::const_iterator i = moves.begin(), e = moves.end(); i != e; ++i)
			cout << *i;
		cout << endl << endl; // after each test case, output an empty line
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}

