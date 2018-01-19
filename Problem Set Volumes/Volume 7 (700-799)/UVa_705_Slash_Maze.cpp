
/*
	9.6.4 Slash Maze
	PC/UVa IDs: 110904/705, Popularity: B, Success rate: average Level: 2

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_705_Slash_Maze.cpp
*/

/*
A maze of width w and height h has (w + w - 1) * (h - 1) + (w - 1) squares (lozenges) in which 
(w - 1) squares and w squares are piled up alternatively.
Each slash or backslash may affect the connectivities of squares in a three consecutive rows in which
both the upper and lower rows have w squares and the middile row has (w - 1) squares:
	The upper half of a slash or a backslash may disconnect a square in the upper row with another in the middle row.
	The lower half of a slach or a backslash may disconnect a square in the middle row with another in the lower row.

A maze can be modeled as a graph where squares are vertices and edges are between the virtices if the 
corresponding squares are not disconnected by a slash or a backslash.
*/

#include <iostream>
#include <vector>
#include <set>
using namespace std;

enum vertex_state {initialized = -1, discovered, processed};

void construct_adjacency_matrix(int width, int height, vector< vector<unsigned char> >& matrix)
{
	for (int h = 0, upper_row = 0, lower_row = width - 1 /* vertices in a upper/lower rows */;
		h < height - 1; h++, upper_row += 2 * width - 1, lower_row += 2 * width - 1) {
		for (int i = 0; i < width - 1; i++) {
			matrix[upper_row + i][upper_row + i + width - 1] = matrix[upper_row + i + width - 1][upper_row + i] = 1;
			matrix[upper_row + i][upper_row + i + width] = matrix[upper_row + i + width][upper_row + i] = 1;
		}
		for (int i = 0; i < width; i++) {
			if (i)
			matrix[lower_row + i][lower_row + i + width - 1] = matrix[lower_row + i + width - 1][lower_row + i] = 1;
			if (i < width - 1)
			matrix[lower_row + i][lower_row + i + width] = matrix[lower_row + i + width][lower_row + i] = 1;
		}
	}
	for (int h = 0, upper_row = -1, middle_row = 0, lower_row = width - 1 /* vertices in a upper/middle/lower rows */;
		h < height; h++, upper_row = lower_row, middle_row += 2 * width - 1, lower_row += 2 * width - 1) {
		for (int i = 0; i < width; i++) {
			char c;
			cin >> c;
			if (c == '/') {
				if (h < height - 1 && i)
					matrix[middle_row + i - 1][lower_row + i] = matrix[lower_row + i][middle_row + i - 1] = 0;
				if (h && i < width - 1)
					matrix[upper_row + i][middle_row + i] = matrix[middle_row + i][upper_row + i] = 0;
			}
			else { // backslash
				if (h && i)
					matrix[middle_row + i - 1][upper_row + i] = matrix[upper_row + i][middle_row + i - 1] = 0;
				if (h < height - 1 && i < width - 1)
					matrix[middle_row + i][lower_row + i] = matrix[lower_row + i][middle_row + i] = 0;
			}
		}
	}
}

#ifdef DEBUG
void print_adjacency_matrix(const vector< vector <unsigned char> >& matrix)
{
	for (int i = 0; i < matrix.size(); i++) {
		cout << i << ": ";
		for (int j = 0; j < matrix[i].size(); j++)
			if (matrix[i][j])
				cout << j << ' ';
		cout << endl;
	}
}
#endif

int find_cycles(int start, const vector< vector <unsigned char> >& matrix,
	set<int>& vertices, vector<vertex_state>& states, vector<int>& parents, int& max_cycle_length)
{
	int nr_cycles = 0;
	states[start] = discovered;
	vertices.erase(start);
	for (int i = 0; i < matrix[start].size(); i++)
		if (matrix[start][i]) {
			if (states[i] == initialized) {
				parents[i] = start;
				return nr_cycles + find_cycles(i, matrix, vertices, states, parents, max_cycle_length);
			}
			else if (states[i] == discovered) {
				if (parents[start] != -1 && parents[start] != i) { // a cycle is found
					nr_cycles++;
					int length = 1;
					for (int u = parents[start]; u != start && u != -1; u = parents[u]) {
						length++;
#ifdef DEBUG
						cout << u << ' ';
#endif
					}
#ifdef DEBUG
					cout << "\ncycle of length = " << length << " found at vertex " << start << endl;
#endif
					if (length > max_cycle_length)
						max_cycle_length = length;
				}
			}
		}
	states[start] = processed;
	return nr_cycles;
}

int find_cycles(const vector< vector <unsigned char> >& matrix, int& max_cycle_length)
{
/*
	do depth-first search until all of the vertices have been visited
	if a cycle is found, calculate its length by following back the parent chain
*/
	int nr_cycles = 0, nr_vertices = matrix.size();
	set<int> vertices;
	for (int i = 0; i < nr_vertices; i++)
		vertices.insert(i);
	while (!vertices.empty()) {
		vector<vertex_state> states(nr_vertices, initialized);
		vector<int> parents(nr_vertices, -1);
		nr_cycles += find_cycles(*vertices.begin(), matrix, vertices, states, parents, max_cycle_length);
	}
	return nr_cycles;
}

int main(int /* argc */, char** /* argv */)
{
	for (int nr_maze = 1; ; nr_maze++) {
		int width, height;
		cin >> width >> height;
		if (!width && !height)
			break;
		int nr_cycles = 0, max_cycle_length = 0;
		if (width && height) {
			int nr_squares = (2 * width - 1) * (height - 1) + (width - 1); // number of squares (lozenges) in the maze
			vector< vector<unsigned char> > matrix(nr_squares, vector<unsigned char>(nr_squares, 0));
			construct_adjacency_matrix(width, height, matrix);
#ifdef DEBUG
			print_adjacency_matrix(matrix);
#endif
			nr_cycles = find_cycles(matrix, max_cycle_length);
		}
		cout << "Maze #" << nr_maze <<":\n";
		if (nr_cycles)
			cout << nr_cycles << " Cycles; the longest has length " << max_cycle_length << ".\n\n";
		else
			cout << "There are no cycles.\n\n";
	}
	return 0;
}

