
/*
	UVa 1207 - AGTC

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1207_AGTC.cpp	

	This problem is similar to UVa 164 - String Computer, UVa 526 - String Distance and Transform Process.
*/

#include <cstdio>
#include <cstring>

const int nr_chars_max = 1000;

enum {editMatchOrReplace, editInsert, editDelete};

struct edit_state {
	int cost_; // cost of reaching this state
/*
    int parent_; // parent state
*/
} edite_states[nr_chars_max + 1][nr_chars_max + 1];

int edit_distance(const char* s, const char* t, int sl, int tl)
{
	for (int i = 0; i < nr_chars_max + 1; i++) {
		// first row
		edite_states[0][i].cost_ = i;
/*
		edite_states[0][i].parent_ =  (i) ? editInsert : -1;
*/
		// first column
        edite_states[i][0].cost_ = i;
/*
		edite_states[i][0].parent_ = (i) ? editDelete : -1;
*/
	}

	for (int i = 1; i < sl; i++)
		for (int j = 1; j < tl; j++) {
			int costs[editDelete - editMatchOrReplace + 1];
			// For inserting or deleting or replacing characters, cost is one, while for maching characters, cost is zero.
			costs[editMatchOrReplace] = edite_states[i - 1][j - 1].cost_ + ((s[i] == t[j]) ? 0 : 1);
			costs[editInsert] = edite_states[i][j - 1].cost_ + 1;
			costs[editDelete] = edite_states[i - 1][j].cost_ + 1;
			edite_states[i][j].cost_ = costs[editMatchOrReplace];
/*
			edite_states[i][j].parent_ = editMatchOrReplace;
*/
			for (int k = editInsert; k <= editDelete; k++)
				if (costs[k] < edite_states[i][j].cost_) {
					edite_states[i][j].cost_ = costs[k];
/*
					edite_states[i][j].parent_ = k;
*/
				}
		}
	return edite_states[sl - 1][tl - 1].cost_;
} 

/*
void reconstruct_path(char* s, char* t, int i, int j, int& p, int& n)
{
	int parent = edite_states[i][j].parent_;
	if (parent == -1)
		p = n = 1;
	else if (parent == editMatchOrReplace) {
		reconstruct_path(s, t, i - 1,j - 1, p, n);
		if (s[i] != t[j]) {
			printf("%d Replace %d,%c\n", n, p, t[j]);
			n++;
		}
		p++;
	}
	else if (parent == editInsert) {
		reconstruct_path(s, t, i, j - 1, p, n);
		printf("%d Insert %d,%c\n", n, p, t[j]);
		p++; n++;
	}
	else if (parent == editDelete) {
		reconstruct_path(s, t, i - 1, j, p, n);
		printf("%d Delete %d\n", n, p);
		n++;
	}
}
*/

char s[nr_chars_max + 2], t[nr_chars_max + 2];

int main()
{
	while (true) {
		s[0] = t[0] = ' ';
		int sl, tl;
		if (scanf("%d %s", &sl, &s[1]) == EOF)
			break;
		scanf("%d %s", &tl, &t[1]);
		int d = edit_distance(s, t, sl + 1, tl + 1);
		printf("%d\n", d);
	}
	return 0;
}

