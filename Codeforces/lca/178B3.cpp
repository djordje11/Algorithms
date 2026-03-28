#include <cstdint>
#include <vector>
#include <iostream>
#include <set>
// in undirected graph checks if edges is in some cicle
// in_cycle[i] true if edge with num i is in cycle

using namespace std;

#define N_MAX 100001
#define M_MAX 100001

int t_in[N_MAX];
bool visited[N_MAX];
bool in_cycle[M_MAX];
int tme = 1;
bool visited2[N_MAX];
int map_graph[N_MAX];


int dp[21][100000 + 1]; 
int t_out[100000 + 1];
int depth[100000 + 1] = {-1};

void dfs3(int curr, int parr, vector<set<int>>& graph)
{
    dp[0][curr] = parr;
    depth[curr] = 1 + depth[parr];
    t_in[curr] = tme++;
    for(auto it : graph[curr])
    {
        if(it != parr)
        {
            dfs3(it, curr, graph);
        }
    } 
    t_out[curr] = tme++;
}

bool is_ancestor(int u, int v)
{
    return t_in[v] > t_in[u] && t_out[v] < t_out[u];
}

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

void dfs2(int curr, int parr, vector<vector<pair<int, int>>>& graph, int id)
{
    visited2[curr] = true;
    map_graph[curr] = id;
    for(auto it : graph[curr])
    {
        if(in_cycle[it.second] && !visited2[it.first])
        {
            dfs2(it.first, curr, graph, id);
        }
    } 
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

    int id = 1;
    for(int i = 1; i <= n; i++)
        if(!visited2[i])
            dfs2(i, 0, graph, id++);
    
    vector<set<int>> new_graph(id);
    
    for(int i = 1; i <= n; i++)
    {
        for(auto it : graph[i])
        {
            if(map_graph[i] != map_graph[it.first])
            {
                new_graph[map_graph[i]].insert(map_graph[it.first]);
                new_graph[map_graph[it.first]].insert(map_graph[i]);
            }
        }
    }




    dfs3(1, 0, new_graph);


    for(int i = 1; 1<< i <= n; i++)
        for(int j = 1; j <= n; j++)
            dp[i][j] = dp[i-1][dp[i-1][j]];


    int q;
    cin >> q;
    while(q--)
    {
        int x, y;
        cin >> x >> y;
        x = map_graph[x];
        y = map_graph[y];
        if(
            x == y
        )
        {
            cout << 0 << endl;
            continue;
        }
        if(depth[x] > depth[y])
            swap(x, y);


        if(is_ancestor(x, y))
        {
            cout << depth[y] - depth[x] << endl;
            continue;
        }

        int count = depth[x] + depth[y];
        for(int i = 20; i >= 0; i--)
            if(dp[i][x] != 0 && !is_ancestor(dp[i][x], y)) x = dp[i][x];

        x = dp[0][x];

        count -= 2 * depth[x];
        cout << count << endl;
    }
    return 0;
}
