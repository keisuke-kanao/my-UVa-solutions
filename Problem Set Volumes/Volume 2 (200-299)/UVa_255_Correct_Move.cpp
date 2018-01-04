
/*
	UVa 255 - Correct Move

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_255_Correct_Move.cpp
*/

#include <iostream>
using namespace std;

const int dirs[][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
const size_t n = sizeof(dirs) / sizeof(dirs[0]);

bool is_legal(int kr, int kc, int qr, int qc, int nqr, int nqc)
{
	if (qr == nqr && qc == nqc)
		return false;
	if (qr == nqr)
		return (kr == qr && (kc > qc && kc <= nqc || kc >= nqc && kc < qc)) ? false : true;
	else if (qc == nqc)
		return (kc == qc && (kr > qr && kr <= nqr || kr >= nqr && kr < qr)) ? false : true;
	else
		return false;
}

bool is_allowed(int kr, int kc, int qr, int qc)
{
	for (size_t i = 0; i < n; i++) {
		int nkr = kr + dirs[i][0], nkc = kc + dirs[i][1];
		if (nkr < 0 || nkr >= 8 || nkc < 0 || nkc >= 8)
			;
		else if (nkr == qr && nkc == qc)
			return false;
	}
	return true;
}

bool is_continue(int kr, int kc, int qr, int qc)
{
	int legal = 0, allowed = 0;
	for (size_t i = 0; i < n; i++) {
		int nkr = kr + dirs[i][0], nkc = kc + dirs[i][1];
		if (nkr < 0 || nkr >= 8 || nkc < 0 || nkc >= 8)
			;
		else {
			legal++;
			if (nkr == qr || nkc == qc)
				allowed++;
		}
	}
	return legal > allowed;
}

int main()
{
	int k, q, nq;
	while (cin >> k >> q >> nq) {
		if (k == q)
			cout << "Illegal state\n";
		else {
			int kr = k / 8, kc = k % 8, qr = q / 8, qc = q % 8, nqr = nq / 8, nqc = nq % 8;
			if (is_legal(kr, kc, qr, qc, nqr, nqc)) {
				if (!is_allowed(kr, kc, nqr, nqc))
					cout << "Move not allowed\n";
				else if (is_continue(kr, kc, nqr, nqc))
					cout << "Continue\n";
				else
					cout << "Stop\n";
			}
			else
				cout << "Illegal move\n";
		}
	}
	return 0;
}

