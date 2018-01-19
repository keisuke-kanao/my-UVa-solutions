
/*
	9.6.2 Playing With Wheels
	PC/UVa IDs: 110902/10067, Popularity: C, Success rate: average Level: 2

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_10067_Playing_With_Wheels.cpp
*/

/*
	Consider the four-digit integers formed by the topmost digits of the wheels as graph vertices.
	A vertex of four-digit integer A B C D is adjacent to the following eight vertices:
		((A + 1) mod 10) B C D	((A - 1) mod 10) B C D
		A ((B + 1) mod 10) C D	A ((B - 1) mod 10) C D
		A B ((C + 1) mod 10) D	A B ((C - 1) mod 10) D
		A B C ((D + 1) mod 10)	A B C ((D - 1) mode 10
	Generate a adjacency list for this graph.

	For each test case, do a bredth first search for the graph, starting from the initial configuration 
	and ending at the target configuration. The path should exclude the forbidden configurations.
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int nr_digits = 4, nr_states = 10000;
enum vertex_state {initialized = -1, discovered, processed};

void construct_adjacency_list(vector< vector<int> >& adjacency_list)
{
	for (int i = 0; i < nr_states; i++)
		for (int j = 0, k = i, p = 1; j < nr_digits; j++, k /= 10, p *= 10) {
			int d = k % 10; // least significant digit
			int left_d = (d + 1) % 10, right_d = (d + 9 /* + 10 - 1 */) % 10;
			int adjacent = i - d * p; // set (4 - j)-th digit of i to 0
			adjacency_list[i][2 * (nr_digits - 1 - j)] = adjacent + left_d * p; // replace (nr_digits - j)-th digit with its left one
			adjacency_list[i][2 * (nr_digits - j) - 1] = adjacent + right_d * p; // replace (nr_digits - j)-th digit with its right one
		}
}

int read_state()
{
	int state = 0;
	for (int i = 0, p = 1000; i < nr_digits; i++, p /= 10) {
		int digit;
		cin >> digit;
		state += digit * p;
	}
	return state;
}

bool search_state_path(int initial, int target,
	const vector< vector<int> >& adjacency_list, const vector<int>& forbidden_states, vector<int>& paths)
{
	// do a breadth-first search
	vector<vertex_state> vs(nr_states, initialized);
	for (vector<int>::const_iterator i = forbidden_states.begin(); i != forbidden_states.end(); i++)
		vs[*i] = processed; // forbidden states will be excluded in the search
	if (vs[initial] == processed) // the initial state is forbedden
		return false;
	if (initial == target)
		return true;
	queue<int> vq; // vertex queue
	vs[initial] = discovered;
	vq.push(initial);
	while (!vq.empty()) {
		int v = vq.front(); vq.pop();
		vs[v] = processed;
		for (int i = 0; i < nr_digits * 2; i++) {
			int j = adjacency_list[v][i];
			if (vs[j] == initialized) {
				vs[j] = discovered;
				paths[j] = v;
				if (j == target)
					return true;
				else
					vq.push(j);
			}
		}
	}
	return false;
}

int get_state_path_length(int initial, int target, const vector<int>& paths)
{
	int length = 0;
	for (int previous_state = paths[target]; previous_state != -1; previous_state = paths[previous_state], length++)
		;
	return length;
}

int main(int /* argc */, char** /* argv */)
{
	int cases;
	cin >> cases;
	if (!cases)
		return 0;
	vector< vector<int> > adjacency_list(nr_states, vector<int>(nr_digits * 2));
	construct_adjacency_list(adjacency_list);
	while (cases--) {
		int initial = read_state(), target = read_state();
		int nr_forbidden;
		cin >> nr_forbidden;
		vector<int> forbidden_states; // set of forbidden states
		for (int i = 0; i < nr_forbidden; i++)
			forbidden_states.push_back(read_state());
		vector<int> paths(nr_states, -1);
		if (search_state_path(initial, target, adjacency_list, forbidden_states, paths))
			cout << get_state_path_length(initial, target, paths) << endl;
		else
			cout << -1 << endl;
	}
	return 0;
}

