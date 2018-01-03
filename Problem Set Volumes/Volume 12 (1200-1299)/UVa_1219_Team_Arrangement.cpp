
/*
	UVa 1219 - Team Arrangement

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1219_Team_Arrangement.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

const int nr_players = 22, nr_chars_max = 31;

struct player {
	int nr_;
	char name_[nr_chars_max + 1];
	char role_;
	int record_;
} players[nr_players];

int nr_Gs, nr_Ds, nr_Ms, nr_Ss, nr_team_Ds, nr_team_Ms, nr_team_Ss;

int Gs[nr_players], Ds[nr_players], Ms[nr_players], Ss[nr_players];

bool read_players()
{
	string s;
	nr_Gs = nr_Ds = nr_Ms = nr_Ss = 0;
	for (int i = 0; i < nr_players; i++) {
		getline(cin, s);
		istringstream iss(s);
		player& p = players[i];
		iss >> p.nr_;
		if (!p.nr_)
			return false;
		iss >> p.name_ >> p.role_;
		switch (p.role_) {
		case 'G':
			Gs[nr_Gs++] = i; break;
		case 'D':
			Ds[nr_Ds++] = i; break;
		case 'M':
			Ms[nr_Ms++] = i; break;
		case 'S':
			Ss[nr_Ss++] = i; break;
		}
		int year1, year2;
		char c;
		p.record_ = 0;
		while (iss >> year1 >> c >> year2)
			p.record_ += year2 - year1 + 1;
#ifdef DEBUG
		cout << p.nr_ << ' ' << p.name_ << ' ' << p.role_ << ' ' << p.record_ << endl;
#endif
	}
	getline(cin, s);
	istringstream iss(s);
	char c;
	iss >> nr_team_Ds >> c >> nr_team_Ms >> c >> nr_team_Ss;
	return true;
}

bool compare_player(int i, int j)
{
	return players[i].nr_ < players[j].nr_;
}

void print_player(int i)
{
	const player& p = players[i];
	cout << p.nr_ << ' ' << p.name_ << ' ' << p.role_ << endl;
}

int main()
{
	while (read_players()) {
		if (!nr_Gs || nr_Ds < nr_team_Ds || nr_Ms < nr_team_Ms || nr_Ss < nr_team_Ss) {
			cout << "IMPOSSIBLE TO ARRANGE\n\n";
			continue;
		}
		sort(Gs, Gs + nr_Gs, compare_player);
		sort(Ds, Ds + nr_Ds, compare_player);
		sort(Ms, Ms + nr_Ms, compare_player);
		sort(Ss, Ss + nr_Ss, compare_player);
		int captain = Gs[0];
		int nr = players[captain].nr_, record = players[captain].record_;
		for (int i = 0; i < nr_team_Ds; i++) {
			int j = Ds[i];
			const player& p = players[j];
			if (p.record_ > record  || p.record_ == record && p.nr_ > nr) {
				captain = j;
				nr = p.nr_, record = p.record_;
			}
		}
		for (int i = 0; i < nr_team_Ms; i++) {
			int j = Ms[i];
			const player& p = players[j];
			if (p.record_ > record  || p.record_ == record && p.nr_ > nr) {
				captain = j;
				nr = p.nr_, record = p.record_;
			}
		}
		for (int i = 0; i < nr_team_Ss; i++) {
			int j = Ss[i];
			const player& p = players[j];
			if (p.record_ > record  || p.record_ == record && p.nr_ > nr) {
				captain = j;
				nr = p.nr_, record = p.record_;
			}
		}
		print_player(captain);
		if (Gs[0] != captain)
			print_player(Gs[0]);
		for (int i = 0; i < nr_team_Ds; i++)
			if (Ds[i] != captain)
				print_player(Ds[i]);
		for (int i = 0; i < nr_team_Ms; i++)
			if (Ms[i] != captain)
				print_player(Ms[i]);
		for (int i = 0; i < nr_team_Ss; i++)
			if (Ss[i] != captain)
				print_player(Ss[i]);
		cout << endl;
	}
	return 0;
}

