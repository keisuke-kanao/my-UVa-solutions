
/*
	1.6.7 Check the Check
	PC/UVa IDs: 110107/10196, Popularity: B, Success rate: average Level: 1

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10196_Check_the_Check.cpp
*/

#include <iostream>
#include <string>
using namespace std;

const int number_of_squares = 8;
const int number_of_kings = 2;

bool black_pawn_capture_white_king(int i, int j, int ki, int kj)
{
	return ki == i + 1 && (kj == j - 1 || kj == j + 1);
}

bool white_pawn_capture_black_king(int i, int j, int ki, int kj)
{
	return ki == i - 1 && (kj == j - 1 || kj == j + 1);
}

bool knight_capture_king(int i, int j, int ki, int kj)
{
	if ((ki == i - 2 || ki == i + 2) && (kj == j - 1 || kj == j + 1))
		return true;
	if ((ki == i - 1 || ki == i + 1) && (kj == j - 2 || kj == j + 2))
		return true;
	return false;
}

bool bishop_capture_king(char chessboard[number_of_squares][number_of_squares], int i, int j, int ki, int kj)
{
	for (int c = j - 1, r = i - 1; c >= 0; c--, r--) {
		if (ki == r && kj == c)
			return true;
		if (chessboard[r][c] != '.')
			break;
	}
	for (int c = j - 1, r = i + 1; c >= 0; c--, r++) {
		if (ki == r && kj == c)
			return true;
		if (chessboard[r][c] != '.')
			break;
	}
	for (int c = j + 1, r = i - 1; c < number_of_squares; c++, r--) {
		if (ki == r && kj == c)
			return true;
		if (chessboard[r][c] != '.')
			break;
	}
	for (int c = j + 1, r = i + 1; c < number_of_squares; c++, r++) {
		if (ki == r && kj == c)
			return true;
		if (chessboard[r][c] != '.')
			break;
	}
	return false;
}

bool rook_capture_king(char chessboard[number_of_squares][number_of_squares], int i, int j, int ki, int kj)
{
	if (ki == i) {
		for (int c = j - 1; c >= 0; c--) {
			if (kj == c)
				return true;
			if (chessboard[i][c] != '.')
				break;
		}
		for (int c = j + 1; c < number_of_squares; c++) {
			if (kj == c)
				return true;
			if (chessboard[i][c] != '.')
				break;
		}
		return false;
	}
	if (kj == j) {
		for (int r = i - 1; r >= 0; r--) {
			if (ki == r)
				return true;
			if (chessboard[r][j] != '.')
				break;
		}
		for (int r = i + 1; r < number_of_squares; r++) {
			if (ki == r)
				return true;
			if (chessboard[r][j] != '.')
				break;
		}
		return false;
	}
	return false;
}

bool queen_capture_king(char chessboard[number_of_squares][number_of_squares], int i, int j, int ki, int kj)
{
	return bishop_capture_king(chessboard, i, j, ki, kj) || rook_capture_king(chessboard, i, j, ki, kj);
}

int capture_king(char chessboard[number_of_squares][number_of_squares], int bki, int bkj, int wki, int wkj)
{
	int result = 0; // zero if no king is in check, -1 if black king is in check, 1 if white king is in check
	for (int i = 0; i < number_of_squares; i++)
		for (int j = 0; j < number_of_squares; j++) {
			switch (chessboard[i][j]) {
			case 'p':
				result = (black_pawn_capture_white_king(i, j, wki, wkj)) ? 1 : 0;
#ifdef DEBUG
				if (result)
					cout << "\tblack pawn (" << i << ", " << j << ") captures white king (" << wki  << ", " << wkj << ")\n";
#endif
				break;
			case 'P':
				result = (white_pawn_capture_black_king(i, j, bki, bkj)) ? -1 : 0;
#ifdef DEBUG
				if (result)
					cout << "\twhite pawn (" << i << ", " << j << ") captures black king (" << bki  << ", " << bkj << ")\n";
#endif
				break;
			case 'n':
				result = (knight_capture_king(i, j, wki, wkj)) ? 1 : 0;
#ifdef DEBUG
				if (result)
					cout << "\tblack knight (" << i << ", " << j << ") captures white king (" << wki  << ", " << wkj << ")\n";
#endif
				break;
			case 'N':
				result = (knight_capture_king(i, j, bki, bkj)) ? -1 : 0;
#ifdef DEBUG
				if (result)
					cout << "\twhite knight (" << i << ", " << j << ") captures black king (" << bki  << ", " << bkj << ")\n";
#endif
				break;
			case 'b':
				result = (bishop_capture_king(chessboard, i, j, wki, wkj)) ? 1 : 0;
#ifdef DEBUG
				if (result)
					cout << "\tblack bishop (" << i << ", " << j << ") captures white king (" << wki  << ", " << wkj << ")\n";
#endif
				break;
			case 'B':
				result = (bishop_capture_king(chessboard, i, j, bki, bkj)) ? -1 : 0;
#ifdef DEBUG
				if (result)
					cout << "\twhite bishop (" << i << ", " << j << ") captures black king (" << bki  << ", " << bkj << ")\n";
#endif
				break;
			case 'r':
				result = (rook_capture_king(chessboard, i, j, wki, wkj)) ? 1 : 0;
#ifdef DEBUG
				if (result)
					cout << "\tblack rook (" << i << ", " << j << ") captures white king (" << wki  << ", " << wkj << ")\n";
#endif
				break;
			case 'R':
				result = (rook_capture_king(chessboard, i, j, bki, bkj)) ? -1 : 0;
#ifdef DEBUG
				if (result)
					cout << "\twhite rook (" << i << ", " << j << ") captures black king (" << bki  << ", " << bkj << ")\n";
#endif
				break;
			case 'q':
				result = (queen_capture_king(chessboard, i, j, wki, wkj)) ? 1 : 0;
#ifdef DEBUG
				if (result)
					cout << "\tblack queen (" << i << ", " << j << ") captures white king (" << wki  << ", " << wkj << ")\n";
#endif
				break;
			case 'Q':
				result = (queen_capture_king(chessboard, i, j, bki, bkj)) ? -1 : 0;
#ifdef DEBUG
				if (result)
					cout << "\twhite queen (" << i << ", " << j << ") captures black king (" << bki  << ", " << bkj << ")\n";
#endif
				break;
			}
			if (result)
				return result;
		}
	return result;
}

int main(int /* argc */, char** /* argv */)
{
	char chessboard[number_of_squares][number_of_squares];
	int bki, bkj, wki, wkj; // the row and column pairs of the two kings

	for (int n = 1; ; n++) {
		bki = bkj = wki = wkj = -1; // mark as not found
		string line;
		for (int i = 0; i < number_of_squares; i++) { // read the squares
			getline(cin, line);
			for (int j = 0; j < number_of_squares; j++) {
				chessboard[i][j] = line[j];
				if (line[j] == 'k') { // black king
					bki = i; bkj = j;
				}
				else if (line[j] == 'K') { // white king
					wki = i; wkj = j;
				}
			}
		}
		if (bki == -1)
			break;
		cout << "Game #" << n;
		// see if the piece can capture the king of the opponent
		switch (capture_king(chessboard, bki, bkj, wki, wkj)) {
		case 0:
			cout << ": no king is in check.\n";
			break;
		case -1:
			cout << ": black king is in check.\n";
			break;
		case 1:
			cout << ": white king is in check.\n";
			break;
		}
		getline(cin, line); // skip a blank line
	}
	return 0;
}

