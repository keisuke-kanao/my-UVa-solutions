
/*
	UVa 10017 - The Never Ending Towers of Hanoi

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10017_The_Never_Ending_Towers_of_Hanoi.cpp
*/

#include <iostream>
#include <list>
using namespace std;

void print_peg(char p, const list<int>& l)
{
	cout << p << "=>";
	if (!l.empty()) {
		cout << "  ";
		for (list<int>::const_iterator i = l.begin(), e = l.end(); i != e; ++i)
			cout << ' ' << *i;
	}
	cout << endl;
}

void print_pegs(const list<int>& a, const list<int>& b, const list<int>& c)
{
	print_peg('A', a);
	print_peg('B', b);
	print_peg('C', c);
	cout << endl;
}

void move_between_pegs(list<int>& i, list<int>& j)
{
	if (i.empty()) {
		i.push_back(j.back()); j.pop_back();
	}
	else if (j.empty()) {
		j.push_back(i.back()); i.pop_back();
	}
	else if (i.back() > j.back()) {
		i.push_back(j.back()); j.pop_back();
	}
	else {
		j.push_back(i.back()); i.pop_back();
	}
}

void tower_of_hanoi_even_disks(list<int>& a, list<int>& b, list<int>& c, int m)
{
	while (true) {
		if (m--) {
			move_between_pegs(a, b); // make the legal move between pegs A and B
			print_pegs(a, b, c);
		}
		else
			break;
		if (m--) {
			move_between_pegs(a, c); // make the legal move between pegs A and C
			print_pegs(a, b, c);
		}
		else
			break;
		if (m--) {
			move_between_pegs(b, c); // make the legal move between pegs B and C
			print_pegs(a, b, c);
		}
		else
			break;
	}
}

void tower_of_hanoi_odd_disks(list<int>& a, list<int>& b, list<int>& c, int m)
{
	while (true) {
		if (m--) {
			move_between_pegs(a, c); // make the legal move between pegs A and C
			print_pegs(a, b, c);
		}
		else
			break;
		if (m--) {
			move_between_pegs(a, b); // make the legal move between pegs A and B
			print_pegs(a, b, c);
		}
		else
			break;
		if (m--) {
			move_between_pegs(b, c); // make the legal move between pegs C and B
			print_pegs(a, b, c);
		}
		else
			break;
	}
}

int main()
{
	for (int p = 1; ; p++) {
		int n, m;
		cin >> n >> m;
		if (!n && !m)
			break;
		cout << "Problem #" << p << endl << endl;
		list<int> a, b, c;
		for (int i = 1; i <= n; i++)
			a.push_front(i);
		print_pegs(a, b, c);
		if (n & 1)
			tower_of_hanoi_odd_disks(a, b, c, m);
		else
			tower_of_hanoi_even_disks(a, b, c, m);
	}
	return 0;
}

