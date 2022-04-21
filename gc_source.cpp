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

    colors[v] = num_colors;

    queue<int> candidates = find_candidates(v);
    dye_candidates( candidates );
}

queue<int> &Problem::find_candidates( int v ){
    queue<int> cands;
    for(int j=0; j<num_vertices; j++)
        if( colors[j]<0 && v!=j && !adjm[v][j] )
            cands.push(j);
    return cands;
}

void Problem::dye_candidates( queue<int> &candidates ){

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
