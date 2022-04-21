#include "gc_header.h"

int main()
{
    int n_v, n_e;
    cin >> n_v >> n_e;

    vector<vector<bool>> adjmat(n_v,vector<bool> (n_v,false));
    for( int i=0; i<n_e; i++ ){
        int v_first, v_second;
        cin >> v_first >> v_second;
        adjmat[v_first][v_second] = true;
        adjmat[v_second][v_first] = true;
    }

    Problem my_problem( n_v, n_e, adjmat );
    my_problem.Solve();
    cout << my_problem.Number_of_colors() << "\n";
    my_problem.show_colors();

    return 0;
}
