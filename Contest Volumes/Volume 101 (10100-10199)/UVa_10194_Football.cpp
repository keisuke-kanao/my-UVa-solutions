
/*
	4.6.8 Football (aka Soccer)
	PC/UVa IDs: 110408/10194, Popularity: B, Success rate: average Level: 1

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10194_Football.cpp
*/

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cstring>
using namespace std;

struct team {
	string name;
	int points; // total points earned (3 points for win, 1 point for tie, 0 points for loss)
	int games; // number of games played
	int wins; // wins
	int ties; // ties
	int losses; // losses
	int goals_scored; // goals scored
	int goals_against; // goals against

	team() : points(0), games(0), wins(0), ties(0), losses(0), goals_scored(0), goals_against(0) {}
};

bool compare_team(const team& i, const team& j)
{
	if (i.points != j.points)
		return i.points > j.points;
	else if (i.wins != j.wins)
		return i.wins > j.wins;
	else if (i.goals_scored - i.goals_against != j.goals_scored - j.goals_against)
		return i.goals_scored - i.goals_against > j.goals_scored - j.goals_against;
	else if (i.goals_scored != j.goals_scored)
		return i.goals_scored > j.goals_scored;
	else if (i.games != j.games)
		return i.games < j.games;
	else
#ifdef __GNUC__
		return strcasecmp(i.name.c_str(), j.name.c_str()) < 0;
#else
		return stricmp(i.name.c_str(), j.name.c_str()) < 0;
#endif
}

#ifdef DEBUG
void print_teams(const vector<team>& teams)
{
	for (vector<team>::const_iterator i = teams.begin(); i != teams.end(); i++)
		cout << i->name << ": " << i->points << ", " << i->games << ", " <<
			i->wins << ", " << i->ties << ", " << i->losses << ", " <<
			i->goals_scored << ", " << i->goals_against << endl;
}
#endif

int main(int /* argc */, char** /* argv */)
{
	string line;
	istringstream iss;

	// read the number of tournaments
	if (!getline(cin, line))
		return 0;
	iss.str(line);
	int tournaments;
	iss >> tournaments;
	iss.clear();
	while (tournaments--) {
		// read a tournament name
		string tournament;
		getline(cin, tournament);
		// read the number of teams
		getline(cin, line);
		iss.str(line);
		int n;
		iss >> n;
		iss.clear();
		vector<team> teams;
		map<string, int> team_names; // key is a team name, value is the index to the vector of teams
		for (int i = 0; i < n; i++) { // read team names
			// for each team, generate a team structure and append it to the vector of teams
			team t;
			getline(cin, t.name);
			teams.push_back(t);
			team_names.insert(make_pair(t.name, i));
		}
#ifdef DEBUG
		print_teams(teams);
#endif
		// read the number of games
		getline(cin, line);
		iss.str(line);
		int games;
		iss >> games;
		iss.clear();
		while (games--) { // read the results of games
			getline(cin, line);
			iss.str(line);
			string name_1, name_2;
			int goals_1, goals_2;
			char c;
			getline(iss, name_1, '#');
			iss >> goals_1 >> c >> goals_2 >> c;
			getline(iss, name_2);
			iss.clear();
			team* t1 = &teams[team_names[name_1]];
			team* t2 = &teams[team_names[name_2]];
			t1->games++; t2->games++;
			if (goals_1 > goals_2) {
				t1->points += 3;
				t1->wins++; t2->losses++;
			}
			else if (goals_1 < goals_2) {
				t2->points += 3;
				t1->losses++; t2->wins++;
			}
			else {
				t1->points++; t2->points++;
				t1->ties++; t2->ties++;
			}
			t1->goals_scored += goals_1; t1->goals_against += goals_2;
			t2->goals_scored += goals_2; t2->goals_against += goals_1;
		}
		// stable sort the vector of teams by their results
		stable_sort(teams.begin(), teams.end(), compare_team);
#ifdef DEBUG
		print_teams(teams);
#endif
		cout << tournament << endl; // print the tournament name
		// print the standings
		int rank = 1;
		for (vector<team>::const_iterator i = teams.begin(); i != teams.end(); i++, rank++)
			cout << rank << ") " << i->name << ' ' << i->points << "p, " << i->games << "g (" <<
				i->wins << '-' << i->ties << '-' << i->losses << "), " <<
				i->goals_scored - i->goals_against << "gd (" << i->goals_scored << '-' << i->goals_against << ")\n";
		if (tournaments)
			cout << endl; // print a blank line between output sets
	}
	return 0;
}

