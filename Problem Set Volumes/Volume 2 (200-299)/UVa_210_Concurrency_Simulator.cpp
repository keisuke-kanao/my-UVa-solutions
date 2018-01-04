
/*
	UVa 210 - Concurrency Simulator

	To build using Visual Studio 2015:
		cl -EHsc -O2 UVa_210_Concurrency_Simulator.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <deque>
#include <cstring>
using namespace std;

const int nr_programs_max = 10, nr_statements_max = 26;

enum {st_assignment, st_output, st_lock, st_unlock, st_end};
const int nr_statement_types = st_end - st_assignment + 1;

struct statement {
	int type_;
	int variable_, value_;
};

struct program {
	int current_; // current statement
	int remaining_; // number of remaining statements
	statement statements_[nr_statements_max];
} programs[nr_programs_max];

const int nr_variables = 'z' - 'a' + 1;
int values[nr_variables];
int nr_programs, execution_times[nr_statement_types], quantum;

deque<int> ready_queue, blocked_queue;

int main()
{
	string s;
	getline(cin, s);
	istringstream iss(s);
	int nr_cases;
	iss >> nr_cases;
	iss.clear();
	while (nr_cases--) {
		getline(cin, s); // a blank line
		getline(cin, s);
		iss.str(s);
		iss >> nr_programs;
		for (int i = 0; i < nr_statement_types; i++)
			iss >> execution_times[i];
		iss >> quantum;
		iss.clear();
		memset(values, 0, sizeof(values));
		for (int i = 0; i < nr_programs; i++) {
			program& p = programs[i];
			p.current_ = p.remaining_ = 0;
			do {
				getline(cin, s);
				iss.str(s);
				string t, u;
				iss >> t;
				statement& st = p.statements_[p.remaining_++];
				if (t == "print") {
					iss >> u;
					st.type_ = st_output, st.variable_ = u[0] - 'a';
				}
				else if (t == "lock")
					st.type_ = st_lock;
				else if (t == "unlock")
					st.type_ = st_unlock;
				else if (t == "end")
					st.type_ = st_end;
				else {
					st.type_ = st_assignment, st.variable_ = t[0] - 'a';
					iss >> u >> st.value_;
				}
				iss.clear();
			} while (p.statements_[p.remaining_ - 1].type_ != st_end);
#ifdef DEBUG
			cout << i << ": " << p.remaining_ << " stateemtns\n";
#endif
			ready_queue.push_back(i);
		}
		bool locked = false;
		while (!ready_queue.empty()) {
			int i = ready_queue.front();
			ready_queue.pop_front();
			program& p = programs[i];
			int q = quantum;
			bool blocked = false;
			do {
				statement& st = p.statements_[p.current_];
				q -= execution_times[st.type_];
				switch (st.type_) {
				case st_assignment:
					values[st.variable_] = st.value_;
					p.current_++, p.remaining_--;
					break;
				case st_output:
					cout << i + 1 << ": " << values[st.variable_] << endl;
					p.current_++, p.remaining_--;
					break;
				case st_lock:
					if (locked) {
						blocked_queue.push_back(i);
						q = -1, blocked = true;
					}
					else {
						locked = true;
						p.current_++, p.remaining_--;
					}
					break;
				case st_unlock:
					if (!blocked_queue.empty()) {
						int j = blocked_queue.front();
						blocked_queue.pop_front();
						ready_queue.push_front(j);
					}
					locked = false;
					p.current_++, p.remaining_--;
					break;
				case st_end:
					p.current_++, p.remaining_--;
					break;
				}
#ifdef DEBUG
			cout << i + 1 << ": " << p.current_ << ' ' << p.remaining_ << ' ' << q << endl;
#endif
			} while (p.remaining_ && q > 0);
			if (p.remaining_&& !blocked)
				ready_queue.push_back(i);
		}
		if (nr_cases)
			cout << endl;
	}
	return 0;
}

