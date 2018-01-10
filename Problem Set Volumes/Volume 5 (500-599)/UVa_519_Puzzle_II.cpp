
/*
	UVa 519 - Puzzle (II)

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_519_Puzzle_II.cpp

	from ACM Central European Regionals 1997 Problem F
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_EU_CERC/1997/index.html)
*/

#include <cstdio>
#include <cstring>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif

enum {s_reserved, s_jut, s_cavity, s_flat};
/*
	A piece is represented by an unsigned char, where:
		bit 6 - 7: top side
		bit 4 - 5: right side
		bit 2 - 3: bottom side
		bit 0 - 1: left side
	and each two-bits have the value of s_flat (0), s_jut (1), or s_cavity (2).
*/
const int nr_sides = 4, nr_rows_max = 6, nr_columns_max = 6;

int nr_rows, nr_columns;
unsigned char pieces[nr_rows_max][nr_columns_max];
	// pieces[i][j] is the value of the piece for i-th row and j-th coloumn, or 0 if not occupied yet

/*
	Four edge pieces are placed to pieces[0][0], pieces[0][m - 1], pieces[n - 1][0], pieces[n - 1][m - 1].
	Divide the other pieces into the following candidate sets:
		top side pieces (the number of which is at most m - 2)
		right side pieces (the number of which is at most n - 2)
		bottom side pieces (the number of which is at most m - 2)
		left side pieces (the number of which is at most n - 2)
		internal pieces (the number of which is at most (n - 2) * (m - 2)):
			further divide these pieces into 4 sets, depending on both the top and left side types.
*/

struct piece_candidates {
	int nr_candidates_; // number of candidates
	int used_; // i-th bit is set if i-th candidates has already been assmbled
	unsigned char candidates_[(nr_rows_max - 2) * (nr_columns_max - 2)];
};

piece_candidates top_side_candidates, right_side_candidates, bottom_side_candidates, left_side_candidates;
	// candidates for top/right/bottm/left sides
piece_candidates internal_candidates[4];
/*
	Internal pieces are divided into 4 sets, depending on both the top and the left side forms.
		internal_candidates[0] for jut top and jut left
		internal_candidates[1] for jut top and cavity left
		internal_candidates[2] for cavity top and jut left
		internal_candidates[3] for cavity top and cavity left
*/

bool put_edge_piece(int row, int columns, unsigned char p)
{
	if (pieces[row][columns])
		return false;
	pieces[row][columns] = p;
	return true;
}

bool add_candidate_piece(piece_candidates& candidates, int nr_candidates_max, unsigned char p)
{
	if (candidates.nr_candidates_ > nr_candidates_max)
		return false;
	candidates.candidates_[candidates.nr_candidates_++] = p;
	return true;
}

bool sort_out_piece(unsigned char p)
{
	if ((p & 0xc3) == 0xc3) { // top left edge
		if (nr_rows == 1 && (p & 0x0c) != 0x0c || nr_columns == 1 && (p & 0x30) != 0x30)
			return false;
		return put_edge_piece(0, 0, p);
	}
	else if ((p & 0xf0) == 0xf0) { // top right edge
		if (nr_rows == 1 && (p & 0x0c) != 0x0c || nr_columns == 1)
			return false;
		return put_edge_piece(0, nr_columns - 1, p);
	}
	else if ((p & 0x3c) == 0x3c) { // bottom right edge
		if (nr_rows == 1 || nr_columns == 1 && (p & 0x03) != 0x03)
			return false;
		return put_edge_piece(nr_rows - 1, nr_columns - 1, p);
	}
	else if ((p & 0x0f) == 0x0f) { // bottom left edge
		if (nr_rows == 1 || nr_columns == 1)
			return false;
		return put_edge_piece(nr_rows - 1, 0, p);
	}
	else if ((p & 0xc0) == 0xc0) { // top sides
		if (nr_rows == 1 && (p & 0x0c) != 0x0c)
			return false;
		return add_candidate_piece(top_side_candidates, nr_columns - 2, p);
	}
	else if ((p & 0x03) == 0x03) { // left side
		if (nr_columns == 1 && (p & 0x30) != 0x30)
			return false;
		return add_candidate_piece(left_side_candidates, nr_rows - 2, p);
	}
	else if ((p & 0x0c) == 0x0c) // bottom side
		return add_candidate_piece(bottom_side_candidates, nr_columns - 2, p);
	else if ((p & 0x30) == 0x30) // right side
		return add_candidate_piece(right_side_candidates, nr_rows - 2, p);
	else { // internal pieces
		unsigned char left = p & 0x03, top = (p & 0xc0) >> 6;
		int i = (left - 1) + (top - 1) * 2;
		return add_candidate_piece(internal_candidates[i], (nr_rows - 2) * (nr_columns - 2), p);
	}
}

bool match_top_bottom_pieces(unsigned char t, unsigned char b)
{
	unsigned char bottom = (t & 0x0c) >> 2, top = (b & 0xc0) >> 6;
	return bottom == s_jut && top == s_cavity || bottom == s_cavity && top == s_jut;
}

bool match_left_right_pieces(unsigned char l, unsigned char r)
{
	unsigned char right = (l & 0x30) >> 4, left = r & 0x03;
	return right == s_jut && left == s_cavity || right == s_cavity && left == s_jut;
}

bool arrange_pieces(int r, int c);

