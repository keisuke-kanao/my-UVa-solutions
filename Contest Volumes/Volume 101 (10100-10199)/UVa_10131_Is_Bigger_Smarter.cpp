
/*
	11.6.1 Is Bigger Smarter?
	PC/UVa IDs: 111101/10131, Popularity: B, Success rate: high Level: 2

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10131_Is_Bigger_Smarter.cpp
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct elephant
{
	int nr;
	int weight;
	int iq;

	elephant(int _nr, int _weight, int _iq) : nr(_nr), weight(_weight), iq(_iq) {}
};

bool compare_elephant_weight(const elephant& i, const elephant& j)
{
	return i.weight < j.weight;
}

// find a LDS (Longest Decreasing Subsequence)
template<class T> int lds(vector<T>& values, vector<int>& indices,
	bool (*compare_values)(const T& i, const T& j))
// A compare_values function should return true if i < j, false otherwise.
{
	int c_max = 1; // length of LDS
	int p_max = 0; // index of the last element of LDS
	vector<int> p(values.size());
		// p[i] is the index of the penultimate element in the LDS which has the final element of values[i]
	vector<int> c(values.size());
		// c[i] is the length of the LDS which has the final element values[i]
	for (int i = 0; i < values.size(); i++) {
		c[i] = 1; p[i] = -1;
	}
	for (int i = 0; i < values.size(); i++)
		for (int j = 0; j < i; j++)
			if ((*compare_values)(values[i], values[j]) && c[j] + 1 > c[i]) {
				c[i] = c[j] + 1; p[i] = j;
				if (c[i] > c_max) {
					c_max = c[i]; p_max = i;
				}
			}
	indices.resize(c_max);
	for (int i = 0, j = p_max; i < c_max; i++, j = p[j])
		indices[c_max - i - 1] = j;
	return c_max;
}

bool compare_elephant(const elephant& i, const elephant& j)
{
	return i.iq < j.iq && i.weight != j.weight;
}

int main(int /* argc */, char** /* argv */)
{
	int nr = 0, weight, iq;
	vector<elephant> elephants;
	for (++nr; cin >> weight >> iq; nr++)
		elephants.push_back(elephant(nr, weight, iq));
	// sort the vector of elephants in ascending order of their weights
	sort(elephants.begin(), elephants.end(), compare_elephant_weight);
	vector<int> indices;
	lds(elephants, indices, compare_elephant);
	cout << indices.size() << endl;
	for (int i = 0; i < indices.size(); i++)
		cout << elephants[indices[i]].nr << endl;
#ifdef DEBUG
	for (int i = 1; i < indices.size(); i++) {
		elephant& previous = elephants[indices[i - 1]];
		elephant& current = elephants[indices[i]];
		if (previous.weight >= current.weight || previous.iq <= current.iq) {
			cerr << "an invalid sequence: " << previous.weight << ' ' << previous.iq <<
				", " << current.weight << ' ' << current.iq << endl;
		}
	}
#endif
	return 0;
}

