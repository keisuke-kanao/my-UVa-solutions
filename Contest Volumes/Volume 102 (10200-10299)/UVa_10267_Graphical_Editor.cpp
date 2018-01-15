/*
	1.6.5 Graphical Editor
	PC/UVa IDs: 110105/10267, Popularity: B, Success rate: low Level: 1

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10267_Graphical_Editor.cpp
*/

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

const int row_max = 250, column_max = 250;

void fill(int c, int r, char old_color, char new_color,
	int m, int n, const char image[row_max][column_max], char filled_image[row_max][column_max]);

void fill(int c, int r, char old_color, char new_color,
	int m, int n, const char image[row_max][column_max], char filled_image[row_max][column_max])
{
	filled_image[r][c] = new_color;
	if (c && filled_image[r][c - 1] == -1 && image[r][c - 1] == old_color)
		fill(c - 1, r, old_color, new_color, m, n, image, filled_image);
	if (c < m - 1 && filled_image[r][c + 1] == -1 && image[r][c + 1] == old_color)
		fill(c + 1, r, old_color, new_color, m, n, image, filled_image);
	if (r && filled_image[r - 1][c] == -1 && image[r - 1][c] == old_color)
		fill(c, r - 1, old_color, new_color, m, n, image, filled_image);
	if (r < n - 1 && filled_image[r + 1][c] == -1 && image[r + 1][c] == old_color)
		fill(c, r + 1, old_color, new_color, m, n, image, filled_image);
}

int main(int /* argc */, char** /* argv */)
{
	char image[row_max][column_max], filled_image[row_max][column_max];
	string line;
	while (getline(cin, line)) {
		istringstream iss(line);
		char command, color, old_color;
		int m, n, x, x2, y, y2;
		string fname;
		iss >> command;
		if (command == 'X')
			break;
		switch (command) {
		case 'I': // create a new image
			iss >> m >> n;
			// fall through
		case 'C': // clear the image
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					image[i][j] = 'O';
			break;
		case 'L': // color the specified pixel
			iss >> x >> y >> color;
			image[y - 1][x - 1] = color;
			break;
		case 'S': // write the file name followed by the contents of the current image
			iss >> fname;
			cout << fname << endl;
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++)
					cout << image[i][j];
				cout << endl;
			}
			break;
		case 'V': // draw a vertical segment of the specified color
			iss >> x >> y >> y2 >> color;
			if (y > y2)
				swap(y, y2);
			for (int i = y - 1; i < y2; i++)
				image[i][x - 1] = color;
			break;
		case 'H': // draw a horizontal segment of the specified color
			iss >> x >> x2 >> y >> color;
			if (x > x2)
				swap(x, x2);
			for (int i = x - 1; i < x2; i++)
				image[y - 1][i] = color;
			break;
		case 'K': // draw a filled rectangle of the specified color
			iss >> x >> y >> x2 >> y2 >> color;
			for (int i = y - 1; i < y2; i++)
				for (int j = x - 1; j < x2; j++)
					image[i][j] = color;
			break;
		case 'F':
			// fill the region R with the specified color, where R is defined as follows:
			// The specified pixel belongs to R. Any other pixel which is the same color as the specifed one and 
			// shares a common side with any pixel in R also belongs to this region.
			iss >> x >> y >> color;
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					filled_image[i][j] = -1;
			x--; y--;
			old_color = image[y][x];
			fill(x, y, old_color, color, m, n, image, filled_image);
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					if (filled_image[i][j] != -1)
						image[i][j] = filled_image[i][j];
			break;
		default:
			break;
		}
	}
	return 0;
}

