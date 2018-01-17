
/*
	4.6.5 Shoemaker's Problem
	PC/UVa IDs: 110405/10026, Popularity: C, Success rate: average Level: 2

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10026_Shoemakers_Problem.cpp
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct job { // a shoemaker's job
	int id; // position in which the job appeared in the input
	int days; // number of days it takes the shoemaker to finish the job
	int fine; // fine per day
};

bool compare_job(const job& i, const job& j)
{
	return i.days * j.fine < j.days * i.fine;
}

int main(int /* argc */, char** /* argv */)
{
	// read the number of test cases
	int cases;
	cin >> cases;
	while (cases--) {
		// read the number of jobs
		int n;
		cin >> n;
		// read each job, generate the job structure, and append it to the vector of jobs
		vector<job> jobs;
		for (int i = 0; i < n; i++) {
			job j;
			j.id = i + 1;
			cin >> j.days >> j.fine;
			jobs.push_back(j);
		}
		// stable sort the vector of jobs in the ascending order of fines to be paid
		stable_sort(jobs.begin(), jobs.end(), compare_job);
		for (int i = 0; i < jobs.size(); i++) {
			cout << jobs[i].id;
			if (i < jobs.size() - 1)
				cout << ' ';
			else
				cout << endl;
		}
		if (cases)
			cout << endl; // print a blink line to separate the two consecutive cases
	}
	return 0;
}

