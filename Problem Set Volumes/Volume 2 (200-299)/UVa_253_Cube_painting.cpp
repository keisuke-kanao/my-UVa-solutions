
/*
	UVa 253 - Cube painting

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_253_Cube_painting.cpp
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

enum {rt_unknown = -1, rt_1_2, rt_1_5, rt_1_3, rt_1_4, rt_2_3, rt_2_4}; // directions of rotations

string rotate_one(const string& s, int dir)
{
	string t(s);
	switch (dir) {
	case rt_1_2:
		// 1 2 3 4 5 6 -> 5 1 3 4 6 2
		t[0] = s[4]; t[1] = s[0]; t[4] = s[5]; t[5] = s[1];
		break;
	case rt_1_5:
		// 1 2 3 4 5 6 -> 2 6 3 4 1 5
		t[0] = s[1]; t[1] = s[5]; t[4] = s[0]; t[5] = s[4];
		break;
	case rt_1_3:
		// 1 2 3 4 5 6 -> 4 2 1 6 5 3
		t[0] = s[3]; t[2] = s[0]; t[3] = s[5]; t[5] = s[2];
		break;
	case rt_1_4:
		// 1 2 3 4 5 6 -> 3 2 6 1 5 4
		t[0] = s[2]; t[2] = s[5]; t[3] = s[0]; t[5] = s[3];
		break;
	case rt_2_3:
		// 1 2 3 4 5 6 -> 1 4 2 5 3 6
		t[1] = s[3]; t[2] = s[1]; t[3] = s[4]; t[4] = s[2];
		break;
	case rt_2_4:
		// 1 2 3 4 5 6 -> 1 3 5 2 4 6
		t[1] = s[2]; t[2] = s[4]; t[3] = s[1]; t[4] = s[3];
		break;
	}
	return t;
}

bool is_searched(const string &s, vector<bool>& searched)
{
	int index = 0;
	for (int i = 0, j = s.length(); i < j; i++) {
		int k = (s[i] == 'r') ? 0 : ((s[i] == 'g') ? 1 : 2);
		index *= 3;
		index += k;
	}
	if (searched[index])
		return true; // already searched
	else {
		searched[index] = true;
		return false;
	}
}

bool rotate_cube(const string& current, const string& target, int previous_dir, vector<bool>& searched)
{
	if (current == target)
		return true;
	else {
		for (int i = rt_1_2; i <= rt_2_4; i++) {
			if (i == previous_dir)
				continue;
			string s = rotate_one(current, i);
			if (is_searched(s, searched))
				continue;
			if (rotate_cube(s, target, i, searched))
				return true;
		}
		return false;
	}
}

int main()
{
	vector<bool> searched(729);
	string s;
	while (cin >> s) {
		string t = s.substr(6);
		s.resize(6);
		fill(searched.begin(), searched.end(), false);
		cout << (rotate_cube(s, t, rt_unknown, searched) ? "TRUE\n" : "FALSE\n");
	}
	return 0;
}

