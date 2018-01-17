
/*
	3.8.6 File Fragmentation
	PC/UVa IDs: 110306/10132, Popularity: C, Success rate: average Level: 2

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10132_File_Fragmentation.cpp
*/

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>
// #include <cassert>
#include <cstring>
using namespace std;

const int file_size_max = 256; // max. number of bytes in a file

// a pair of the file fragment of the same lengths, one is adjacent to one side, and the other is adjacent to the other side
typedef pair<string, string> fragment;

/*
	Create a multiple sets of fragments, each of which has the fragments of same length.

	When all of the fragments have been read, each set has at most two fragments and one 
	is (part of) the left side and the other is (part of the) right side of the original file.
*/

bool have_same_fragment(const string& fragment, const string& s) // see if fragment is a part of s
{
/*
	If fragment is adjacent to the left side, s[0] - s[fragment.lenth() - 1] should be equal.
	If fragment is adjecent to the right side, s[s.length() - fragment.length()] - s[s.length() - 1] should be equal.
*/
	int slength = s.length(), flength = fragment.length();
	if (!flength)
		return false;
	if (!slength || slength < flength)
		return false;
	const char* ss = s.c_str();
	const char* fs = fragment.c_str();
	return !strncmp(ss, fs, flength) || !strncmp(ss + slength - flength, fs, flength);
}

bool restore_fragment(string& first, string& second, string& file)
{
	// see if first and seonds overlap partially
	int overlap_length = first.length() + second.length() - file.length();
//	assert(overlap_length >= 0);
	if (overlap_length < 0)
		return false;
	// see if first is adjacent to the left side and second is adjacent to the right side
	if (!strncmp(first.c_str() + first.length() - overlap_length, second.c_str(), overlap_length)) {
		file = first; file += second.c_str() + overlap_length;
		return true;
	}
	// see if first is adjacent to the right side and second is adjacent to the left side
	else if (!strncmp(first.c_str(), second.c_str() + second.length() - overlap_length, overlap_length)) {
		file = second; file += first.c_str() + overlap_length;
		return true;
	}
	else
		return false;
}

bool restore_fragments(int min_length, int max_length, string& file, const vector<fragment>& fragments)
{
	string first = fragments[max_length].first;
	fragment second_candidates = make_pair(fragments[max_length].second, "");
	if (second_candidates.first.empty()) {
		for (int i = max_length - 1; i >= min_length; i--) {
			string f = fragments[i].first, s = fragments[i].second;
			if (f.empty())
				continue;
			if (s.empty()) {
				second_candidates.first = f;
				break;
			}
			else {
				// see if f and/or s is a part of first
				bool f_is_part = have_same_fragment(f, first), s_is_part = have_same_fragment(s, first);
				if (f_is_part && s_is_part) {
					second_candidates.first = f; second_candidates.second = s;
				}
				else if (f_is_part)
					second_candidates.first = s;
				else
					second_candidates.first = f;
				break;
			}
		}
		if (second_candidates.first.empty())
			second_candidates.first = first;
	}
	if (restore_fragment(first, second_candidates.first, file))
		return true;
	else if (!second_candidates.second.empty() && restore_fragment(first, second_candidates.second, file))
		return true;
	else
		return false;
}

int main(int /* argc */, char** /* argv */)
{
	string line;
	istringstream iss;

	// read the number of cases
	getline(cin, line);
	iss.str(line);
	int cases;
	iss >> cases;
	iss.clear();
	if (cases)
		getline(cin, line); // skip a blank line
	while (cases--) {
		int min_length = file_size_max, max_length = 0, max_second = 0;
		vector<fragment> fragments(file_size_max + 1);
			// i-th slot contains a pair of file fragments of length i, and the first slot is never used

		while (cin) { // read the fragments
			getline(cin, line);
			if (line.empty())
				break;
			int length = line.length();
			min_length = min(min_length, length); max_length = max(max_length, length);
			fragment& f = fragments[length];
			if (f.first.empty())
				f.first = line;
			else if (f.first != line && f.second.empty())
				f.second = line;
		}

		// restore the file
		string file(min_length + max_length, '\0');
		fragment f = fragments[min_length];
		restore_fragments(min_length, max_length, file, fragments);
		cout << file << endl;
		if (cases)
			cout << endl;

		if (cin.eof())
			break;
	}
	return 0;
}

