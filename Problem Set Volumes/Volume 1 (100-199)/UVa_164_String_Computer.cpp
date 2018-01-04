
/*
	UVa 164 - String Computer

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_164_String_Computer.cpp

	from ACM South Pacific Regionals - 1991
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_VV_SouthPac/1991/index.html)
*/

#include <cstdio>
#include <cstring>

const int nr_chars_max = 20;

enum {editMatchOrReplace, editInsert, editDelete};

struct edit_state {
	int cost_; // cost of reaching this state
    int parent_; // parent state
} edite_states[nr_chars_max + 1][nr_chars_max + 1];

int edit_distance(const char* s, const char* t, int sl, int tl)
{
	for (int i = 0; i < nr_chars_max + 1; i++) {
		// first row
		edite_states[0][i].cost_ = i;
		edite_states[0][i].parent_ =  (i) ? editInsert : -1;
		// first column
        edite_states[i][0].cost_ = i;
		edite_states[i][0].parent_ = (i) ? editDelete : -1;
	}

	for (int i = 1; i < sl; i++)
		for (int j = 1; j < tl; j++) {
			int costs[editDelete - editMatchOrReplace + 1];
			// For inserting or deleting or replacing characters, cost is one, while for maching characters, cost is zero.
			costs[editMatchOrReplace] = edite_states[i - 1][j - 1].cost_ + ((s[i] == t[j]) ? 0 : 1);
			costs[editInsert] = edite_states[i][j - 1].cost_ + 1;
			costs[editDelete] = edite_states[i - 1][j].cost_ + 1;
			edite_states[i][j].cost_ = costs[editMatchOrReplace];
			edite_states[i][j].parent_ = editMatchOrReplace;
			for (int k = editInsert; k <= editDelete; k++)
				if (costs[k] < edite_states[i][j].cost_) {
					edite_states[i][j].cost_ = costs[k];
					edite_states[i][j].parent_ = k;
				}
		}
	return edite_states[sl - 1][tl - 1].cost_;
} 

void reconstruct_path(char* s, char* t, int i, int j, int& p)
{
	int parent = edite_states[i][j].parent_;
	if (parent == -1)
		p = 1;
	else if (parent == editMatchOrReplace) {
		reconstruct_path(s, t, i - 1,j - 1, p);
		if (s[i] != t[j])
			printf("C%c%02d", t[j], p);
		p++;
	}
	else if (parent == editInsert) {
		reconstruct_path(s, t, i, j - 1, p);
		printf("I%c%02d", t[j], p);
		p++;
	}
	else if (parent == editDelete) {
		reconstruct_path(s, t, i - 1, j, p);
		printf("D%c%02d", s[i], p);
	}
}

int main()
{
	while (true) {
		char s[nr_chars_max + 2], t[nr_chars_max + 2];
		s[0] = t[0] = ' ';
		scanf("%s", &s[1]);
		if (s[1] == '#')
			break;
		scanf("%s", &t[1]);
		int sl = strlen(s), tl = strlen(t);
		edit_distance(s, t, sl, tl);
		int p;
		reconstruct_path(s, t, sl - 1, tl - 1, p);
		printf("E\n");
	}
	return 0;
}

