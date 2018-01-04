
/*
	UVa 335 - Processing MX Records

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_335_Processing_MX_Records.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

struct MX_record {
	vector<string> pieces_;
	bool operational_;
	int preference_;
	string redirected_name_;
};

void get_pieces(const string& s, vector<string>& pieces)
{
	for (const char *p = s.c_str(), *q = p; *p; ) {
		while (*p && *p != '.')
			p++;
		pieces.push_back(string(q, p - q));
		if (*p)
			q = ++p;
	}
}

bool compare_pieces(const vector<string>& vs, const vector<string>& vt)
{
	int i = vs.size() - 1, j = vt.size() - 1;
	for( ; i >= 0 && j >= 0; i--, j--) {
		if (vs[i] == "*" || vt[j] == "*")
			return true;
		else if (vs[i] != vt[j])
			return false;
	}
	return (i == -1 && j == -1) ? true : false;
}

int main()
{
	string s, line;
	getline(cin, line);
	istringstream iss(line);
	int N;
	iss >> N;
	iss.clear();
	vector<MX_record> MX_records(N);
	for (int i = 0; i < N; i++) {
		MX_records[i].operational_ = true;
		getline(cin, line);
		iss.str(line);
		if (line[0] != ' ') {
			iss >> s;
			get_pieces(s, MX_records[i].pieces_);
		}
		else
			MX_records[i].pieces_ = MX_records[i - 1].pieces_;
		iss >> MX_records[i].preference_ >> MX_records[i].redirected_name_;
		iss.clear();
	}
	while (true) {
		getline(cin, line);
		if (line[0] == 'X')
			break;
		else {
			iss.str(line);
			char c;
			iss >> c >> s;
			iss.clear();
			switch (c) {
			case 'A':
			{
				vector<string> pieces;
				get_pieces(s, pieces);
				int ri = -1;
				for (int i = 0; i < N; i++)
					if (compare_pieces(pieces, MX_records[i].pieces_)) {
						if (MX_records[i].operational_ &&
							(ri == -1 || MX_records[ri].preference_ > MX_records[i].preference_))
							ri = i;
					}
				cout << s << " =>";
				if (ri != -1)
					cout << ' ' << MX_records[ri].redirected_name_;
				cout << endl;
			}
				break;
			case 'U':
				for (int i = 0; i < N; i++)
					if (MX_records[i].redirected_name_ == s)
						MX_records[i].operational_ = true;
				break;
			case 'D':
				for (int i = 0; i < N; i++)
					if (MX_records[i].redirected_name_ == s)
						MX_records[i].operational_ = false;
				break;
			}
		}
	}
	return 0;
}

