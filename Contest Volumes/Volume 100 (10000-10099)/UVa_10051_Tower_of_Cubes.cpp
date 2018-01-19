
/*
	9.6.6 Tower of Cubes
	PC/UVa IDs: 110906/10051, Popularity: C, Success rate: high Level: 3

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10051_Tower_of_Cubes.cpp
*/

#include <iostream>
#include <vector>
#include <map>
using namespace std;

enum cube_face_side {front = 0, back, left, right, top, bottom};
const int nr_faces = bottom - front + 1;

struct cube_face {
	int nr;
	int /* cube_face_side */ side;
	int color;
};

void print_cubes(int ith, const vector<cube_face>& cube_faces, const vector< pair<int, int> >& tower_heights)
{
	const char* face_sides[] = {"front", "back", "left", "right", "top", "bottom"};
	int i = tower_heights[ith].second;
	if (i != -1)
		print_cubes(i, cube_faces, tower_heights);
	cout << cube_faces[ith].nr << ' ' << face_sides[cube_faces[ith].side] << endl;
}

int main(int /* argc */, char** /* argv */)
{
	for (int case_nr = 1; ; case_nr++) {
		int nr_cubes;
		cin >> nr_cubes;
		if (!nr_cubes)
			break;
		int nr_cube_faces = nr_cubes * nr_faces;
		vector<cube_face> cube_faces(nr_cube_faces);
		multimap<int, int> colors; // key is a color, value (may be multiple) is an index to cube_faces vector
		for (int i = 0; i < nr_cubes; i++)
			for (int j = front; j < nr_faces; j++) {
				int k = i * nr_faces + j;
				cube_face& f = cube_faces[k];
				f.nr = i + 1; f.side = j; cin >> f.color;
				colors.insert(pair<int, int>(f.color, k));
			}

		// apply LIS (Longest Increasing Sequence)
		vector< pair<int, int> > tower_heights(nr_cube_faces, make_pair(0, -1));
			// for each i-th face of a cube, 
			// tower_heights[i].first is the height of the tower whose bottom cube has the i-th face on top
			// tower_heights[i].second is the index to previous face of a cube
		int max_height = 0; // max. tower height so far
		int i_max_height = 0; // index to the face that has the max. height
		for (int i = 0; i < nr_cubes; i++)
			for (int j = 0; j < nr_faces; j++) {
				int k = i * nr_faces + j; // index to the face of a cube
				int l = (k & 1) ? k - 1 : k + 1; // index to the face that is on the opposite side
				int height = tower_heights[k].first + 1;
				// enumerate the faces whose color is the same as the oppsite face
				pair<multimap<int, int>::const_iterator, multimap<int, int>::const_iterator> cis =
					colors.equal_range(cube_faces[l].color);
				for (multimap<int, int>::const_iterator ci = cis.first; ci != cis.second; ci++) {
					int m = ci->second; // index to the face of a cube
					if (cube_faces[m].nr <= i + 1) // for the faces that are on the same cube or on the upper cubes
						continue;
					pair<int, int>& th = tower_heights[m];
					if (th.first < height) {
						th.first = height; th.second = k;
						if (height > max_height) {
							max_height = height; i_max_height = m;
						}
					}
				}
			}
		if (case_nr > 1)
			cout << endl; // print a blank line between two successive test cases
		cout << "Case #" << case_nr << endl;
		cout << max_height + 1 << endl;
		print_cubes(i_max_height, cube_faces, tower_heights);
	}
	return 0;
}

