
/*
	8.6.5 Tug of War
	PC/UVa IDs: 110805/10032, Popularity: B, Success rate: low Level: 2

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10032_Tug_of_War.cpp
*/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

#ifdef DEBUG
void print_pr_people(int sum_of_weights, const vector< pair<unsigned char, unsigned char> >& nr_people)
{
	for (int i = 1; i <= sum_of_weights; i++)
		if (nr_people[i].first)
			cout << i << '(' << static_cast<unsigned int>(nr_people[i].first) << ' ' <<
				static_cast<unsigned int>(nr_people[i].second) << ") ";
	cout << endl;
}
#endif

int generate_nr_people(int n, const vector<int>& weights, vector< pair<unsigned char, unsigned char> >& nr_people)
{
/*
	While calculating each realizable team weight, 
	also record the minimum/maximum number of people whose weights are added up to it.
*/
	int sum_of_weights = 0;
	for (int i = 1; i <= n; i++) {
		int w = weights[i];
		for (int j = sum_of_weights; j; j--)
			if (nr_people[j].first) {
				if (nr_people[j + w].first) {
					nr_people[j + w].first = min(nr_people[j + w].first, static_cast<unsigned char>(nr_people[j].first + 1));
					nr_people[j + w].second = max(nr_people[j + w].second, static_cast<unsigned char>(nr_people[j].second + 1));
				}
				else {
					nr_people[j + w].first = nr_people[j].first + 1;
					nr_people[j + w].second = nr_people[j].second + 1;
				}
			}
		nr_people[w].first = 1;
		if (!nr_people[w].second)
			nr_people[w].second = 1;
		sum_of_weights += w;
	}
#ifdef DEBUG
	print_pr_people(sum_of_weights, nr_people);
#endif
	return sum_of_weights;
}

bool is_valid_team_weight(int nr_one, int nr_other, int one_weight, int other_weight, int nr_weights,
	const vector<int>& weights, const vector< pair<unsigned char, unsigned char> >& nr_people)
{
	if (!nr_weights)
		return false;
	int w = one_weight - weights[nr_weights];
	if (!w) {
		if (nr_one == 1)
			return true;
		else if (nr_other > 1 && other_weight == one_weight)
			return false;
		else return is_valid_team_weight(nr_other, nr_one, other_weight, one_weight, nr_weights, weights, nr_people);
	}
	else if (w < 0)
		return is_valid_team_weight(nr_other, nr_one, other_weight, one_weight, nr_weights, weights, nr_people);
	else if (nr_people[w].first && nr_one - 1 >= nr_people[w].first && nr_one - 1 <= nr_people[w].second &&
		is_valid_team_weight(nr_one - 1, nr_other, w, other_weight, nr_weights - 1, weights, nr_people))
		return true;
	else {
		if (!(w = other_weight - weights[nr_weights]))
			return (nr_other == 1) ? true : false;
		else if (w < 0)
			return false;
		else if (nr_people[w].first && nr_other - 1 >= nr_people[w].first && nr_other - 1 <= nr_people[w].second &&
			is_valid_team_weight(nr_one, nr_other - 1, one_weight, w, nr_weights - 1, weights, nr_people))
			return true;
		else
			return false;
	}
}

pair<int, int> find_minimum_team_weight_pair(int n, int sum_of_weights,
	const vector<int>& weights, const vector< pair<unsigned char, unsigned char> >& nr_people)
{
	int nr_one_max = n / 2, nr_other_max = 0; // max. number of people for a team
	if (n & 1)
		nr_other_max = nr_one_max + 1;
	int i = sum_of_weights / 2;
	for ( ; ; i--) {
		int nr_one = nr_people[i].first, nr_other = nr_people[sum_of_weights - i].first;
		if (nr_one && nr_other) {
			if (n & 1) {
				if (nr_one < nr_other_max && nr_other < nr_other_max) {
					if (is_valid_team_weight(nr_other_max, nr_one_max, sum_of_weights - i, i, n, weights, nr_people) ||
						is_valid_team_weight(nr_other_max, nr_one_max, i, sum_of_weights - i, n, weights, nr_people))
							break;
				}
				else if (nr_one == nr_other_max) {
					if (is_valid_team_weight(nr_other_max, nr_one_max, i, sum_of_weights - i, n, weights, nr_people))
						break;
				}
				else if (nr_other == nr_other_max) {
					if (is_valid_team_weight(nr_other_max, nr_one_max, sum_of_weights - i, i, n, weights, nr_people))
						break;
				}
			}
			else {
				if (nr_one <= nr_one_max && nr_other <= nr_one_max) {
					if (is_valid_team_weight(nr_one_max, nr_one_max, sum_of_weights - i, i, n, weights, nr_people) ||
						is_valid_team_weight(nr_one_max, nr_one_max, i, sum_of_weights - i, n, weights, nr_people))
						break;
				}
			}
		}
	}
	return make_pair(i, sum_of_weights - i);
}

int main(int /* argc */, char** /* argv */)
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	int cases; // number of test cases
	cin >> cases;
	while (cases--) {
		int n;
		cin >> n; // number of people
		vector<int> weights(n + 1); // vector of weights
		weights[0] = 0;
		for (int i = 1; i <= n; i++)
			cin >> weights[i];
		if (n < 2)
			cout << "0 " << weights[n] << endl;
		else {
			sort(weights.begin() + 1, weights.end());
			int sum_of_weights = 0;
			for (int i = 1; i <= n; i++)
				sum_of_weights += weights[i];
			vector< pair<unsigned char, unsigned char> > nr_people(sum_of_weights + 1, make_pair(0, 0));
				// 	nr_peoplei].first/second is the minimum/maximum number of people whose weights are added up to i, 
				// or 0 if no weights are added up to i
			generate_nr_people(n, weights, nr_people);
			pair<int, int> weight_pair = find_minimum_team_weight_pair(n, sum_of_weights, weights, nr_people);
			cout << weight_pair.first << ' ' << weight_pair.second << endl;
		}
		if (cases)
			cout << endl; // the output of each two consecutive cases will be separated by a blank line
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}
 
