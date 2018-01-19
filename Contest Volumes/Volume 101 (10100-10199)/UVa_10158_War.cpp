
/*
	10.5.5 War
	PC/UVa IDs: 111005/10158, Popularity: B, Success rate: average Level: 3

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10158_War.cpp
*/

#include <iostream>
#include <vector>
using namespace std;

class union_find {
public:
	union_find(int _n);
	~union_find() {}
	int find(int i) const;
	int do_union(int i, int j);
		// generate the union of the two sets to which i and j belong and return the representative of the result set

private:
	int n; // number of elements
	vector<int> representatives; // representatives[i] is the representative of a set to which i belongs
	vector<int> ranks; // number of elements in the set to which i belongs
};

union_find::union_find(int _n)
	: n(_n), representatives(_n), ranks(_n, 1)
{
	for (int i = 0; i < n; i++)
		representatives[i] = i;
}

int union_find::find(int i) const // return the representative of a set to which i belongs
{
	return (representatives[i] == i) ? i : find(representatives[i]);
}

int union_find::do_union(int i, int j)
// generate the union of the two sets to which i and j belong and return the representative of the result set
{
	int ri = find(i), rj = find(j);
	if (ri == rj) // already in the same set
		return ri;
	if (ranks[ri] >= ranks[rj]) {
		ranks[ri] += ranks[rj];
		representatives[rj] = ri;
		return ri;
	}
	else {
		ranks[rj] += ranks[ri];
		representatives[ri] = rj;
		return rj;
	}
}

enum opcode { // operation codes
	opc_unknown = 0, opc_set_friends, opc_set_enemies, opc_are_friends, opc_are_enemies
};

void set_enemies(int i, int j, union_find& friends, vector<int>& enemies)
{
	int ri = friends.find(i), rj = friends.find(j);
	int rei = enemies[ri], rej = enemies[rj];
	enemies[ri] = (rei == -1) ? rj : friends.do_union(rei, rj);
	enemies[rj] = (rej == -1) ? ri : friends.do_union(rej, ri);
}

void set_friends(int i, int j, union_find& friends, vector<int>& enemies)
{
	int ri = friends.find(i), rj = friends.find(j);
	friends.do_union(ri, rj);
	if (enemies[ri] != -1)
		set_enemies(enemies[ri], rj, friends, enemies);
	if (enemies[rj] != -1)
		set_enemies(ri, enemies[rj], friends, enemies);
}

bool are_friends(int i, int j, const union_find& friends)
{
	return friends.find(i) == friends.find(j);
}

bool are_enemies(int i, int j, const union_find& friends, const vector<int>& enemies)
{
	int ri = friends.find(i), rj = friends.find(j);
	return ri == enemies[rj] || rj == enemies[ri];
}

int main(int /* argc */, char** /* argv */)
{
	int nr_people;
	cin >> nr_people;
	union_find friends(nr_people);
	vector<int> enemies(nr_people, -1);
		// enemies[i] is the representative of the set to which i's enemies belong
	while (true) {
		int code, i, j;
		cin >> code >> i >> j;
		if (!code && !i && !j)
			break;
		switch (code) {
		case opc_set_friends:
			if (are_enemies(i, j, friends, enemies))
				cout << -1 << endl;
			else
				set_friends(i, j, friends, enemies);
			break;
		case opc_set_enemies:
			if (are_friends(i, j, friends))
				cout << -1 << endl;
			else
				set_enemies(i, j, friends, enemies);
			break;
		case opc_are_friends:
			cout << ((are_friends(i, j, friends)) ? 1 : 0) << endl;
			break;
		case opc_are_enemies:
			cout << ((are_enemies(i, j, friends, enemies)) ? 1 : 0) << endl;
			break;
		}
	}
	return 0;
}

