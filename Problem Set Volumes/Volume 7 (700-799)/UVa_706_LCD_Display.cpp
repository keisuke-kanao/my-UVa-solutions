
/*
	1.6.4 LCD Display
	PC/UVa IDs: 110104/706, Popularity: A, Success rate: average Level: 1

	To build using Visucal Studio 2008:
		cl -EHsc UVa_706_LCD_Display.cpp
*/

#include <iostream>
#include <string>
using namespace std;

const int s_max = 10, nc_max = 8;
const int rows_max = 2 * s_max + 3, columns_max = (s_max + 3) * nc_max;

void write_digit(int s, char n, int column, char displays[rows_max][columns_max])
{
	if (n != '1' && n != '4') // for the first row
		for (int i = 0; i < s; i++)
			displays[0][column + 1 + i] = '-';
	for (int i = 0; i < s; i++) { // for the 2nd to (s + 1)-th rows
		if (n >= '1' && n <= '3' || n == '7')
			;
		else
			displays[1 + i][column] = '|';
		if (n != '5' && n != '6')
			displays[1 + i][column + s + 1] = '|';
	}
	if (n != '0' && n != '1' && n != '7') // for the (s + 2)-th row
		for (int i = 0; i < s; i++)
			displays[s + 1][column + 1 + i] = '-';
	for (int i = 0; i < s; i++) { // for the (s + 3) to (s * 2 + 2)-th rows
		if (n == '0' || n == '2' || n == '6' || n == '8')
			displays[s + 2 + i][column] = '|';
		if (n != '2')
			displays[s + 2 + i][column + s + 1] = '|';
	}
	if (n != '1' && n != '4' && n != '7') // for the (s * 2 + 3)-th row
		for (int i = 0; i < s; i++)
			displays[s * 2 + 2][column + 1 + i] = '-';
}

int main(int /* argc */, char** argv)
{
	char displays[rows_max][columns_max];
	int s;
	while (cin >> s) {
		string numbers;
		cin >> numbers;
		if (!s && numbers == "0") // end of input
			break;
		int rows = s * 2 + 3, columns = (s + 2) * numbers.length() + numbers.length() - 1;
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < columns; j++)
				displays[i][j] = ' ';
		for (int i = 0; i < numbers.length(); i++)
			write_digit(s, numbers[i], (s + 3) * i, displays);
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++)
				cout << displays[i][j];
			cout << endl;
		}
		cout << endl;
	}
	return 0;
}

