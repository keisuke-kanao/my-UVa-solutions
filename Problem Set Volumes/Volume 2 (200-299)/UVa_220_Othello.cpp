
/*
	UVa 220 - Othello

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_220_Othello.cpp
*/

#include <cstdio>

const int nr_squares = 8;
char board[nr_squares][nr_squares + 1];

bool is_other_disk(char disk, int r, int c)
{
	if (r < 0 || r >= nr_squares || c < 0 || c >= nr_squares)
		return false;
	return board[r][c] != '-' && disk != board[r][c];
}

bool is_leagal_move(char disk, int r, int c)
{
	if (is_other_disk(disk, r - 1, c)) // above squares
		for (int i = r - 2; i >= 0; i--) {
			if (board[i][c] == disk)
				return true;
			else if (board[i][c] == '-')
				break;
		}
	if (is_other_disk(disk, r + 1, c)) // below squares
		for (int i = r + 2; i < nr_squares; i++) {
			if (board[i][c] == disk)
				return true;
			else if (board[i][c] == '-')
				break;
		}
	if (is_other_disk(disk, r, c - 1)) // left squares
		for (int j = c - 2; j >= 0; j--) {
			if (board[r][j] == disk)
				return true;
			else if (board[r][j] == '-')
				break;
		}
	if (is_other_disk(disk, r, c + 1)) // rigtht squares
		for (int j = c + 2; j < nr_squares; j++) {
			if (board[r][j] == disk)
				return true;
			else if (board[r][j] == '-')
				break;
		}
	if (is_other_disk(disk, r - 1, c - 1)) // diagonally upper left squares
		for (int i = r - 2, j = c - 2; i >= 0 && j >= 0; i--, j--) {
			if (board[i][j] == disk)
				return true;
			else if (board[i][j] == '-')
				break;
		}
	if (is_other_disk(disk, r + 1, c - 1)) // diagonally lower left squares
		for (int i = r + 2, j = c - 2; i < nr_squares && j >= 0; i++, j--) {
			if (board[i][j] == disk)
				return true;
			else if (board[i][j] == '-')
				break;
		}
	if (is_other_disk(disk, r - 1, c + 1)) // diagonally upper rigtht squares
		for (int i = r - 2, j = c + 2; i >= 0 && j < nr_squares; i--, j++) {
			if (board[i][j] == disk)
				return true;
			else if (board[i][j] == '-')
				break;
		}
	if (is_other_disk(disk, r + 1, c + 1)) // diagonally lower right squares
		for (int i = r + 2, j = c + 2; i < nr_squares && j < nr_squares; i++, j++) {
			if (board[i][j] == disk)
				return true;
			else if (board[i][j] == '-')
				break;
		}
	return false;
}

bool print_leagal_moves(char disk)
{
	bool leagal = false;
	for (int r = 0; r < nr_squares; r++)
		for (int c = 0; c < nr_squares; c++)
			if (board[r][c] == '-' && is_leagal_move(disk, r, c)) {
				if (leagal)
					putchar(' ');
				leagal = true;
				printf("(%d,%d)", r + 1, c + 1);
			}
	if (leagal)
		putchar('\n');
	else
		puts("No legal move.");
	return leagal;
}

void move(char disk, int r, int c, int& nr_white, int& nr_black)
{
	board[r][c] = disk;
	int nr_changed = 0;
	if (is_other_disk(disk, r - 1, c)) // above squares
		for (int i = r - 2; i >= 0; i--) {
			if (board[i][c] == disk) {
				for (i++; i < r; i++, nr_changed++)
					board[i][c] = disk;
				break;
			}
			else if (board[i][c] == '-')
				break;
		}
	if (is_other_disk(disk, r + 1, c)) // below squares
		for (int i = r + 2; i < nr_squares; i++) {
			if (board[i][c] == disk) {
				for (i--; i > r; i--, nr_changed++)
					board[i][c] = disk;
				break;
			}
			else if (board[i][c] == '-')
				break;
		}
	if (is_other_disk(disk, r, c - 1)) // left squares
		for (int j = c - 2; j >= 0; j--) {
			if (board[r][j] == disk) {
				for (j++; j < c; j++, nr_changed++)
					board[r][j] = disk;
				break;
			}
			else if (board[r][j] == '-')
				break;
		}
	if (is_other_disk(disk, r, c + 1)) // rigtht squares
		for (int j = c + 2; j < nr_squares; j++) {
			if (board[r][j] == disk) {
				for (j--; j > c; j--, nr_changed++)
					board[r][j] = disk;
				break;
			}
			else if (board[r][j] == '-')
				break;
		}
	if (is_other_disk(disk, r - 1, c - 1)) // diagonally upper left squares
		for (int i = r - 2, j = c - 2; i >= 0 && j >= 0; i--, j--) {
			if (board[i][j] == disk) {
				for (i++, j++; i < r && j < c; i++, j++, nr_changed++)
					board[i][j] = disk;
				break;
			}
			else if (board[i][j] == '-')
				break;
		}
	if (is_other_disk(disk, r + 1, c - 1)) // diagonally lower left squares
		for (int i = r + 2, j = c - 2; i < nr_squares && j >= 0; i++, j--) {
			if (board[i][j] == disk) {
				for (i--, j++; i > r && j < c; i--, j++, nr_changed++)
					board[i][j] = disk;
				break;
			}
			else if (board[i][j] == '-')
				break;
		}
	if (is_other_disk(disk, r - 1, c + 1)) // diagonally upper rigtht squares
		for (int i = r - 2, j = c + 2; i >= 0 && j < nr_squares; i--, j++) {
			if (board[i][j] == disk) {
				for (i++, j--; i < r && j > c; i++, j--, nr_changed++)
					board[i][j] = disk;
				break;
			}
			else if (board[i][j] == '-')
				break;
		}
	if (is_other_disk(disk, r + 1, c + 1)) // diagonally lower right squares
		for (int i = r + 2, j = c + 2; i < nr_squares && j < nr_squares; i++, j++) {
			if (board[i][j] == disk) {
				for (i--, j--; i > r && j > c; i--, j--, nr_changed++)
					board[i][j] = disk;
				break;
			}
			else if (board[i][j] == '-')
				break;
		}

	if (disk == 'W') {
		nr_white += nr_changed + 1; nr_black -= nr_changed;
	}
	else {
		nr_white -= nr_changed; nr_black += nr_changed + 1;
	}
}

int main()
{
	int nr_games;
	scanf("%d", &nr_games);
	while (nr_games--) {
		for (int i = 0; i < nr_squares; i++)
			scanf("%s", board[i]);
		int nr_white = 0, nr_black = 0;
		for (int r = 0; r < nr_squares; r++)
			for (int c = 0; c < nr_squares; c++) {
				if (board[r][c] == 'W')
					nr_white++;
				else if (board[r][c] == 'B')
					nr_black++;
			}
		char command[4];
		scanf("%s", command);
		char disk = command[0];
		bool quit = false;
		while (!quit) {
			scanf("%s", command);
			switch (command[0]) {
			case 'L':
				if (!print_leagal_moves(disk))
					disk = (disk == 'W') ? 'B' : 'W';
				break;
			case 'M':
				move(disk, command[1] - '1', command[2] - '1', nr_white, nr_black);
				printf("Black - %2d White - %2d\n", nr_black, nr_white);
				disk = (disk == 'W') ? 'B' : 'W';
				break;
			default:
				quit = true;
				for (int i = 0; i < nr_squares; i++)
					puts(board[i]);
				break;
			}
		}
		if (nr_games)
			putchar('\n');
	}
	return 0;
}

