
/*
	UVa 291 - The House Of Santa Claus

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_291_The_House_Of_Santa_Claus.cpp
*/

#include <iostream>
using namespace std;

const int nr_vertices = 5;
bool edges[nr_vertices][nr_vertices] = { // edges[i][j] is true if there is an edge from i to j
	{false, true, true, false, true},
	{true, false, true, false, true},
	{true, true, false, true, true},
	{false, false, true, false, true},
	{true, true, true, true, false}
};
const int nr_edges = 8;
int vertices[nr_edges + 1];

void draw_the_house(int i, int e)
{
	if (e == nr_edges) {
		for (int i = 0; i <= nr_edges; i++)
			cout << vertices[i];
		cout << endl;
	}
	else {
		for (int j = 0; j < nr_vertices; j++)
			if (edges[i][j]) {
				vertices[e + 1] = j + 1;
				edges[i][j] = edges[j][i] = false;
				draw_the_house(j, e + 1);
				edges[i][j] = edges[j][i] = true;
			}
	}
}

int main()
{
	vertices[0] = 1;
	for (int i = 1; i < nr_vertices; i++)
		if (edges[0][i]) {
			vertices[1] = i + 1;
			edges[0][i] = edges[i][0] = false;
			draw_the_house(i, 1);
			edges[0][i] = edges[i][0] = true;
		}
	return 0;
}