bool arrange_side_pieces(int r, int c, piece_candidates& candidates)
{
	bool successful = false;
	for (int i = 0, j = 1; i < candidates.nr_candidates_; i++, j <<= 1) {
		if (candidates.used_ & j)
			continue;
		if ((!c || match_left_right_pieces(pieces[r][c - 1], candidates.candidates_[i])) &&
			(!r || match_top_bottom_pieces(pieces[r - 1][c], candidates.candidates_[i]))) {
			candidates.used_ |= j;
			pieces[r][c] = candidates.candidates_[i];
			int nr, nc;
			if (c == nr_columns - 1) {
				nr = r + 1; nc = 0;
			}
			else {
				nr = r; nc = c + 1;
			}
			successful = arrange_pieces(nr, nc);
			candidates.used_ &= ~j;
			if (successful)
				return successful;
		}
	}
	return successful;
}

bool arrange_internal_pieces(int r, int c)
{
	bool successful = false;
	unsigned char right = (pieces[r][c - 1] & 0x30) >> 4, bottom = (pieces[r - 1][c] & 0x0c) >> 2;
	int left = (right == s_jut) ? s_cavity : s_jut, top = (bottom == s_jut) ? s_cavity : s_jut;
	int ci = (left - 1) + (top - 1) * 2;
	piece_candidates& candidates = internal_candidates[ci];
	for (int i = 0, j = 1; i < candidates.nr_candidates_; i++, j <<= 1)
		if (!(candidates.used_ & j)) {
			candidates.used_ |= j;
			pieces[r][c] = candidates.candidates_[i];
			successful = arrange_pieces(r, c + 1);
			candidates.used_ &= ~j;
			if (successful)
				return successful;
		}
	return successful;
}

bool arrange_pieces(int r, int c)
{
	if (r == nr_rows)
		return true;
	else if (c == nr_columns)
		return arrange_pieces(r + 1, 0);
	else if (!r) {
		if (!c) // top left edge
			return arrange_pieces(r, c + 1);
		else if (c == nr_columns - 1) // top right edge
			return (match_left_right_pieces(pieces[r][c - 1], pieces[r][c])) ?
				arrange_pieces(r, c + 1) : false;
		else
			return arrange_side_pieces(r, c, top_side_candidates);
	}
	else if (r == nr_rows - 1) {
		if (!c) // bottom left edge
			return (match_top_bottom_pieces(pieces[r - 1][c], pieces[r][c])) ?
				arrange_pieces(r, c + 1) : false;
		else if (c == nr_columns - 1) // bottom right edge
			return (match_left_right_pieces(pieces[r][c - 1], pieces[r][c]) &&
				match_top_bottom_pieces(pieces[r - 1][c], pieces[r][c])) ?
				arrange_pieces(r, c + 1) : false;
		else
			return arrange_side_pieces(r, c, bottom_side_candidates);
	}
	else {
		if (!c) // left side
			return arrange_side_pieces(r, c, left_side_candidates);
		else if (c == nr_columns - 1) // right side
			return arrange_side_pieces(r, c, right_side_candidates);
		else {
			return arrange_internal_pieces(r, c);
		}
	}
}

#ifdef DEBUG
void print_pieces()
{
	char ps[nr_sides + 1];
	ps[nr_sides] = '\0';
	for (int i = 0; i < nr_rows; i++)
		for (int j = 0; j < nr_columns; j++) {
			unsigned char p = pieces[i][j];
			for (int k = 0; k < nr_sides; k++, p >>= 2) {
				char c;
				switch (p & 0x03) {
				case s_jut:
					c = 'O'; break;
				case s_cavity:
					c = 'I'; break;
				default:
					c = 'F'; break;
				}
				ps[nr_sides - k - 1] = c;
			}
			printf("%s%c", ps, ((j == nr_columns - 1) ? '\n' : ' '));
		}
}
#endif

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	while (true) {
		scanf("%d %d", &nr_rows, &nr_columns);
		if (!nr_rows && !nr_columns)
			break;
		int nr_pieces = nr_rows * nr_columns;
		bool yes = true;
		memset(pieces, 0, sizeof(pieces));
		memset(&top_side_candidates, 0, sizeof(top_side_candidates));
		memset(&right_side_candidates, 0, sizeof(right_side_candidates));
		memset(&bottom_side_candidates, 0, sizeof(bottom_side_candidates));
		memset(&left_side_candidates, 0, sizeof(left_side_candidates));
		for (int i = 0; i < 4; i++)
			memset(&internal_candidates[i], 0, sizeof(internal_candidates[0]));
		for (int i = 0; i < nr_pieces; i++) {
			char ps[nr_sides + 1];
			scanf("%s", ps);
			if (!yes)
				continue;
			unsigned char p = 0;
			for (int j = 0; j < nr_sides; j++) {
				if (j)
					p <<= 2;
				p |= (ps[j] == 'O') ? s_jut : ((ps[j] == 'I') ? s_cavity : s_flat);
			}
			yes = sort_out_piece(p);
		}
		if (yes)
			yes = arrange_pieces(0, 0);
		printf((yes) ?"YES\n" : "NO\n");
#ifdef DEBUG
		if (yes)
			print_pieces();
#endif
	}
#ifdef __ELAPSED_TIME__
	fprintf(stderr, "elapsed time = %lf sec.\n", static_cast<double>(clock() - start) / CLOCKS_PER_SEC);
#endif
	return 0;
}

