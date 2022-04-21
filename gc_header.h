#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Problem{
public:

    Problem( int nv, int ne, vector<vector<bool>> &Adj_M );
    void Solve();

    int Number_of_colors();
    void show_colors();

private:

    bool solved;

    int num_vertices,
        num_edges;
    vector<vector<bool>> adjm; // adjacency matrix

    int num_colors;
    vector<int> colors; // solution

    int next_undyed(int start);
    void partial_dye( int v );
    queue<int> &find_candidates( int v );
    void dye_candidates( queue<int> &candidates );
    bool not_adjacent_to_others( int v, vector<int> &others );
};
