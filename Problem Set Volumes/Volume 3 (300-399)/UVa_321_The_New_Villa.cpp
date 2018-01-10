
/*
	UVa 321 - The New Villa

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_321_The_New_Villa.cpp

	from ACM Southwestern European Regional Contest Problem Set 1996 Problem F
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_EU_SWERC/1996/index.html)
*/

#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

const int nr_rooms_max = 10;
const int room_shift = 1 << nr_rooms_max;
const int lights_mask = room_shift - 1;

bool doors[nr_rooms_max][nr_rooms_max]; // doors[i][j] is true if there is a door between i-th and j-th rooms
int switches[nr_rooms_max]; // switches[i] is the bitmap of lights of the i-th room,
	// in which j-th bit of switches[i] is set if there is a switch for the light of j-th room in the i-th room

bool visited[nr_rooms_max * room_shift]; // visited[i] is true if the state of i has already been visited
int parents[nr_rooms_max * room_shift]; // parents[i] is the i-th parent state

bool push_state(int current, int next, queue<int>& q)
{
	if (!visited[next]) {
		visited[next] = true;
		parents[next] = current;
		q.push(next);
		return true;
	}
	else
		return false;
}

bool bfs(int nr_rooms, int end_state)
{
/*
	Each state consists of two fields:
		bit 0 - bit 9: bitmap of lights where i-th bit is set if the i-th room's light is on
		bit 10 - bit 13: room index
	Do a breadth-first-search between transferable states.
*/
	queue<int> q;
	int state = 1; // light is on at the first room (hallway)
	visited[state] = true;
	q.push(state);
	while (!q.empty()) {
		int current = q.front();
		q.pop();
		if (current == end_state)
			return true;
		int r = current >> nr_rooms_max, lights = current & lights_mask;
		for (int i = 0, l = 1; i < nr_rooms_max; i++, l <<= 1)
			if (doors[r][i] && lights & l) // since i-th rooms has already been lit, we can move to it
				push_state(current, i << nr_rooms_max | lights, q);
		for (int i = 0, l = 1; i < nr_rooms; i++, l <<= 1)
			if (switches[r] & l) { // r-th room has a switch of the light for i-th room
				int next = -1;
				if (lights & l) {
					if (r != i) // the light can be switched to off
						next = r << nr_rooms_max | lights & ~l;
				}
				else // the light can be switched to on
					next = r << nr_rooms_max | lights | l;
				if (next != -1)
					push_state(current, next, q);
			}
	}
	return false;
}

int get_number_of_steps(int end_state)
{
	int nr_steps = 0;
	for (int p = parents[end_state]; p != -1; p = parents[p])
		nr_steps++;
	return nr_steps;
}

void print_steps(int current, int next)
{
	if (current == -1)
		return;
	print_steps(parents[current], current);
	int i = current ^ next;
	if (i & lights_mask) {
		int l = 1;
		for (int j = i >> 1; j; j >>= 1)
			l++;
		if (i & next)
			cout << "- Switch on light in room " << l << ".\n";
		else
			cout << "- Switch off light in room " << l << ".\n";
	}
	else {
		int r = next >> nr_rooms_max;
		cout << "- Move to room " << r + 1 << ".\n";
	}
}

int main()
{
	for (int v = 1; ; v++) {
		int r, d, s;
		cin >> r >> d >> s;
		if (!r && !d && !s)
			break;
		memset(doors, 0, sizeof(doors));
		memset(switches, 0, sizeof(switches));
		for (int i = 0; i < d; i++) {
			int j, k;
			cin >> j >> k;
			j--; k--;
			doors[j][k] = doors[k][j] = true;
		}
		for (int i = 0; i < s; i++) {
			int j, k;
			cin >> j >> k;
			j--; k--;
			switches[j] |= 1 << k;
		}
		memset(visited, 0, sizeof(visited));
		memset(parents, -1, sizeof(parents));
		int end_state = (r - 1) << nr_rooms_max | 1 << (r - 1);
		bool successful = bfs(r, end_state);
		cout << "Villa #" << v << endl;
		if (successful) {
			cout << "The problem can be solved in " << get_number_of_steps(end_state) << " steps:\n";
			print_steps(parents[end_state], end_state);
		}
		else
			cout << "The problem cannot be solved.\n";
		cout << endl;
	}
	return 0;
}

