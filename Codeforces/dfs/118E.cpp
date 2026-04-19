#include <iostream>
#include <vector>

// check if graph have bridge using dfs tree
// if have output 0
// othervise direct all edges from dfs tree downwards tree, and all back edges upwards tree

using namespace std;

#define N_MAX 100001

bool visited[N_MAX];
int level[N_MAX];
int h[N_MAX];
int edges[3*N_MAX][2];

bool can = true;
int cnt = 0;
void dfs(int curr,int par, vector<vector<int>>& graph, int curr_level)
{
    visited[curr] = true;
    level[curr] = curr_level;
    h[curr] = curr_level;
    for(auto it : graph[curr])
    {
        if(it == par || visited[it] && level[it] > level[curr])continue;
        edges[cnt][0] = curr;
        edges[cnt++][1] = it;
        if(!visited[it])
        {
            dfs(it, curr,  graph, curr_level + 1);
            if(h[it] > level[curr])      
            {
                can = false;
                break;
            }
            h[curr] = min(h[curr], h[it]);
        }
        else 
        {
            h[curr] = min(h[curr], h[it]);
        }
    } 
}


int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n+1);

    for(int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    dfs(1, 0, graph, 0);

    if(can)
    {
        for(int i = 0; i < m; i++)
        {
            cout << edges[i][0] << " " << edges[i][1] << endl;
        }
    }
    else 
    {
        cout << 0 << endl;
    }


    return 0;
}
