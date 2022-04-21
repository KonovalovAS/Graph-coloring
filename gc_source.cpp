#include "gc_header.h"


Problem::Problem( int nv, int ne, vector<vector<bool>> &Adj_M ){
    num_vertices = nv;
    num_edges = ne;
    adjm = Adj_M;

    colors = vector<int> (num_vertices,-1);
    num_colors = 0;

    solved = false;
}

int Problem::Number_of_colors(){
    return num_colors;
}

void Problem::show_colors(){
    for(auto c: colors)
        cout << c << " ";
}

void Problem::Solve(){

    if( !solved ){
        int cur(0);

        while( cur < num_vertices ){

        //cout<<"Current vertex: "<<cur<<"\n";
            partial_dye( cur );

            num_colors++;
            cur = next_undyed( cur );
        }

        solved = true;
    }
}

//====

int Problem::next_undyed(int start){

    if( start < num_vertices )
        while( start<num_vertices && colors[start]>=0 )
            start++;

    return start;
}

void Problem::partial_dye( int v ){

    //cout << "\tIn partial dye\n";
    colors[v] = num_colors;

    queue<int> candidates;
    find_candidates(v,candidates);

    //cout<<"\tBack in partial dye, gonna dye candidates\n";
    dye_candidates( candidates );
}

void Problem::find_candidates( int v, queue<int> &cands ){

    //cout<<"\t\tLooking for candidates\n";
    for(int j=0; j<num_vertices; j++){
            //cout<<"\t\t"<<j<<"\n";
        if( v!=j && colors[j]<0 && !adjm[v][j] ){
            cands.push(j);
            //cout<<"\t\t\tpushing "<<j<<"\n";
        }
    }
    //cout<<"\t\tall found\n";
}

void Problem::dye_candidates( queue<int> &candidates ){

    //cout<<"\t\t\tDying candidates\n";
    vector<int> others;

    while( !candidates.empty() ){

        int cur = candidates.front();
        candidates.pop();

        if( not_adjacent_to_others(cur,others) ){
            colors[cur] = num_colors;
            others.push_back(cur);
        }
    }
}

bool Problem::not_adjacent_to_others( int v, vector<int> &others ){
    bool ans = true;
    int tmp = others.size();
    for(int i=0; i<tmp && ans; i++)
        ans = ans && !adjm[v][others[i]];
    return ans;
}

// Auxiliary functions

void solve_4_console_input(){
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
}
//

int solve_4_file_input( string &fname ){
    ifstream input( fname );
    int n_v, n_e;
    input >> n_v >> n_e;

    vector<vector<bool>> adjmat(n_v,vector<bool> (n_v,false));
    for( int i=0; i<n_e; i++ ){
        int v_first, v_second;
        input >> v_first >> v_second;
        adjmat[v_first][v_second] = true;
        adjmat[v_second][v_first] = true;
    }
    input.close();

    Problem my_problem( n_v, n_e, adjmat );
    my_problem.Solve();
    //cout << my_problem.Number_of_colors() << "\n";
    //my_problem.show_colors();
    return my_problem.Number_of_colors();
}

void run_tests_console( string &fname ){
    ofstream OUT ( fname );

    int good(0),all(0);
    string name;
    int gv;
    cin >> name >> gv;
    while( name != "end" ){
        all++;

        name = "gc_" + name;
        int myres = solve_4_file_input( name );
        double dif = (double)(myres-gv)/gv;
        dif *= 100;
        OUT << name << "\t" << dif << "%\tgolden value: "
            << gv << "\tme: " << myres << "\n";
        cout << name << "\t" << dif << "%\tgolden value: "
             << gv << "\tme: " << myres << "\n";

        if(dif<=20 && dif>=-20)
            good++;

        cin >> name >> gv;
    }
    OUT << good << " out of " << all << " passed!";
    cout << good << " out of " << all << " passed!";

    OUT.close();
}
