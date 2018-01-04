
/*
	UVa 405 - Message Routing

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_405_Message_Routing.cpp

	from ACM South Central Regional Programming Contest 1995-96, Problem #6
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_SouthCen/1995/index.html)
*/

#include <string>
#include <map>
#include <cstdio>
#include <cstring>
using namespace std;

const int M_max = 10, I_max = 9, nr_components = 4, nr_chars_max = 15;

struct routing_table {
	int mi_;
	char components_[nr_components][nr_chars_max + 1];
};

struct mta {
	int nr_tables_;
	routing_table routing_tables_[I_max];
} mtas[M_max];

string mta_names[M_max];
bool routed[M_max];

int main()
{
	int M;
	char s[nr_chars_max + 1];
	for (int scenario_nr = 1; scanf("%d", &M) != EOF; scenario_nr++) {
		map<string, int> mta_name_indices;
		for (int i = 0; i < M; i++) {
			int I;
			scanf("%s %d", s, &I);
			pair<map<string, int>::iterator, bool> result = mta_name_indices.insert(make_pair(s, static_cast<int>(mta_name_indices.size())));
			mta_names[result.first->second] = result.first->first;
			mta& m = mtas[result.first->second];
			m.nr_tables_ = I;
			for (int j = 0; j < I; j++) {
				scanf("%s", s);
				pair<map<string, int>::iterator, bool> result = mta_name_indices.insert(make_pair(s, static_cast<int>(mta_name_indices.size())));
				routing_table& r = m.routing_tables_[j];
				r.mi_ = result.first->second;
				for (int k = 0; k < nr_components; k++)
					scanf("%s", &r.components_[k]);
			}
		}
		printf("Scenario # %d\n", scenario_nr);
		int N;
		scanf("%d", &N);
		for (int i = 1; i <= N; i++) {
			for (int j = 0; j < M; j++)
				routed[j] = false;
			routing_table r;
			scanf("%s", s);
			routed[r.mi_ = mta_name_indices[s]] = true;
			for (int j = 0; j < nr_components; j++)
				scanf("%s", &r.components_[j]);
			while (true) {
				mta& m = mtas[r.mi_];
				int j;
				for (j = 0; j < m.nr_tables_; j++) {
					routing_table& mr = m.routing_tables_[j];
					int k;
					for (k = 0; k < nr_components; k++)
						if (mr.components_[k][0] != '*' && strcmp(mr.components_[k], r.components_[k]))
							break;
					if (k == nr_components) // found
						break;
				}
				if (j < m.nr_tables_) { // found
					if (r.mi_ == m.routing_tables_[j].mi_) {
						printf("%d -- delivered to %s\n", i, mta_names[r.mi_].c_str());
						break;
					}
					else if (routed[m.routing_tables_[j].mi_]) {
						printf("%d -- circular routing detected by %s\n", i, mta_names[m.routing_tables_[j].mi_].c_str());
						break;
					}
					else
						routed[r.mi_ = m.routing_tables_[j].mi_] = true;
				}
				else {
					printf("%d -- unable to route at %s\n", i, mta_names[r.mi_].c_str());
					break;
				}
			}
		}
		putchar('\n');
	}
	return 0;
}

