
/*
	3.8.5 Automated Judge Script
	PC/UVa IDs: 110305/10188, Popularity: B, Success rate: average Level: 1

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10188_Automated_Judge_Script.cpp
*/

#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
using namespace std;

bool read_solutions(string& solutions)
{
	string line;
	// read the number of solutions
	getline(cin, line);
	istringstream iss(line);
	int n;
	iss >> n;
	iss.clear();
	if (!n)
		return false;
	while (n--) { // read the solutions
		getline(cin, line);
		solutions += line;
		solutions += '\n';
	}
	return true;
}

bool is_accepted(const string& correct_solutions, const string& solutions)
{
	return correct_solutions == solutions;
}

bool compare_digits(const string& s, const string& t)
{
	int nr_non_numerics = 0;
	for (int i = 0, j = 0; i < s.length(); i++) {
		if (!isdigit(s[i])) {
			nr_non_numerics++; continue;
		}
		for ( ; j < t.length(); j++)
			if (isdigit(t[j]))
				break;
		if (j == t.length() || s[i] != t[j])
			return false;
		j++;
	}
	return (nr_non_numerics) ? true : false;
}

bool is_presentation_error(const string& correct_solutions, const string& solutions)
{
	return compare_digits(correct_solutions, solutions) && compare_digits(solutions, correct_solutions);
}

int main(int /* argc */, char** /* argv */)
{
	int x = 1;
	while (true) {
		// read the correct solutions
		string correct_solutions;
		if (!read_solutions(correct_solutions))
			break;
		string solutions;
		read_solutions(solutions);
		cout << "Run #" << x++;
		if (is_accepted(correct_solutions, solutions))
			cout << ": Accepted\n";
		else if (is_presentation_error(correct_solutions, solutions))
			cout << ": Presentation Error\n";
		else
			cout << ": Wrong Answer\n";
	}
	return 0;
}

