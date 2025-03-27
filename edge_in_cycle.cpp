#include <cstdint>
#include <vector>
#include <iostream>

// in undirected graph checks if edges is in some cicle
// in_cycle[i] true if edge with num i is in cycle

using namespace std;

#define N_MAX 100001
#define M_MAX 100001

int t_in[N_MAX];
bool visited[N_MAX];
bool in_cycle[M_MAX];
int tme = 1;

int dfs(int curr, int parr, vector<vector<pair<int, int>>>& graph)
{
    t_in[curr] = tme++;
    visited[curr] = true;
    int min_t_in = INT32_MAX;

    for(auto it : graph[curr])
    {
        if(!visited[it.first])
        {
            int ret = dfs(it.first, curr, graph);
            min_t_in = min(min_t_in, ret);
            if(ret <= t_in[curr])
            {
                in_cycle[it.second] = true;
            }   
        }
        else if(it.first != parr)
        {
            if(t_in[it.first] < min_t_in)
            {
                min_t_in = t_in[it.first];
            }
            in_cycle[it.second] = true;
        }
    } 
    return min_t_in;
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int,int>>> graph(n+1);

    for(int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        graph[x].push_back({y, i});
        graph[y].push_back({x, i});
    }

    dfs(1, 0, graph);

    for(int i = 0 ; i<m; i++)
        cout << in_cycle[i] << " ";
    
    cout << endl;
    return 0;
}
