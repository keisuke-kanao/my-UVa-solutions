
/*
	UVa 10243 - Fire! Fire!! Fire!!!

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10243_Fire_Fire_Fire.cpp
*/

/*
There is a greedy algorithm for finding minimum vertex cover of a tree which uses DFS traversal.

1. For each leaf of the tree, select its parent (i.e. its parent is in minimum vertex cover).
2. For each internal node:
  if any of its children is not selected, then select this node.
*/

/*
We can notice that for every edge we have to include one of the nodes. Which one to choose? 
Assume we have an edge with "normal" node and a leaf. Which node is better to choose? 
Not the leaf of course, as the other node might help us with one more edge. 
The algorithm is as follows:
  1 Start from any node which is not a leaf.
  2 For each child make a DFS call and 
    when it returns check if either parent or child are marked as node in vertex cover. 
    If not you have to choose one of them so choose the parent (and mark it).
  3 For a leaf do nothing.
*/

#include<stdio.h>
#include<vector>
using namespace std;

const int N_max = 1000;
vector<int> graph[N_max + 1];
int covered[N_max + 1];

int tree_vertex_cover(int v)
{
    covered[v] = -1;
	if (graph[v].size() == 1) // leaf
		return 0;
    int nr_cover = 0;
	for (size_t i = 0; i < graph[v].size(); i++)
        if(!covered[graph[v][i]]) {
            nr_cover += tree_vertex_cover(graph[v][i]);
            if(covered[v] < 1 && covered[graph[v][i]] < 1)
                nr_cover++, covered[v] = 1;
        }
    return nr_cover;
}

int main()
{
	while (true) {
		int i, j, k, N;
		scanf("%d", &N);
		if (!N)
			break;
		for (i = 1; i <= N; i++) {
            graph[i].clear();
            covered[i] = 0;
			scanf("%d", &j);
			while (j--) {
				scanf("%d", &k);
				graph[i].push_back(k);
			}
		}
		int min_nr_cover = 1;
		if (N > 2) {
			for (i = 1; i <= N; i++)
    	        if(graph[i].size() > 1) {
					min_nr_cover = tree_vertex_cover(i);
        	        break;
				}
		}
        printf("%d\n", min_nr_cover);
	}
	return 0;
}

