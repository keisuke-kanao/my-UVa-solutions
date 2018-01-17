
/*
	3.8.8 Fmt
	PC/UVa IDs: 110308/848, Popularity: C, Success rate: low Level: 2

	To build using Visucal Studio 2008:
		cl -EHsc UVa_848_Fmt.cpp
*/

#include <iostream>
#include <string>
using namespace std;

const int max_char_per_line = 72; // max. number of characters per line

string pretrim_string(const string& s) // trim the spaces from the beginning of s
{
	int i = 0;
	while (i < s.length() && s[i] == ' ')
		i++;
	return s.substr(i);
}
string trim_string(const string& s) // trim the spaces from the end of s
{
	int i = s.length() - 1;
	while (i >= 0 && s[i] == ' ')
		i--;
	return s.substr(0, i + 1);
}
void print_line(const string& line) // check s for any non-blank characters, and ignore if none found. print o/w.
{
	bool non_blank_chars = false;
	for (int i = 0; i < line.length(); i++)
		if (line[i] != ' ') {
			non_blank_chars = true;
			break;
		}
	if (non_blank_chars)
		cout << trim_string(line) << endl;
}
int main(int /* argc */, char** /* argv */)
{
	string line, formatted_line;
	while (getline(cin, line)) {
		bool blank_line = true;
		for (int i = 0; i < line.length(); i++) // see if the line is a blank/empty one
			if (line[i] != ' ' && line[i] != '\t') {
				blank_line = false;
				break;
			}
		if (blank_line) {
			print_line(formatted_line);
			formatted_line.clear();
			cout << line << endl;
			continue;
		}
		if (line.length()>0&&line[0] == ' ') { // if the line starts with a  space, start a new formatted line
			print_line(formatted_line);
			formatted_line.clear();
		}
		// see if continuing an existing formatted line with a new input line
		bool concatenate_line = false;
		if (formatted_line.length() > 0) {
			formatted_line += " "; // replace the previous '\n' with ' '
			concatenate_line = true;
		}
		// greedily fit the line into the formatted line(s)
		int start = 0; // index to the last space ever found
		for (int i = 0; i < line.length(); i++) {
			if (line[i] == ' ') {
				if (formatted_line.length() + (i - start) <= max_char_per_line) {
					if ((start > 0 || concatenate_line) && formatted_line.length() == 0)
						formatted_line += pretrim_string(line.substr(start, (i - start)));
					else
						formatted_line += line.substr(start, (i - start));
				}
				else {
					if (!formatted_line.empty())
						cout << trim_string(formatted_line) << endl;
					formatted_line = pretrim_string(line.substr(start, (i - start)));
				}
				start = i;
			}
			else if (i == line.length() - 1) { // a boundary case for the end of line
				if (formatted_line.length() + (i - start + 1) <= max_char_per_line) {
					if ((start > 0 || concatenate_line) && formatted_line.length() == 0)
						formatted_line += pretrim_string(line.substr(start));
					else
						formatted_line += line.substr(start);
				}
				else {
					print_line(formatted_line);
					formatted_line = pretrim_string(line.substr(start));
				}
			}
		}
	}
	print_line(formatted_line);
	return 0;
}

