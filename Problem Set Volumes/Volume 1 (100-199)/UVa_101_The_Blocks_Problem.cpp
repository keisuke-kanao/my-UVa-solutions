
/*
	UVa 101 - The Blocks Problem

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_101_The_Blocks_Problem.cpp
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <iterator>
using namespace std;

typedef pair<int, list<int>::iterator> bposition;

void push_block(int b /* block */, int p /* positon */, vector< list<int> >& blocks, vector<bposition>& positions)
// push b onto p
{
	positions[b].first = p;
	list<int>& l = blocks[p];
	positions[b].second = l.insert(l.end(), b);
}

void return_blocks(int b /* block */, vector< list<int> >& blocks, vector<bposition>& positions)
// return any blocks that are stacked on top of block b
{
	list<int>& l = blocks[positions[b].first];
	list<int>::iterator i = positions[b].second, e = l.end();
	if (++i != e) {
		list<int>::iterator j = i;
		do
			push_block(*j, *j, blocks, positions);
		while (++j != e);
		l.erase(i, e);
	}
}

void move_onto(int a, int b, vector< list<int> >& blocks, vector<bposition>& positions)
// Put block a onto block b, 
// after returning any blocks that are stacked on top of blocks a and b to their initial positions
{
	// return any blocks that are stacked on top of blocks a and b
	return_blocks(a, blocks, positions);
	return_blocks(b, blocks, positions);
	// move block a onto block b
	blocks[positions[a].first].erase(positions[a].second);
	push_block(a, positions[b].first, blocks, positions);
}
void move_over(int a, int b, vector< list<int> >& blocks, vector<bposition>& positions)
// Put block a onto the top of the stack containing block b, 
// after returning any blocks that are stacked on top of block a to their initial positions
{
	// return any blocks that are stacked on top of block a
	return_blocks(a, blocks, positions);
	// move block a onto the top of the stack containing block b
	blocks[positions[a].first].erase(positions[a].second);
	push_block(a, positions[b].first, blocks, positions);
}

void pile_blocks(int b /* block */, int p /* position */, vector< list<int> >& blocks, vector<bposition>& positions)
{
	list<int>& l = blocks[positions[b].first];
	list<int>::iterator i = positions[b].second;
	list<int>::iterator e = l.end();
	for (list<int>::iterator j = i; j != e; ++j)
		push_block(*j, p, blocks, positions);
	l.erase(i, e);
}

void pile_onto(int a, int b, vector< list<int> >& blocks, vector<bposition>& positions)
// Move the pile of blocks consisting of block a, and any blocks that are stacked above block a, onto block b.
// All blocks on top of block b are moved to their initial positions prior to the pile taking place. 
// The blocks stacked above block a retain their order when moved.
{
	// return any blocks that are stacked on top of block b
	return_blocks(b, blocks, positions);
	pile_blocks(a, positions[b].first, blocks, positions);
}

void pile_over(int a, int b, vector< list<int> >& blocks, vector<bposition>& positions)
// Put the pile of blocks consisting of block a, and any blocks that are stacked above block a, 
// onto the top of the stack containing block b. 
// The blocks stacked above block a retain their original order when moved.
{
	pile_blocks(a, positions[b].first, blocks, positions);
}

int main()
{
	int nr_blocks;
	cin >> nr_blocks;
	vector< list<int> > blocks(nr_blocks);
		// blocks[i] is a stack of blocsk at position i
	vector<bposition> positions(nr_blocks);
		// positions[i] is where block i is stacked: positions[i].second in the list of blocks[positions[i].first]
	for (int i = 0; i < nr_blocks; i++) { // initially, each blocks[i] has only one block i
		blocks[i].push_back(i);
		positions[i] = make_pair(i, blocks[i].begin());
	}
	string command;
	getline(cin, command); // skip '\n'
	while (true) {
		getline(cin, command);
		if (command == "quit")
			break;
		istringstream iss(command);
		string s, t;
		int a, b;
		iss >> s >> a >> t >> b;
		if (a == b || positions[a].first == positions[b].first) // an illegal command
			continue;
		if (s == "move") {
			if (t == "onto")
				move_onto(a, b, blocks, positions);
			else
				move_over(a, b, blocks, positions);
		}
		else {
			if (t == "onto")
				pile_onto(a, b, blocks, positions);
			else
				pile_over(a, b, blocks, positions);
		}
	}
	for (int i = 0; i < nr_blocks; i++) {
		cout << /* setfill(' ') << setw(2) << */ i << ':';
		list<int>& l = blocks[i];
		for (list<int>::const_iterator j = l.begin(), e = l.end(); j != e; ++j)
			cout << ' ' << *j;
		cout << endl;
	}
	return 0;
}

