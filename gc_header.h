#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

void solve_4_console_input();

int solve_4_file_input( string &fname );

void run_tests_console( string &fname );

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
    void find_candidates( int v, queue<int> &cands );
    void dye_candidates( queue<int> &candidates );
    bool not_adjacent_to_others( int v, vector<int> &others );
};
