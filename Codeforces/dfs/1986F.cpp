#include <iostream>
#include <vector>

using namespace std;

#define N_MAX 100001
using ull = signed long long;

bool visited[N_MAX];
int level[N_MAX];
int h[N_MAX];

signed long long max1 = 0;
int dfs(int curr,int par, vector<vector<int>>& graph, int curr_level)
{
    visited[curr] = true;
    level[curr] = curr_level;
    h[curr] = curr_level;
    ull res = 1;
    ull n = graph.size()-1;
    for(auto it : graph[curr])
    {
        if(it == par || visited[it] && level[it] > level[curr])continue;
        if(!visited[it])
        {
            res += dfs(it, curr,  graph, curr_level + 1);

        }
        h[curr] = min(h[curr], h[it]);  
    } 

    if(h[curr] > level[par])
    {   
        max1 = std::max<signed long long>(max1, res * (n-res));
    }
    return res;
}

int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        int n, m;
        max1 = 0;
        cin >> n >> m;
        vector<vector<int>> graph(n+1);

        for(int i = 0; i <= n; i++)
        {
            visited[i] = level[i] = h[i] = 0;
        }

        for(int i = 0; i < m; i++)
        {
            int x, y;
            cin >> x >> y;
            graph[x].push_back(y);
            graph[y].push_back(x);
        }
        dfs(1, 0, graph, 0);

        cout << ull(n) * ull((n-1))/2 - max1 << endl;

    }
    return 0;
}
