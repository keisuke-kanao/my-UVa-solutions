
/*
	UVa 10422 - Knights in FEN

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10422_Knights_in_FEN.cpp
*/

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

const int nr_rows = 5, nr_columns = 5;
const int nr_moves_max = 10;

void move_knights(int nr_moves, int& min_nr_moves, int psi, int psj, int si, int sj,
	char chessboard[nr_rows][nr_columns]);

void swap_space(int nr_moves, int& min_nr_moves, int psi, int psj, int si, int sj, int ki, int kj,
	char chessboard[nr_rows][nr_columns])
{
	if (ki < 0 || ki >= nr_rows || kj < 0 || kj >= nr_columns)
		;
 	else if (psi == ki && psj == kj)
		;
	else {
		swap(chessboard[si][sj], chessboard[ki][kj]);
		move_knights(nr_moves + 1, min_nr_moves, si, sj, ki, kj, chessboard);
		swap(chessboard[ki][kj], chessboard[si][sj]);
	}
}

int are_knights_at_final_positions(const char chessboard[nr_rows][nr_columns])
{
	const char final_positions[nr_rows][nr_columns] = {
		{'1', '1', '1', '1', '1'},
		{'0', '1', '1', '1', '1'},
		{'0', '0', ' ', '1', '1'},
		{'0', '0', '0', '0', '1'},
		{'0', '0', '0', '0', '0'}
	};
	int nr_differences = 0;
	for (int i = 0; i < nr_rows; i++)
		for (int j = 0; j < nr_columns; j++)
			if (chessboard[i][j] != final_positions[i][j])
				nr_differences++;
	return nr_differences;
}

void move_knights(int nr_moves, int& min_nr_moves, int psi, int psj, int si, int sj,
	char chessboard[nr_rows][nr_columns])
{
	if (nr_moves > nr_moves_max)
		return;
	int nr_differences = are_knights_at_final_positions(chessboard);
	if (!nr_differences) {
#ifdef DEBUG
	cout << "number of moves = " << nr_moves << endl;
#endif
		if (nr_moves < min_nr_moves)
			min_nr_moves = nr_moves;
		return;
	}
	else if (nr_differences - 2 > nr_moves_max - nr_moves)
		return; // no need to further search
	else {
		// from the current space position (si, sj), swap a knight with the space
 		swap_space(nr_moves, min_nr_moves, psi, psj, si, sj, si - 2, sj - 1, chessboard);
		swap_space(nr_moves, min_nr_moves, psi, psj, si, sj, si - 2, sj + 1, chessboard);
		swap_space(nr_moves, min_nr_moves, psi, psj, si, sj, si - 1, sj - 2, chessboard);
		swap_space(nr_moves, min_nr_moves, psi, psj, si, sj, si - 1, sj + 2, chessboard);
		swap_space(nr_moves, min_nr_moves, psi, psj, si, sj, si + 1, sj - 2, chessboard);
		swap_space(nr_moves, min_nr_moves, psi, psj, si, sj, si + 1, sj + 2, chessboard);
		swap_space(nr_moves, min_nr_moves, psi, psj, si, sj, si + 2, sj - 1, chessboard);
		swap_space(nr_moves, min_nr_moves, psi, psj, si, sj, si + 2, sj + 1, chessboard);
	}
}

int main()
{
	int n;
	cin >> n;
	string line;
	getline(cin, line); // skip '\n'
	while (n--) {
		char chessboard[nr_rows][nr_columns];
		int si, sj;
		for (int i = 0; i < nr_rows; i++) {
			getline(cin, line);
			for (int j = 0; j < nr_columns; j++) {
				chessboard[i][j] = line[j];
				if (chessboard[i][j] == ' ') {
					si = i; sj = j;
				}
			}
		}
		int min_mr_moves = nr_moves_max + 1;
		move_knights(0, min_mr_moves, -1, -1, si, sj, chessboard);
		if (min_mr_moves > nr_moves_max)
			cout << "Unsolvable in less than 11 move(s).\n";
		else
			cout << "Solvable in " << min_mr_moves <<" move(s).\n";
	}
	return 0;
}

