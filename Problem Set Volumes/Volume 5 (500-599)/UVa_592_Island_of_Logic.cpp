
/*
	UVa 592 - Island of Logic

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_592_Island_of_Logic.cpp

	from ACM Western and Southwestern European Regionals 1997
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_EU_SWERC/1997/index.html)
*/

/*
Details for a few cases:

1
A: I am divine.

	day/night	A		deducible
	--------------------------------
	d			d(ivine)	o
	d			e(vil)		o
	d			h(uman)		x
	n			d			x
	n			e			o
	n			h			o

	day or night, A = divine or evil or human

1
A: I am lying.

	day/night	A		deducible
	--------------------------------
	d			d(ivine)	x
	d			e(vil)		x
	d			h(uman)		x
	n			d			x
	n			e			x
	n			h			x

	impossible

2
D: E is human.
D: E is evil.

	day/night	D			E		deducible
	--------------------------------------------
	d			d(ivine)	d			x
	d			d			e(vil)		x
	d			d			h(uman)		x
	d			e			d			o
	d			e			e			x
	d			e			h			x
	d			h			d			x
	d			h			e			x
	d			h			h			x

	n			d(ivine)	d			x
	n			d			e(vil)		x
	n			d			h(uman)		x
	n			e			d			o
	n			e			e			x
	n			e			h			x
	n			h			d			o
	n			h			e			x
	n			h			h			x

	day or night, D = evil or human, E = divine

3
E: I am not human.
D: E is evil.
D: It is day.

	day/night	D			E		deducible
	--------------------------------------------
	d			d(ivine)	d			x
	d			d			e(vil)		x
	d			d			h(uman)		x
	d			e			d			x
	d			e			e			x
	d			e			h			x
	d			h			d			x
	d			h			e			x
	d			h			h			x

	n			d(ivine)	d			x
	n			d			e(vil)		x
	n			d			h(uman)		x
	n			e			d			o
	n			e			e			x
	n			e			h			o
	n			h			d			o
	n			h			e			x
	n			h			h			o

	night		D = evil or human, E = divine or human
*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstring>
using namespace std;

const int nr_speakers_max = 'E' - 'A' + 1;
enum {unknown = -1, divine, evil, human};
enum {day, night};
enum {divine_deduced = 1 << divine, evil_deduced = 1 << evil, human_deduced = 1 << human};
enum {day_deduced = 1 << day, night_deduced = 1 << night};

bool is_correct_statement(int day_or_night, const vector<int>& speakers, const char* p)
{
	int referrer = speakers[*p - 'A'];
	p += 3;
	if (*p == 'I' && *(p + 1) == 't') { // "It is ..."
		p += 6;
		if (!strncmp(p, "day", strlen("day")))
			return day_or_night == day;
		else // "night."
			return day_or_night == night;
	}
	else {
		int referred = (*p == 'I') ? referrer : speakers[*p - 'A'];
		p += 5;
		if (!strncmp(p, "divine", strlen("divine")))
			return referred == divine;
		else if (!strncmp(p, "evil", strlen("evil")))
			return referred == evil;
		else if (!strncmp(p, "human", strlen("human")))
			return referred == human;
		else if (!strncmp(p, "lying", strlen("lying")))
			return referred == evil || referred == human && day_or_night == night;
		else if (!strncmp(p, "not divine.", strlen("not divine")))
			return referred != divine;
		else if (!strncmp(p, "not evil", strlen("not evil")))
			return referred != evil;
		else if (!strncmp(p, "not human", strlen("not human")))
			return referred != human;
		else // "not lying."
			return referred == divine || referred == human && day_or_night == day;
	}
}

bool are_statements_deducible(int day_or_night, const vector<int>& speakers, const vector< vector<string> >& statements)
{
	for (int i = 0; i < nr_speakers_max; i++)
		if (speakers[i] != -1) {
			for (size_t j = 0; j < statements[i].size(); j++) {
				if (speakers[i] == divine || speakers[i] == human && day_or_night == day) {
					if (!is_correct_statement(day_or_night, speakers, statements[i][j].c_str()))
						return false;
				}
				else { // speakers[i] == evil || speaker[i] == human && day_or_night == night
					if (is_correct_statement(day_or_night, speakers, statements[i][j].c_str()))
						return false;
				}
			}
		}
	return true;
}

void deduce_inhabitants(int day_or_night, int si, vector<int>& speakers, const vector< vector<string> >& statements,
	int& deduced_day_or_night, vector<int>& deduced_speakers)
{
	while (si < nr_speakers_max && speakers[si] == -1)
		si++;
	if (si < nr_speakers_max) {
		for (int i = divine; i <= human; i++) {
			speakers[si] = i;
			deduce_inhabitants(day_or_night, si + 1, speakers, statements, deduced_day_or_night, deduced_speakers);
		}
	}
	else {
		if (are_statements_deducible(day_or_night, speakers, statements)) {
			// record the deduced facts (day or night, inhabitant types)
			deduced_day_or_night |= 1 << day_or_night;
			for (int i = 0; i < nr_speakers_max; i++)
				if (speakers[i] != -1)
					deduced_speakers[i] |= 1 << speakers[i];
		}
	}
}

int main()
{
	for (int c = 1; ; c++) {
		string line;
		getline(cin, line);
		istringstream iss(line);
		int n;
		iss >> n;
		iss.clear();
		if (!n)
			break;
		vector<int> speakers(nr_speakers_max, -1);
			// speakers[i] is the type of ('A' + i)-th speaker, or -1 if not appeared
		vector<int> deduced_speakers(nr_speakers_max, -1);
			// deduced_speakers[i] is the deduced type(s) of ('A' + i)-th speaker, or -1 if not appeared
		vector< vector<string> > statements(nr_speakers_max);
			// statements[i] is the vector of ('A' + i)-th statesments
		for (int i = 0; i < n; i++) {
			getline(cin, line);
			int referrer = line[0] - 'A';
			speakers[referrer] = deduced_speakers[referrer] = 0;
			if (line[3] >= 'A' && line[3] <= 'E') {
				int referred = line[3] - 'A';
				speakers[referred] = deduced_speakers[referred] = 0;
			}
			statements[referrer].push_back(line);
		}
		int deduced_day_or_night = 0;
		deduce_inhabitants(day, 0, speakers, statements, deduced_day_or_night, deduced_speakers);
		deduce_inhabitants(night, 0, speakers, statements, deduced_day_or_night, deduced_speakers);
		cout << "Conversation #" << c << endl;
		int nr_deduced = 0, nr_facts = 0;
		for (int i = 0; i < nr_speakers_max; i++) {
			int referrer = deduced_speakers[i];
			if (referrer != -1) {
				if (referrer == divine_deduced || referrer == evil_deduced || referrer == human_deduced) {
					nr_facts++; nr_deduced++;
					cout << static_cast<char>(i + 'A') << " is " <<
						((referrer == divine_deduced) ? "divine.\n" :
						((referrer == evil_deduced) ? "evil.\n" : "human.\n"));
				}
				else if (referrer)
					nr_deduced++;
			}
		}
		if (deduced_day_or_night) {
			nr_deduced++;
			if (deduced_day_or_night == day_deduced || deduced_day_or_night == night_deduced) {
				nr_facts++;
				cout << "It is " << ((deduced_day_or_night == day_deduced) ? "day.\n" : "night.\n");
			}
		}
		if (!nr_deduced)
			cout << "This is impossible.\n";
		else if (!nr_facts)
			cout << "No facts are deducible.\n";
		cout << endl;
	}
	return 0;
}

